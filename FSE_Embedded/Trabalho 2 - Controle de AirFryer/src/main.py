from PID.pid_use import PID
from i2c.bmp280 import BMP
from i2c.lcd import LCD
from uart.uart import Uart
from gpio.controle_potencia import ControlePotencia
from utils.log_csv import cria_log

from time import sleep
from threading import Thread

class ControleAirFryer:
    """
    Classe que faz o controle propriamente dito da AirFryer:
    - Funcionamento
    - Modos
    - PID (temperaturas e controle de potência)
    - Utilitários para tempo e iterações
    - Controladores de Threads
    """
    def __init__(self):
        self.pid = PID()
        self.bmp = BMP()
        self.lcd = LCD()
        self.uart = Uart()
        self.controle_potencia = ControlePotencia()

        self.ligado = False
        self.funcionando = False
        self.modo_inicial = "dashboard" # Dashboard ou Encoder
        self.modo_encoder = "manual" # Manual ou Automático

        self.temp_int = 27.5
        self.temp_amb = 20.0
        self.temp_ref = 40.0
        self.sg_cntrl = 0

        self.inicia_timer = 0
        self.iter = 0
        self.tempo = 0
        self.tempo_restante = 0
        self.opcao_auto = None

        self.thread_dashboard_funcionando = False
        self.thread_manual_funcionando = False
        self.thread_auto_funcionando = False
    
    def iniciar(self):
        """
        Inicia o resistor e ventoinha com zero e desliga o sistema e o funcionamento para garantir que será inicializado corretamente.
        Zera os atributos utilitários importantes.
        """
        self.controle_potencia.iniciar()
        self.uart.envia_mensagem('sist_off')
        sleep(0.1)
        self.uart.envia_mensagem('func_off')
        self.uart.envia_mensagem('cntrl_ds')

        self.uart.envia_mensagem('cont_tim', 0)
        self.tempo = 0
        self.tempo_restante = 0
        self.inicia_timer = 0
        self.iter = 0

        print('Sistema iniciado!')

    ##########################################
    # Métodos Controles Potencia/Temperatura #
    ##########################################

    def controle_potencia_funcionamento(self):
        """
        A partir do cálculo do PID, atualiza o sinal de controle e, consequentemente, o controle de potência é ativado.
        """
        if self.ligado == True and self.funcionando == True:
            self.pid.atualiza_referencia(self.temp_ref)
            self.sg_cntrl = self.pid.controle(self.temp_int)
            self.controle_potencia.funcionamento(self.sg_cntrl)
            self.uart.envia_mensagem('sg_cntrl', self.sg_cntrl)

    def controle_temperatura(self):
        """
        Atualiza as temperaturas e vai para a função do funcionamento de controle de potência.
        """
        if self.ligado == True and self.funcionando == True:
            self.att_temperatura_ambiente()

            if self.modo_inicial == "dashboard":

                if self.iter == 0:
                    controleAirFryer.trata_comando_user()
                    self.iter += 1
                
                self.uart.envia_mensagem('temp_ref')
                _, valor = self.uart.recebe_mensagem()
                if type(valor) == float:
                    self.temp_ref = valor
            
            self.att_temperatura_interna()
            
            self.controle_potencia_funcionamento()
            sleep(0.1)
    
    ###############################
    # Métodos Funcionamento Modos #
    ###############################
    
    def modo_dashboard(self):
        """
        Chama funcionamento para o modo Dashboard
        """
        while self.thread_dashboard_funcionando:
            self.executar_modo("Modo Dashboard")
        return

    def modo_automatico(self):
        """
        Funcionamento do modo Encoder/Terminal: Automático 
        O tempo e a temperatura de referência são aquelas relacionadas à opção escolhida.
        """
        if self.opcao_auto == None:
            print('Nenhum modo selecionado!')
            return
        else:
            # Tempo da opção selecionada
            self.tempo = self.opcao_auto[1]
            self.uart.envia_mensagem('cont_tim', self.tempo)
            # Temperatura da opção selecionada
            self.temp_ref = self.opcao_auto[2]
            self.uart.envia_mensagem('sg_refer', self.temp_ref)

        while self.thread_auto_funcionando:
            self.executar_modo("Modo Encoder / Terminal: Automático")
        return

    def modo_manual(self):
        """
        Funcionamento do modo Encoder/Terminal: Manual
        Envia a temperatura e o tempo escolhidos pelo usuário
        """
        self.uart.envia_mensagem('cont_tim', self.tempo)
        self.uart.envia_mensagem('sg_refer', self.temp_ref)

        while self.thread_manual_funcionando:
            self.executar_modo("Modo Encoder / Terminal: Manual")
        return

    def executar_modo(self, modo):
        """
        De 1 em 1 segundo, faz o controle de temperatura, quando a temperatura atinge uma taxa próxima e aceitável da de referência, 
        o timer é ativado e decrescido. O LCD é atualizado a cada vez, passando os parâmetros para utilização.
        O log também é atualizado a cada iteração.
        """
        print()
        print(f'-> {modo}! <-')
        print('Pressione CTRL+C para interromper o funcionamento')
        if modo == "Modo Encoder / Terminal: Automático":
            print(self.opcao_auto[0])

        if self.ligado and self.funcionando:
            self.controle_temperatura()

            if self.inicia_timer == 1:
                self.tempo_restante -= 1
                # print('   -> Tempo Restante (em segundos): ', self.tempo_restante)
                if self.tempo_restante == 0:
                    print('Fim do tempo de aquecimento, desligando!')
                    self.desligar()
                    return

            if self.inicia_timer == 0 and (self.temp_int >= self.temp_ref - 2 and self.temp_int <= self.temp_ref + 2):
                self.tempo_restante = self.tempo * 60
                self.inicia_timer = 1
                # print('   -> Tempo Restante (em segundos): ', self.tempo_restante)

            self.lcd.mostrar_lcd(self.temp_int, self.temp_ref, self.temp_amb, self.tempo_restante, self.modo_encoder)

            cria_log(self.temp_int, self.temp_amb, self.temp_ref, self.sg_cntrl)

        sleep(1)
    
    ###############################
    # Método Inicia Funcionamento #
    ###############################
    
    def inicia_aquecimento(self):
        """
        Caso seja solicitado o funcionamento da AirFryer, chama a thread do tipo de modo.
        Trata interrupção da Thread com CTRL+C ou seu fim com o tempo selecinado.
        """
        if self.ligado == True and self.funcionando == False:
            self.uart.envia_mensagem('func_onn')
            self.funcionando = True
            # print('Botão de funcionando ligado')
            
            # Thread: Dashboard
            if self.modo_inicial == 'dashboard':
                self.thread_dashboard_funcionando = True

                # Modo Manual
                self.uart.envia_mensagem('cntrl_ds')
                
                self.dashboard_thread = Thread(target=self.modo_dashboard)
                self.dashboard_thread.start()
                self.dashboard_thread.join()
                
                if self.thread_dashboard_funcionando == False:
                    return
                
                # Tratamento do CTRL+C da Thread
                try:
                    while True:
                        sleep(10000)
                except KeyboardInterrupt:
                    self.dashboard_thread.join()
                    print('Desligando modo dashboard!')
                    print()
                    self.desligar()
                    return
            
            elif self.modo_inicial == "encoder":

                # Thread: Encoder/Terminal Manual
                if self.modo_encoder == "manual":
                    self.thread_manual_funcionando = True
                
                    # Modo Manual
                    self.uart.envia_mensagem('cntrl_ds')

                    self.manual_thread = Thread(target=self.modo_manual)
                    self.manual_thread.start()
                    self.manual_thread.join()
                
                    if self.thread_manual_funcionando == False:
                        return
                 
                    # Tratamento do CTRL+C da Thread
                    try:
                        while True:
                            sleep(10000)
                    except KeyboardInterrupt:
                        self.thread_manual_funcionando = False
                        self.manual_thread.join()
                        print('Desligando modo manual!')
                        print()
                        self.desligar()
                        return
                    
                # Thread: Encoder/Terminal Automático
                elif self.modo_encoder == "auto":
                    self.thread_auto_funcionando = True
                    
                    # Modo automático
                    self.uart.envia_mensagem('cntrl_tm')
                    
                    self.auto_thread = Thread(target=self.modo_automatico)
                    self.auto_thread.start() 
                    self.auto_thread.join()
                    
                    if self.thread_auto_funcionando == False:
                        return 
                    
                    # Tratamento do CTRL+C da Thread
                    try:
                        while True:
                            sleep(10000)
                    except KeyboardInterrupt:
                        self.thread_auto_funcionando = False
                        self.auto_thread.join()
                        print('Desligando modo automático!')
                        print()
                        self.desligar()
                        return
    
    ########################
    # Métodos Liga/Desliga #
    ########################
                    
    def liga_sistema(self):
        """
        Ativa o sistema (botão de ligado)
        """
        self.uart.envia_mensagem('sist_onn')
        self.ligado = True
        # print('Botão de ligado ativado')
    
    def desliga_sistema(self):
        """
        Desativa o sistema (botão de ligado) e chama o desligamento do aquecimento
        """
        self.uart.envia_mensagem('sist_off')
        self.ligado = False
        print('Botão de ligado desativado')
        self.desliga_aquecimento()
    
    def desliga_aquecimento(self):
        """
        Desativa o funcionamento da AirFryer (botão de funcionamento)
        """
        self.uart.envia_mensagem("func_off")
        self.funcionando = False
        # print('Botão de funcionando desligado')
    
    ######################################
    # Métodos Atualiza Tempo/Temperatura #
    ######################################
    
    def mais_tempo(self):
        """
        O usuário aumentou um minuto no dashboard
        """
        self.tempo += 1
        self.uart.envia_mensagem('cont_tim', self.tempo)
        # print('Tempo aumentado: ', self.tempo)
    
    def menos_tempo(self):
        """
        O usuário diminuiu um minuto no dashboard
        """
        if self.tempo > 0:
            self.tempo -= 1
        elif self.tempo == 0:
            self.tempo = 0
        self.uart.envia_mensagem('cont_tim', self.tempo)
        # print('Tempo diminuido: ', self.tempo)

    def att_temperatura_ambiente(self):
        """
        Atualiza a temperatura ambiente proveniente do sensor
        """
        self.temp_amb = self.bmp.temperatura()
        self.uart.envia_mensagem('temp_amb', self.temp_amb)
        # print(f'Temperatura Ambiente Atualizada: {self.temp_amb}')
        sleep(0.1)

    def att_temperatura_interna(self):
        """
        Atualiza a temperatura interna a partir do recebido do dashboard
        """
        self.uart.envia_mensagem('temp_int')
        # sleep(0.5)
        _, valor = self.uart.recebe_mensagem()
        if valor == None:
            return
        self.temp_int = valor

        # print(f'Temperatura Interna Atualizada: {self.temp_int}')
    
    def att_modo_inicial(self, modo):
        """
        Atualiza o modo inicial (dashboard ou encoder)
        """
        self.modo_inicial = modo
    
    def att_modo_encoder(self, modo):
        """
        Atualiza o modo do encoder (manual ou auto)
        """
        self.modo_encoder = modo
    
    def passar(self):
        """
        Tratar comandos não encontrados
        """
        pass

    #################################
    # Métodos Tratamento e Desligar #
    #################################

    def trata_comando_user(self):
        """
        Tratar comandos do usuário, chama a função referente ao comando enviado.
        """
        sleep(0.1)
        comandos = {
            "liga_air": self.liga_sistema,
            "desliga_": self.desliga_sistema,
            "init_aqc": self.inicia_aquecimento,
            "cancela_": self.desliga_aquecimento,
            "tempo_m+": self.mais_tempo,
            "tempo_m-": self.menos_tempo,
        }

        comando, valor = self.uart.recebe_mensagem()
        if comando == 'com_user' and self.modo_inicial == 'dashboard':
            comandos.get(valor, self.passar)()
        return 

    def desligar(self):
        """
        Desliga os botões da AirFryer, para o resistor e ventoinha e fecha o acesso com bmp e uart.
        Além disso, volta à temperatura ambiente.
        As Threads pararão de funcionar, também.
        """
        self.thread_dashboard_funcionando = False
        self.thread_manual_funcionando = False
        self.thread_auto_funcionando = False

        # Voltar à temperatura ambiente
        self.uart.envia_mensagem('sg_cntrl', -100) 
        sleep(0.1)
        self.uart.envia_mensagem('sg_refer', self.temp_amb)
        sleep(0.1)

        self.uart.envia_mensagem('sist_off')
        self.ligado = False
        sleep(0.1)

        self.uart.envia_mensagem('func_off')
        self.funcionando = False
        sleep(0.1)

        self.uart.envia_mensagem('cntrl_ds')

        self.uart.envia_mensagem('cont_tim', 0)

        # Desligando e fechando dispositivos
        self.controle_potencia.parar()
        self.bmp.fechar()
        self.uart.fechar()
        self.lcd.desliga_lcd()
        
        print('Sistema desligado!')
        print()

