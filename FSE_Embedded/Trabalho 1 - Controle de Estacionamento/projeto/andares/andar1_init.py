from utils.tcp_client import Andar_TCP
from andar1_utils.andar1_componentes import Cancela
from utils.andar_componentes import Vaga
from andar1_utils.andar1_config import *

import threading

# Cria a conexão TCP do Andar 1
andar1_tcp = Andar_TCP(
    host = HOST,
    port = PORT_ANDAR1,
    buffer_size = BUFFER_SIZE,
    sinal_lotado_andar1=SINAL_DE_LOTADO_FECHADO_ANDAR1,
    sinal_lotado_andar2=SINAL_DE_LOTADO_FECHADO_ANDAR2
)

# Instancia a cancela de entrada
cancela_entrada = Cancela(
    sensor_abertura_pin=SENSOR_ABERTURA_CANCELA_ENTRADA,
    motor_pin=MOTOR_CANCELA_ENTRADA,
    sensor_fechamento_pin=SENSOR_FECHAMENTO_CANCELA_ENTRADA,
    andar_tcp=andar1_tcp,
    tipo=0
)

# Instancia a cancela de saída
cancela_saida = Cancela(
    sensor_abertura_pin=SENSOR_ABERTURA_CANCELA_SAIDA,
    motor_pin=MOTOR_CANCELA_SAIDA,
    sensor_fechamento_pin=SENSOR_FECHAMENTO_CANCELA_SAIDA,
    andar_tcp=andar1_tcp,
    tipo=1
)

# Instancia as vagas
vagas = Vaga(
    endereco_01=ENDERECO_01,
    endereco_02=ENDERECO_02,
    endereco_03=ENDERECO_03,
    sensor_de_vaga=SENSOR_DE_VAGA,
    andar=1,
    andar_tcp=andar1_tcp
)

if __name__ == "__main__":
    # Thread para a cancela de entrada
    cancela_entrada_thread = threading.Thread(target=cancela_entrada.verifica_cancela)
    cancela_entrada_thread.daemon = True
    cancela_entrada_thread.start()
    
    # Thread para as vagas do primeiro andar
    vaga_thread = threading.Thread(target=vagas.testar_vagas)
    vaga_thread.daemon = True
    vaga_thread.start()

    # Thread para a cancela de saída
    cancela_saida_thread = threading.Thread(target=cancela_saida.verifica_cancela)
    cancela_saida_thread.daemon = True
    cancela_saida_thread.start()

    # Thread para o recebimento de mensagens
    receive_message_thread = threading.Thread(target=andar1_tcp.receive_message)
    receive_message_thread.daemon = True
    receive_message_thread.start()

    # Esperar as threads
    cancela_entrada_thread.join()
    vaga_thread.join()
    cancela_saida_thread.join()
    receive_message_thread.join()