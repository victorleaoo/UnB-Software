import RPi.GPIO as GPIO
import time
import socket

class SensorPassagem:
    """
    Classe que gerencia o sensor de passagem para o segundo andar
    """
    def __init__(self, sensor_de_passagem_1, sensor_de_passagem_2, andar_tcp):
        """
        Recebe o endereçamento dos pinos (e faz o setup) da GPIO para:
        - sensor_de_passagem_1 = SENSOR_DE_PASSAGEM_1 = ENTRADA
        - sensor_de_passagem_2 = SENSOR_DE_PASSAGEM_2 = ENTRADA
        - tcp do andar para mandar mensagem
        
        São adicionados detectadores de evento para saber, ao houver um pulso, se o carro subiu ou desceu
        """
        self.SENSOR_DE_PASSAGEM_1 = sensor_de_passagem_1
        self.SENSOR_DE_PASSAGEM_2 = sensor_de_passagem_2
        self.andar_tcp = andar_tcp
        self.ordem_de_acionamento = []

        self.socket = None

        # Setup dos pinos
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.SENSOR_DE_PASSAGEM_1, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setup(self.SENSOR_DE_PASSAGEM_2, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

        # Espera a detecção de um evento (subir ou descer dos pinos de passagens)
        GPIO.add_event_detect(self.SENSOR_DE_PASSAGEM_1, GPIO.BOTH, callback=self._sensor_1_callback)
        GPIO.add_event_detect(self.SENSOR_DE_PASSAGEM_2, GPIO.BOTH, callback=self._sensor_2_callback)

    def _sensor_1_callback(self, pin):
        """
        Função callback para o sensor de passagem 1, detecta a borda de subida e descida do sinal do sensor
        Adiciona na lista de ordem de acionamento, usada posteriormente para entender se o carro subiu ou desceu
        """
        if GPIO.input(self.SENSOR_DE_PASSAGEM_1):
            self.ordem_de_acionamento.append(1)
            
    def _sensor_2_callback(self, pin):
        """
        Função callback para o sensor de passagem 2, detecta a borda de subida e descida do sinal do sensor
        Adiciona na lista de ordem de acionamento, usada posteriormente para entender se o carro subiu ou desceu
        """
        if GPIO.input(self.SENSOR_DE_PASSAGEM_2):
            self.ordem_de_acionamento.append(2)

    def monitorar_sensor(self):
        """
        Função que roda em loop e detecta quando houveram acionamento dos dois sensores
        Manda mensagem para o servidor central avisando se um carro subiu ou desceu do segundo andar
        """
        while True:
            if len(self.ordem_de_acionamento) == 2:
                if self.ordem_de_acionamento == [1, 2]:
                    mensagem = "PASSAGEM: SUBIU"
                    print("PASSAGEM: SUBIU")
                    self.andar_tcp.send_message(mensagem)
                elif self.ordem_de_acionamento == [2, 1]:
                    mensagem = "PASSAGEM: DESCEU"
                    print("PASSAGEM: DESCEU")
                    self.andar_tcp.send_message(mensagem)
                
                self.ordem_de_acionamento = []
            
            time.sleep(0.1)