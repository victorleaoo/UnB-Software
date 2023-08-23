import RPi.GPIO as GPIO
import time
import socket

class Cancela:
    """
    Classe que gerencia a cancela (e seus sensores) no momento de entrada/saída de um carro
    """
    def __init__(self, sensor_abertura_pin, motor_pin, sensor_fechamento_pin, andar_tcp, tipo):
        """
        Recebe o endereçamento dos pinos (e faz o setup) da GPIO para:
        - sensor_abertura_pin = SENSOR_ABERTURA_CANCELA_ENTRADA ou SENSOR_ABERTURA_CANCELA_SAIDA = ENTRADA
        - motor_pin = MOTOR_CANCELA_ENTRADA ou MOTOR_CANCELA_SAIDA = SAÍDA
        - sensor_fechamento_pin = SENSOR_FECHAMENTO_CANCELA_ENTRADA ou SENSOR_FECHAMENTO_CANCELA_SAIDA = ENTRADA
        - tcp do andar para mandar mensagem
        - tipo 0 de entrada e tipo 1 de saida
        
        Os pinos de saída são setados como LOW
        """
        self.sensor_abertura_pin = sensor_abertura_pin
        self.motor_pin = motor_pin
        self.sensor_fechamento_pin = sensor_fechamento_pin
        self.andar_tcp = andar_tcp
        self.tipo = tipo

        self.socket = None

        # Setup dos pinos
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.sensor_abertura_pin, GPIO.IN)
        GPIO.setup(self.motor_pin, GPIO.OUT)
        GPIO.setup(self.sensor_fechamento_pin, GPIO.IN)

        # Inicializa o de saída como LOW
        GPIO.output(self.motor_pin, GPIO.LOW)

    def abrir_cancela(self):
        """
        Abre a cancela (ativa o motor para HIGH)
        """
        GPIO.output(self.motor_pin, GPIO.HIGH)

    def fechar_cancela(self):
        """
        Fecha a cancela (volta o motor para LOW) e avisa o servidor central se chegou ou saiu um carro do estacionamento
        """
        if self.tipo == 0:
            mensagem = "CATRACA: +1"
        elif self.tipo == 1:
            mensagem = "CATRACA: -1"

        self.andar_tcp.send_message(mensagem)
        
        time.sleep(0.5)

        GPIO.output(self.motor_pin, GPIO.LOW)

    def verifica_cancela(self):
        """
        Verifica de tempo em tempo se chegou um novo carro, caso sim, abre a cancela.
        Após abrir a cancela, espera o sinal de que o carro já passou e, então, fecha a cancela.
        """
        while True:
            while not GPIO.input(self.sensor_abertura_pin):
                time.sleep(0.1)

            self.abrir_cancela()

            while not GPIO.input(self.sensor_fechamento_pin):
                time.sleep(0.1)

            self.fechar_cancela()

            time.sleep(1)