def calcula_crc16(data):
    """
    Calcula o valor CRC16 de uma sequência de bytes (data) utilizando o polinômio CRC16 MODBUS
    """
    crc = 0x0000  
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x0001:
                crc >>= 1
                crc ^= 0xA001
            else:
                crc >>= 1
    return crc

def check_crc(buffer):
    """
    Verifica se o CRC16 recebido é válido com um CRC calculado
    Caso não, dá uma exceção
    """
    valid_crc = calcula_crc16(buffer[:-2]).to_bytes(2, "little")
    crc_received = buffer[-2:]
    if crc_received != valid_crc:
        return None
    return 1