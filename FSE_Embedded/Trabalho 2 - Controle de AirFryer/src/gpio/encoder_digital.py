import RPi.GPIO as GPIO
from i2c.lcd import LCD

from utils.componentes import ENCODER_CLK, ENCODER_DT, ENCODER_SW

class EncoderDigital:
    """
    Classe responsável por implementar o Encoder Digital e suas utilizações juntamente com o LCD.
    Implementa apenas o modo manual.
    """
    def __init__(self):
        self.lcd = LCD()
        
        # Salvando a iteração, temperatura e tempo iniciais
        self.iter = 0
        self.temp = 30.0
        self.tempo = 0

        # Setando os pinos e os estados iniciais
        GPIO.setmode(GPIO.BCM)

        GPIO.setup(ENCODER_CLK, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setup(ENCODER_SW, GPIO.IN, pull_up_down=GPIO.PUD_UP)
        GPIO.setup(ENCODER_DT, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
    
        self.estadoClock = GPIO.input(ENCODER_CLK)
        self.estadoDT = GPIO.input(ENCODER_DT)
        self.estadoSWInit = GPIO.input(ENCODER_SW)

    def monitora_encoder(self):
        """
        Monitora os botões do encoder e trata o que for utilizado (girar ou botão)
        """
        while True:

            # Sentido horário
            if self.estadoClock == 1 and self.estadoDT == 0:

                # Primeira iteração apenas printa Manual
                if self.iter == 0:
                    self.lcd.print_encoder('Manual')

                # Segunda iteração aumenta temperatura
                if self.iter == 1:
                    self.temp += 5.0
                    self.lcd.print_encoder('Temp: ', round(self.temp,1))

                # Segunda iteração aumenta tempo
                if self.iter == 2:
                    self.temp += 1
                    self.lcd.print_encoder('Tempo: ', self.tempo)

            # Sentido anti-horário
            if self.estadoClock == 0 and self.estadoDT == 1:

                # Primeira iteração apenas printa Manual
                if self.iter == 0:
                    self.lcd.print_encoder('Manual')
                
                # Segunda iteração diminui temperatura
                if self.iter == 1:
                    if self.temp >= 35.0:
                        self.temp -= 5
                        self.lcd.print_encoder('Temp: ', round(self.temp,1))

                # Segunda iteração diminui tempo
                if self.iter == 1:
                    if self.temp >= 0:
                        self.temp -= 1
                        self.lcd.print_encoder('Tempo: ', self.tempo)

            # Botão
            if self.estadoSWInit == 0:
                # Primeiro clique passa para a temperatura
                if self.iter == 0:
                    self.iter = 1
                    self.lcd.print_encoder('Temp: ', round(self.temp,1))
                
                # Segundo clique passa para o tempo
                if self.iter == 1:
                    self.iter = 2
                    self.lcd.print_encoder('Tempo: ', self.tempo)

                # Terceiro clique inicia
                if self.iter == 2:
                    self.lcd.print_encoder('Inicio')

    def desligar(self):
        """
        Limpa a GPIO
        """
        GPIO.cleanup()