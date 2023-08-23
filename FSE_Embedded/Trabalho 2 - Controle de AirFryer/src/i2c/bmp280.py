from bmp280 import BMP280
from smbus import SMBus

from i2c.utils.config import END_BMP280

class BMP:
    """
    Classe responsável por implementar o sensor BMP280
    """
    def __init__(self, address=END_BMP280):
        """
        Inicializa com o endereço fornecido
        """
        self.address = address
        self.bus = SMBus(1)
        self.bmp280 = BMP280(i2c_dev=self.bus)
    
    def temperatura(self):
        """
        Retorna a temperatura do sensor
        """
        temperatura = self.bmp280.get_temperature()
        return round(temperatura, 2)
    
    def fechar(self):
        """
        Fecha a conexão
        """
        self.bus.close()