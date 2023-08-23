import time
import RPi.GPIO as GPIO
import os

class Vaga:
    """
    Classe que gerencia as vagas de um andar
    """
    def __init__(self, endereco_01, endereco_02, endereco_03, sensor_de_vaga, andar, andar_tcp):
        """
        Recebe o endereçamento dos pinos (e faz o setup) da GPIO para:
        - cada um dos endereços para ver cada uma das vagas = ENDERECO_01, ENDERECO_02, ENDERECO_03 = SAÍDA
        - sensor de vagas =  = ENTRADA
        - andar (saber se é o primeiro ou segundo)
        - tcp do andar para mandar mensagem

        - um dicionário para saber quais vagas estão sendo usadas, inicializado com todas 0
        
        Os pinos de saída são setados como LOW
        """
        self.ENDERECO_01 = endereco_01
        self.ENDERECO_02 = endereco_02
        self.ENDERECO_03 = endereco_03
        self.SENSOR_DE_VAGA = sensor_de_vaga
        
        self.vagas_distribuicao = {
            '0': 0,
            '1': 0,
            '2': 0,
            '3': 0,
            '4': 0,
            '5': 0,
            '6': 0,
            '7': 0
        }

        self.andar = andar
        self.andar_tcp = andar_tcp

        # Setup dos pinos
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.ENDERECO_01, GPIO.OUT)
        GPIO.setup(self.ENDERECO_02, GPIO.OUT)
        GPIO.setup(self.ENDERECO_03, GPIO.OUT)
        GPIO.setup(self.SENSOR_DE_VAGA, GPIO.IN)

        # Inicializa os de saídas como LOW
        GPIO.output(self.ENDERECO_01, GPIO.LOW)
        GPIO.output(self.ENDERECO_02, GPIO.LOW)
        GPIO.output(self.ENDERECO_03, GPIO.LOW)
    
    def vagas_string(self):
        """
        Função que lê o dicionário de vagas e retorna uma string formatada para o servidor central
        """
        resultado = ""
        for chave, valor in self.vagas_distribuicao.items():
            resultado += f'{chave} -> {valor}\n'
        linhas = resultado.split('\n')
        primeira = linhas[0]
        linhas[0] = ""
        linhas.append("8" + primeira[1:]) 
        novo_texto = '\n'.join(linhas).strip().replace('\n\n', '\n')
        return novo_texto

    def testar_vagas(self):
        """
        Roda um loop da vaga de endereço 0 (000) até a vaga de endereço 7 (111) e verifica o seu sensor. Caso a vaga tenha mudado (vaga ou não), envia uma mensagem para o servidor central com a nova distribuição.
        Tem um sleep de 0.5 segundos entre cada uma das vagas.
        """
        while True:
            for i in range(8):
                sensor = 0
                # Converter o número da vaga em um valor binário em formato string
                endereco_bin = "{0:b}".format(i).zfill(3)

                # Configurar os pinos de endereço para a vaga atual
                GPIO.output(self.ENDERECO_01, int(endereco_bin[2]))
                GPIO.output(self.ENDERECO_02, int(endereco_bin[1]))
                GPIO.output(self.ENDERECO_03, int(endereco_bin[0]))

                # Verificar o sinal do sensor da vaga e atualiza seu valor no dicionário
                if GPIO.input(self.SENSOR_DE_VAGA):
                    if self.vagas_distribuicao[str(i)] == 0:
                        self.vagas_distribuicao[str(i)] = 1
                        vagas_andar = "VAGAS ANDAR" + str(self.andar) + ": \n" + self.vagas_string()
                        self.andar_tcp.send_message(vagas_andar)
                    
                    sensor = 1

                if((self.vagas_distribuicao[str(i)] == 1) and (sensor == 0)):
                    self.vagas_distribuicao[str(i)] = 0
                    vagas_andar = "VAGAS ANDAR" + str(self.andar) + ": \n" + self.vagas_string()
                    self.andar_tcp.send_message(vagas_andar)

                time.sleep(0.5)

            time.sleep(1)