from menu import Menu

if __name__ == "__main__":
    controleAirFryer = ControleAirFryer()
    menu = Menu()

    modo = menu.inicia_menu()
    try:
        # Enquanto o modo não for de finalizar
        while modo != 3:

            # Modo Dashboard
            if modo == 1:
                controleAirFryer.iniciar()

                controleAirFryer.att_modo_inicial("dashboard")
                print('----- Modo Dashboard -----')
                print('Selecione suas configurações de pouco em pouco...')
                print('Quando o botão de iniciar e de funcionamento forem ativados, a AirFryer começará a funcionar!')

                # Quando ligar e em funcionamento forem ativados, ele começa o funcionamento
                # Para quando a thread for finalizada
                try:
                    while True:
                        controleAirFryer.uart.envia_mensagem('com_user')
                        controleAirFryer.trata_comando_user()
                        sleep(0.5)
                        if controleAirFryer.thread_dashboard_funcionando == True and controleAirFryer.inicia_timer == 1:
                            break
                except KeyboardInterrupt:
                    controleAirFryer.desligar()
                    pass

            # Modo Encoder / Terminal
            elif modo == 2:
                opcao = menu.menu_encoder()

                controleAirFryer.att_modo_inicial("encoder")

                # Modo Manual
                if opcao == 1:
                    controleAirFryer.iniciar()

                    # Recebe a temperatura e tempo selecionados
                    temperatura, tempo = menu.encoder_manual()

                    controleAirFryer.temp_ref = temperatura
                    controleAirFryer.tempo = tempo

                    # Inicia o funcionamento
                    controleAirFryer.att_modo_encoder("manual")
                    controleAirFryer.liga_sistema()
                    controleAirFryer.inicia_aquecimento()

                # Modo Automático
                elif opcao == 2:
                    controleAirFryer.iniciar()

                    # Recebe a opção selecionada
                    opcao = menu.encoder_automatico()
                    
                    controleAirFryer.opcao_auto = opcao

                    # Inicia o funcionamento
                    controleAirFryer.att_modo_encoder("auto")
                    controleAirFryer.liga_sistema()
                    controleAirFryer.inicia_aquecimento()
            
            modo = menu.inicia_menu()
        
        print('Finalizando o sistema!')

    # Tratamento CTRL+C (desliga sistema)
    except KeyboardInterrupt:
        try:
            controleAirFryer.desligar()
        except Exception:
            pass
        finally:
            print("Finalizando o programa!")
            exit()