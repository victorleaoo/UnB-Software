# Conexão Serial UART
PORT_UART = "/dev/serial0"
BAUDRATE = 9600

# matricula = [8, 3, 6, 7]

# Comandos via UART
codigos_gerais = {
    "temp_int": [0x01, 0x23, 0xC1, 8, 3, 6, 7], # Solicita Temperatura Interna
    "temp_ref": [0x01, 0x23, 0xC2, 8, 3, 6, 7], # Solicita Temperatura de Referência
    "com_user": [0x01, 0x23, 0xC3, 8, 3, 6, 7], # Lê comandos do usuário
    "sg_cntrl": [0x01, 0x16, 0xD1, 8, 3, 6, 7], # Envia sinal de controle Int (4 bytes)
    "sg_refer": [0x01, 0x16, 0xD2, 8, 3, 6, 7], # Envia sinal de Referência Float (4 bytes)
    "sist_onn": [0x01, 0x16, 0xD3, 8, 3, 6, 7, 1], # Envia Estado do Sistema (Ligado = 1) - (4 bytes)
    "sist_off": [0x01, 0x16, 0xD3, 8, 3, 6, 7, 0], # Envia Estado do Sistema (Desligado = 0) - (4 bytes)
    "cntrl_ds": [0x01, 0x16, 0xD4, 8, 3, 6, 7, 0], # Modo de Controle da Temperatura de referência (Dashboard = 0) (4 bytes)
    "cntrl_tm": [0x01, 0x16, 0xD4, 8, 3, 6, 7, 1], # Modo de Controle da Temperatura de referência (Automático = 1) (4 bytes)
    "func_onn": [0x01, 0x16, 0xD5, 8, 3, 6, 7, 1], # Envia Estado de Funcionamento (Funcionando = 1) (4 bytes)
    "func_off": [0x01, 0x16, 0xD5, 8, 3, 6, 7, 0], # Envia Estado de Funcionamento (Parado = 0)) (4 bytes)
    "temp_amb": [0x01, 0x16, 0xD6, 8, 3, 6, 7], # Envia Temperatura Ambiente (Float)) (4 bytes)
    "cont_tim": [0x01, 0x16, 0xD7, 8, 3, 6, 7], # Envia Contador de Tempo (usado no modo de pré-programação) (4 bytes)
    "str_lcdd": [0x01, 0x16, 0xD8, 8, 3, 6, 7], # Envia String do Display LCD para o Dashboard (1 byte: tamanho da string + N bytes da String)
}

comandos_usuario = {
    0x01: "liga_air", # Liga a AirFryer
    0x02: "desliga_", # Desliga a AirFryer
    0x03: "init_aqc", # Inicia aquecimento
    0x04: "cancela_", # Cancela processo
    0x05: "tempo_m+", # Tempo + : adiciona 1 minuto ao timer
    0x06: "tempo_m-", # Tempo - : adiciona 1 minuto ao timer
    0x07: "menu_ali", # Menu : aciona o modo de alimentos pré-programados
}

# Receber mensagens de retorno
mensagens_retorno = {
    0xC1: "temp_int", # Retorno Temperatura Interna 
    0xC2: "temp_ref", # Retorno Temperatura Referência
    0xC3: "com_user", # Retorno Comandos Usuário
}