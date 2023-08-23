from utils.tcp_client import Andar_TCP
from andar2_utils.andar2_config import *
from utils.andar_componentes import *
from andar2_utils.andar2_componentes import *

import threading

# Cria a conexão TCP do Andar 2
andar2_tcp = Andar_TCP(
    host = HOST,
    port = PORT_ANDAR2,
    buffer_size = BUFFER_SIZE,
    sinal_lotado_andar1=SINAL_DE_LOTADO_FECHADO_ANDAR1,
    sinal_lotado_andar2=SINAL_DE_LOTADO_FECHADO_ANDAR2
)

# Instancia as vagas
vagas = Vaga(
    endereco_01=ENDERECO_01,
    endereco_02=ENDERECO_02,
    endereco_03=ENDERECO_03,
    sensor_de_vaga=SENSOR_DE_VAGA,
    andar=2,
    andar_tcp=andar2_tcp
)

if __name__ == "__main__":
    # Instancia os Sensores de Passagem
    sensores_passagem = SensorPassagem(
        sensor_de_passagem_1=SENSOR_DE_PASSAGEM_1,
        sensor_de_passagem_2=SENSOR_DE_PASSAGEM_2,
        andar_tcp=andar2_tcp
    )
    
    # Thread para as vagas do primeiro andar
    vaga_thread = threading.Thread(target=vagas.testar_vagas)
    vaga_thread.daemon = True
    vaga_thread.start()

    # Thread para os sensores de passagem
    sensores_passagem_thread = threading.Thread(target=sensores_passagem.monitorar_sensor)
    sensores_passagem_thread.daemon = True
    sensores_passagem_thread.start()

    # Thread para o recebimento de mensagens
    receive_message_thread = threading.Thread(target=andar2_tcp.receive_message)
    receive_message_thread.daemon = True
    receive_message_thread.start()

    # Esperar as threads
    vaga_thread.join()
    sensores_passagem_thread.join()
    receive_message_thread.join()