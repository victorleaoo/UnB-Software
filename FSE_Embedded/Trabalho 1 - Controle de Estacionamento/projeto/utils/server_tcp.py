import socket
from utils.server_config import *
import datetime

import os

class TCPServer:
    """
    Classe que gerencia o servidor central por meio de TCP/IP (faz as conexões, recebe e manda mensagem)
    """
    def __init__(self, host, port_andar1, port_andar2):
        """
        Recebe:
        - o host do servidor central
        - a porta do andar 1
        - a porta do andar 2
        Inicializa um socket para cada andar (socket_andar1 e socket_andar2)

        Armazena:
        - quantidade total no estacionamento e em cada andar
        - distribuição de vagas por andar
        - horarios de entrada e saida
        """
        self.host = host
        self.port_andar1 = port_andar1
        self.port_andar2 = port_andar2

        self.quantidade_total = 0
        self.quantidade_andar1 = 0
        self.quantidade_andar2 = 0

        self.distribuicao_andar1 = "1 -> 0\n2 -> 0\n3 -> 0\n4 -> 0\n5 -> 0\n6 -> 0\n7 -> 0\n8 -> 0\n"
        self.distribuicao_andar2 = "1 -> 0\n2 -> 0\n3 -> 0\n4 -> 0\n5 -> 0\n6 -> 0\n7 -> 0\n8 -> 0\n"

        self.lista_horarios = []
        self.valor_total = 0.0

        self.andar1_fechado = 0
        self.andar2_fechado = 0

        self.socket_andar1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket_andar1.bind((self.host, self.port_andar1))
        self.socket_andar1.listen()

        self.socket_andar2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket_andar2.bind((self.host, self.port_andar2))
        self.socket_andar2.listen()

    def accept_connection(self, port):
        """
        Aceita a conexão de um cliente (andar) específico, caso seja tentado uma porta que não foi passada, traz um erro.
        """
        if port == self.port_andar1:
            client_socket, client_address = self.socket_andar1.accept()
        elif port == self.port_andar2:
            client_socket, client_address = self.socket_andar2.accept()
        else:
            raise ValueError("Porta inválida")

        return client_socket, client_address
    
    def trata_mensagem(self, data):
        """
        Trata as variáveis dependendo da mensagem recebida dos andares.
        """
        if data.decode() == "CATRACA: +1":
            self.lista_horarios.append(datetime.datetime.now())

            self.quantidade_total += 1
            self.quantidade_andar1 += 1
        elif data.decode() == "CATRACA: -1":
            self.valor_total += ((int(abs((datetime.datetime.now() - self.lista_horarios.pop()).total_seconds() / 60))) * VALOR_TAXA)

            self.quantidade_total -= 1
            self.quantidade_andar1 -= 1
        elif data.decode() == "PASSAGEM: SUBIU":
            self.quantidade_andar2 += 1
            self.quantidade_andar1 -= 1
        elif data.decode() == "PASSAGEM: DESCEU":
            self.quantidade_andar2 -= 1
            self.quantidade_andar1 += 1
        elif "VAGAS ANDAR1:" in data.decode():
            self.distribuicao_andar1 = data.decode()
        elif "VAGAS ANDAR2:" in data.decode():
            self.distribuicao_andar2 = data.decode()

    def manipula_andar(self, client_socket, address, andar):
        """
        Apresenta informações referentes ao estacionamento.
        Recebe e envia as mensagens do andar especificado (1 ou 2).
        """
        while True:
            print('\n|                    ESTACIONAMENTO                    |')
            print('| Quantidade total de carros no estacionamento: ' + str(self.quantidade_total) + " |")

            # Se a quantidade total no estacionamento for igual a 16, ele é fechado
            if self.andar1_fechado == 1:
                print('!!!!!ESTACIONAMENTO FECHADO!!!!!')
            if self.quantidade_total == 16:
                print('!!!!! ESTACIONAMENTO LOTADO !!!!!\n')
                self.andar1_fechado=1
                msg_lotado = "ANDAR1: LOTADO"
                client_socket.send(msg_lotado.encode())

            # Se o estacionamento é dado como fechado, mas sua quantidade total não é 16, ele deve ser aberto
            if (self.andar1_fechado == 1) and (self.quantidade_total != 16):
                msg = "ANDAR1: ABRIR"
                client_socket.send(msg.encode())

            print('| Quantidade total de carros no Andar 1: ' + str(self.quantidade_andar1) + "    |")
            print('| Quantidade total de carros no Andar 2: ' + str(self.quantidade_andar2) + "    |")

            # Se a quantidade total no andar 2 é 8, ele é fechado
            if self.andar2_fechado == 1:
                print('!!!!!ANDAR 2 FECHADO!!!!!')
            if self.quantidade_andar2 == 8:
                print('!!!!!ANDAR 2 LOTADO!!!!!\n')
                self.andar2_fechado=1
                msg_lotado = "ANDAR2: LOTADO"
                client_socket.send(msg_lotado.encode())
            
            # Se o andar 2 é dado como fechado, mas sua quantidade total não é 8, ele deve ser aberto
            if (self.andar2_fechado == 1) and (self.quantidade_andar2 != 8):
                msg = "ANDAR2: ABRIR"
                client_socket.send(msg.encode())

            print('| Valor total pago no estacionamento: R$ {:.2f}'.format(self.valor_total) + " |")

            print('| Vagas Andar 1: ')
            print(self.distribuicao_andar1)
            print('| Vagas Andar 2: ')
            print(self.distribuicao_andar2)

            # Tentativa de receber input do usuário
            # comando = input("Digite algum comando (1 para fechar/abrir o estacionamento todo OU 2 para fechar/abrir o andar 2): ")
            # if comando == "1":
            #     if self.andar1_fechado == 1:
            #         msg = "ANDAR1: ABRIR"
            #     else:
            #         msg = "ANDAR1: LOTADO"
            #     client_socket.send(msg.encode())
            # elif comando == "2":
            #     if self.andar2_fechado == 1:
            #         msg = "ANDAR2: ABRIR"
            #     else:
            #         msg = "ANDAR2: LOTADO"
            #     client_socket.send(msg_lotado.encode())
            # else:
            #     print('Comando inválido! Coloque 1 ou 2!\n')

            try:
                # Recebe a mensagem do cliente
                data = client_socket.recv(BUFFER_SIZE)
                self.trata_mensagem(data)
            except:
                # Encerra a conexão em caso de erro na recepção da mensagem
                print(f'Erro ao receber mensagem do andar {andar} {address}')
                client_socket.close()
                break