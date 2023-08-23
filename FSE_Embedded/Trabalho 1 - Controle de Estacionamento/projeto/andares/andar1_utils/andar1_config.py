# Conexão TCP/IP
HOST = 'localhost'  # Endereço do servidor
PORT_ANDAR1 = 10911  # Porta do servidor do andar 1
BUFFER_SIZE = 1024  # Tamanho do buffer de recebimento de mensagens

# Pinos

## Cancela Entrada
SENSOR_ABERTURA_CANCELA_ENTRADA = 23 # Sensor que um carro chegou
MOTOR_CANCELA_ENTRADA = 10 # Cancela de entrada
SENSOR_FECHAMENTO_CANCELA_ENTRADA = 24 # Sensor que um carro já passou

## Cancela Saída
SENSOR_ABERTURA_CANCELA_SAIDA = 25 # Sensor que um carro quer sair
MOTOR_CANCELA_SAIDA = 17 # Cancela de saída
SENSOR_FECHAMENTO_CANCELA_SAIDA	= 12 # Sensor que um carro saiu

## Vagas
ENDERECO_01 = 22 # Endereço BIT 1
ENDERECO_02 = 26 # Endereço BIT 2
ENDERECO_03 = 19 # Endereço BIT 3
SENSOR_DE_VAGA = 18 # Sensor de Vaga

## Sinais de Lotado
SINAL_DE_LOTADO_FECHADO_ANDAR1 = 27 # Sinal de Lotado do andar 1
SINAL_DE_LOTADO_FECHADO_ANDAR2 = 8  # Sinal de Lotado do andar 2