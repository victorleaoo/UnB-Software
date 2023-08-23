import threading
from utils.server_tcp import TCPServer
from utils.server_config import *

# Inicia o servidor central
if __name__ == '__main__':
    server = TCPServer(HOST, PORT_ANDAR1, PORT_ANDAR2)
    print(f'Servidor iniciado em {HOST}:{PORT_ANDAR1} e {HOST}:{PORT_ANDAR2}')

    # Aguarda as conexões dos servidores dos andares
    while True:
        try:
            # Aceita a conexão do andar 1
            andar1_socket, andar1_address = server.accept_connection(PORT_ANDAR1)
            print(f'Conexão estabelecida com o andar 1 {andar1_address}')
            # Cria uma nova thread para tratar do andar 1
            andar1_thread = threading.Thread(target=server.manipula_andar, args=(andar1_socket, andar1_address, 1))
            andar1_thread.daemon = True
            andar1_thread.start()

            # Aceita a conexão do andar 2
            andar2_socket, andar2_address = server.accept_connection(PORT_ANDAR2)
            print(f'Conexão estabelecida com o andar 2 {andar2_address}')
            # Cria uma nova thread para tratar do andar 2
            andar2_thread = threading.Thread(target=server.manipula_andar, args=(andar2_socket, andar2_address, 2))
            andar2_thread.daemon = True
            andar2_thread.start()

        except KeyboardInterrupt:
            # Encerra o programa ao receber o comando de interrupção do usuário (Ctrl+C)
            print("Programa encerrado pelo usuário.")
            break
        except:
            # Encerra a conexão em caso de erro na conexão
            print("Erro ao estabelecer conexão com um dos andares.")
            if andar1_socket:
                andar1_socket.close()
            if andar2_socket:
                andar2_socket.close()
            continue

    # Encerra as conexões
    andar1_socket.close()
    andar2_socket.close()
    print("Conexões encerradas.")