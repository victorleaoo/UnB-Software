import serial
from time import sleep

from uart.modbus import codifica_mensagem, decodifica_mensagem
from uart.utils.config import PORT_UART, BAUDRATE

class Uart:
    """
    Classe responsável por se comunicar com a UART
    Faz a comunicação usando a biblioteca Serial e com os métodos write e read
    """
    def __init__(self, port=PORT_UART, baudrate=BAUDRATE):
        self.port = port
        self.baudrate = baudrate
        self.conectado = False

    def conexao(self):
        """
        Método que verifica e abre a conexão com a UART
        Caso ocorra alguma falha, ela será exibida
        """
        if self.conectado == False:
            try:
                self.serial = serial.Serial(self.port, self.baudrate)
                self.conectado = True
            except serial.SerialException as e:
                print('Falha ao estabelecer conexão UART:', str(e))
    
    def envia_mensagem(self, message, value=None):
        """
        Caso esteja conectado, codifica uma mensagem por meio do MODBUS e CRC e, então, a escreve na porta serial
        """
        self.conexao()  # Caso não esteja conectado, tenta a conexão.
        if self.conectado:
            msg = codifica_mensagem(message, value)
            if msg is not None:
                self.serial.write(msg)
            else:
                raise Exception('Erro na codificação da mensagem!')
        else:
            raise Exception('Não conectado e conexão com erro!')

    def recebe_mensagem(self):
        """
        Caso esteja conectado, lê os bytes na porta serial e decodifica a mensagem
        """
        self.conexao()  # Caso não esteja conectado, tenta a conexão.
        if self.conectado:
            sleep(0.1)
            try:
                buffer = self.serial.read(9)
                mensagem, valor = decodifica_mensagem(buffer)
                self.serial.reset_input_buffer()
                return mensagem, valor
            except serial.SerialException as e:
                raise Exception('Erro ao receber mensagem:', str(e))
        else:
            raise Exception('Não conectado e conexão com erro!')

    def fechar(self):
        """
        Caso haja uma conexão e queira, fecha-se ela
        """
        if self.conectado == True:
            self.serial.close()
            self.conectado = False