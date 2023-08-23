import struct

from uart.utils.config import codigos_gerais, mensagens_retorno, comandos_usuario
from uart.crc import calcula_crc16, check_crc

def codifica_mensagem(codigo, valor=None):
    """
    Função que codifica a mensagem com CRC, caso espere um valor (diferente de None), trata o valor dependendo do seu tipo (int, float ou string)
    """
    try:
        bytes_mensagem = bytes(codigos_gerais.get(codigo, None))
    except TypeError:
        return None # Retorna None se não for encontrado o código passado
    
    if valor is not None:
        if isinstance(valor, int):
            valor = struct.pack("<i", valor)
        elif isinstance(valor, float):
            valor = struct.pack("<f", round(valor, 2))
        elif isinstance(valor, str):
            valor = valor.encode('utf-8')
        else:
            raise ValueError('Tipo de valor inválido')
        
        bytes_mensagem = bytes_mensagem + valor

    crc = calcula_crc16(bytes_mensagem)
    mensagem_crc = bytes_mensagem + crc.to_bytes(2, "little")
    return mensagem_crc

def decodifica_mensagem(buffer):
    """
    Primeiramente, checa o CRC
    Em seguida, retorna o código que foi usado e o seu valor de retorno arrendado
    Caso seja um valor de envio, não tem código de resposta
    """
    crc_checado = check_crc(buffer)

    if crc_checado == None:
        return None, None

    retorno_float = [0xC1, 0xC2]

    if len(buffer) == 9:
        code = buffer[1]
        mensagem_code = buffer[2]
        value = buffer[3:7]

        if code == 0x23:
            if mensagem_code in retorno_float:
                return mensagens_retorno[mensagem_code], round(struct.unpack("<f", value)[0], 2)
            elif mensagem_code == 0xC3:
                return mensagens_retorno[mensagem_code], comandos_usuario.get(struct.unpack("<i", value)[0])
        elif code == 0x16:
            return None, None
    return None, None