class PID:
    """
    Classe responsável pelo PID do projeto 
    Possui os métodos para controle e atualizar a referencia, caso necessário
    """
    def __init__(self, kp=30.0, ki=0.2, kd=400.0, t=1.0):
        self.kp = kp  
        self.ki = ki  
        self.kd = kd  
        self.t = t    
        self.referencia = 0.0
        self.erro_total = 0.0
        self.erro_anterior = 0.0
        self.sinal_de_controle_MAX = 100.0
        self.sinal_de_controle_MIN = -100.0

    def atualiza_referencia(self, referencia):
        """
        Atualiza o valor de referência do controlador PID.
        """
        self.referencia = referencia

    def controle(self, saida_medida):
        """
        Realiza o cálculo do controle PID para obter o sinal de controle.
        """
        erro = self.referencia - saida_medida

        self.erro_total += erro

        if self.erro_total >= self.sinal_de_controle_MAX:
            self.erro_total = self.sinal_de_controle_MAX
        elif self.erro_total <= self.sinal_de_controle_MIN:
            self.erro_total = self.sinal_de_controle_MIN

        delta_error = erro - self.erro_anterior

        sinal_de_controle = (
            (self.kp * erro)
            + (self.ki * self.t) * self.erro_total
            + (self.kd / self.t) * delta_error
        )

        if sinal_de_controle >= self.sinal_de_controle_MAX:
            sinal_de_controle = self.sinal_de_controle_MAX
        elif sinal_de_controle <= self.sinal_de_controle_MIN:
            sinal_de_controle = self.sinal_de_controle_MIN
            
        # Caso o valor de saída do PID esteja entre 0 e -40%, a ventoinha deverá ser acionada com 40% de sua capacidade.
        if sinal_de_controle < 0 and sinal_de_controle > -40:
            sinal_de_controle = -40

        self.erro_anterior = erro

        return int(sinal_de_controle)
