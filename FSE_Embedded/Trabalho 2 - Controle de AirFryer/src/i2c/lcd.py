import i2c.driver.RPi_I2C_driver as RPi_I2C_driver

class LCD:
    """
    Classe responsável por implementar o LCD
    """
    def __init__(self):
        """
        Inicializa o LCD
        """
        self.lcd = RPi_I2C_driver.lcd()

    def mostrar_lcd(self, temp_int, temp_ref, temp_amb, tempo, modo):
        """
        Mostra o modo, as temperaturas importantes e tempo no LCD
        """
        self.lcd.lcd_clear()
        
        if modo == 'auto':
            lcd_print = f"A| I:{str(round(temp_int, 1))} R:{str(round(temp_ref, 1))}"
        elif modo == 'manual':
            lcd_print = f"M| I:{str(round(temp_int, 1))} R:{str(round(temp_ref, 1))}"

        self.lcd.lcd_display_string(lcd_print, 1)
        self.lcd.lcd_display_string(f"A: {str(round(temp_amb, 1))} T(s):{tempo}", 2)

    def print_encoder(self, texto):
        """
        Imprime um texto na primeira linha do LCD
        """
        self.lcd.lcd_display_string(texto, 1)
    
    def desliga_lcd(self):
        """
        Limpa o LCD
        """
        self.lcd.lcd_clear()