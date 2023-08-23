class Menu:
    """
    Classe referente ao menu, com diferentes opções de menu
    """
    def __init__(self):
        """
        Inicializa com as opções automáticas existentes
        """
        self.opcoes_automatico = {
            1: ['Frango: 7 min e 60°C', 7, 60.0],
            2: ['Pão de Queijo: 2 min e 30°C', 2, 30.0],
            3: ['Batata Frita: 5 min e 50°C', 5, 50.0],
        }

    def inicia_menu(self):
        """
        Menu inicial para escolha de modo (Dashboard ou Encoder)
        """
        print('----- Bem vindo ao Controlador de AirFryer -----')
        print('Há dois modos disponíveis: ')
        print('1 - Dashboard')
        print('2 - Encoder Digital / Terminal')
        print('3 - Finalizar sistema')

        # Aguarda um modo válido
        modo = self.selecionar_opcao([1, 2, 3], 'Escolha um modo válida (1 para Dashboard, 2 para Encoder Digital ou 3 para finalizar)')
        
        print()

        return modo

    def menu_encoder(self):
        """
        Menu inicial do Encoder para escolha de modo (Manual ou Automático)
        """
        print('----- Modo Encoder / Terminal -----')
        print()
        print('Para o encoder, há duas opções disponíveis: ')
        print('1 - Manual')
        print('2 - Automático')

        opcao = self.selecionar_opcao([1, 2], 'Escolha uma opção válida (1 para Manual ou 2 para Automático)')

        print()
        
        return opcao

    def encoder_manual(self):
        """
        Menu inicial do Encoder em modo Manual (pede temperatura e tempo)
        """
        print('----- Modo Encoder / Terminal: Manual -----')
        print()
        print('Para o modo manual, é necessário que você selecione a temperatura e o tempo em minutos')
        while True:
            try:
                temperatura = float(input("Informe a temperatura: "))
                break
            except ValueError:
                print("Digite um número válido")
                continue
        while True:
            try:
                tempo = int(input("Informe o tempo em minutos: "))
                break
            except ValueError:
                print("Digite um número válido")
                continue
        print()
        print(f'Você escolhe a seguinte temperatura: {temperatura} e tempo: {tempo}')
        return temperatura, tempo

    def encoder_automatico(self):
        """
        Menu inicial do Encoder em modo Automático (pede opção)
        """
        print('----- Modo Encoder / Terminal: Automático -----')
        print()
        print('Para o modo automático, há as seguintes opções, escolha uma delas: ')
        self.imprimir_opcoes_automatico()
        print()

        opcao = self.selecionar_opcao(list(range(1, len(self.opcoes_automatico) + 1)), '', automatico=1)

        print('Você selecionou a seguinte opção: ', self.opcoes_automatico[opcao][0])
        return self.opcoes_automatico[opcao]

    #######################
    # Funções Utilitárias #
    #######################

    def selecionar_opcao(self, opcoes, string_validas, automatico=0):
        """
        Função para receber qual opção o usuário deseja
        """
        while True:
            try:
                opcao = int(input('Qual modo gostaria de acessar? '))
                if opcao in opcoes:
                    break
                raise ValueError
            except ValueError:
                if automatico == 1:
                    print('Escolha uma opção válida entre as seguintes: ')
                    self.imprimir_opcoes_automatico()
                    print()
                    continue
                print(string_validas)
                print()
                continue
        return opcao


    def imprimir_opcoes_automatico(self):
        """
        Imprime as opções automáticas
        """
        for chave, opcao in self.opcoes_automatico.items():
            print(f'{chave} - {opcao[0]}')