import RPi.GPIO as GPIO

from gpio.utils.componentes import RESISTOR, VENTOINHA, FREQUENCIA

class ControlePotencia:
    """
    Classe responsável por implementar o controlador de potência (Resistor e Ventoinha)
    Implementa por PWM
    """
    def __init__(self, resistor_pin=RESISTOR, fan_pin=VENTOINHA):
        """
        Inicializa os pinos da GPIO com frequência 1200 (pode ser alterada para teste)
        """
        self.resistor_pin = resistor_pin
        self.fan_pin = fan_pin

        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.resistor_pin, GPIO.OUT)
        GPIO.setup(self.fan_pin, GPIO.OUT)

        self.resistor_pwm = GPIO.PWM(self.resistor_pin, FREQUENCIA)
        self.fan_pwm = GPIO.PWM(self.fan_pin, FREQUENCIA)
    
    def iniciar(self):
        """
        Inicia ambos com 0%
        """
        self.resistor_pwm.start(0)
        self.fan_pwm.start(0)

    def muda_resistor_dc(self, duty_cicle):
        """
        Muda a % de funcionamento do resistor
        """
        self.resistor_pwm.ChangeDutyCycle(duty_cicle)

    def muda_fan_dc(self, duty_cicle):
        """
        Muda a % de funcionamento da ventoinha
        """
        self.fan_pwm.ChangeDutyCycle(duty_cicle)

    def funcionamento(self, sg_cntrl):
        """
        Dependendo do sinal de controle (positivo ou negativo) muda o duty cycle do resistor ou da ventoinha
        """
        if sg_cntrl > 0:
            self.muda_resistor_dc(sg_cntrl)
            self.muda_fan_dc(0)
        else:
            self.muda_resistor_dc(0)
            self.muda_fan_dc(abs(sg_cntrl))

    def parar(self):
        """
        Para o funcionamento de ambos e limpa a GPIO
        """
        self.resistor_pwm.stop()
        self.fan_pwm.stop()
        GPIO.cleanup()