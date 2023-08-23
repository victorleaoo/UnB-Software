import socket
import RPi.GPIO as GPIO
import time

class Andar_TCP():
    """
    Classe que gerencia a conexão (envio e recebimento de mensagem dos andares) com o servidor central
    """
    def __init__(self, host, port, sinal_lotado_andar1, sinal_lotado_andar2, buffer_size):
        """
        Recebe:
        - o host do servidor central
        - a porta do andar
        - o tamanho do buffer
        - sinais de lotado dos andares: SINAL_DE_LOTADO_FECHADO_ANDAR1 e SINAL_DE_LOTADO_FECHADO_ANDAR2 = SAIDA

        Os pinos são setados como LOW
        """
        self.host = host
        self.port = port
        self.buffer_size = buffer_size

        self.sinal_lotado_andar1 = sinal_lotado_andar1
        self.sinal_lotado_andar2 = sinal_lotado_andar2

        # Setup dos pinos
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.sinal_lotado_andar1, GPIO.OUT)
        GPIO.setup(self.sinal_lotado_andar2, GPIO.OUT)

        # Inicializa o de saída como LOW
        GPIO.output(self.sinal_lotado_andar1, GPIO.LOW)
        GPIO.output(self.sinal_lotado_andar2, GPIO.LOW)

        # Tenta se conectar ao servidor
        while True:
            try:
                self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.socket.connect((self.host, self.port))
                break
            except ConnectionRefusedError:
                print(f"Conexão com o servidor central recusada. Tentando novamente em 5 segundos...")
                time.sleep(5)

    def send_message(self, message):
        """
        Função para enviar uma mensagem ao servidor central.
        """
        self.socket.sendall(message.encode())

    def receive_message(self):
        """
        Função para tratar mensagens recebidas pelo servidor central:
        - Abrir ou fechar os andares 1 ou 2 dependendo da mensagem
        """
        while True:
            message = self.socket.recv(self.buffer_size)
            
            if message.decode() == "ANDAR2: LOTADO":
                GPIO.output(self.sinal_lotado_andar2, GPIO.HIGH)
            elif message.decode() == "ANDAR2: ABRIR":
                GPIO.output(self.sinal_lotado_andar2, GPIO.LOW)
            elif message.decode() == "ANDAR1: LOTADO":
                GPIO.output(self.sinal_lotado_andar1, GPIO.HIGH)
            elif message.decode() == "ANDAR1: ABRIR":
                GPIO.output(self.sinal_lotado_andar1, GPIO.LOW)
            
    def close_connection(self):
        """
        Função para fechar a conexão com o servidor central.
        """
        self.socket.close()