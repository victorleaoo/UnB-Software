import csv
from datetime import datetime
import os

def cria_log(temp_int, temp_amb, temp_ref, sinal_controle):
    """
    Salva as informações para log em um arquivo csv
    """
    nome_arquivo = "./log.csv"

    if not os.path.exists(nome_arquivo):
        with open(nome_arquivo, "w") as arquivo:
            arquivo.write("Datetime,Temp Interna,Temp Ambiente,Temp Referencia,Acionamento Atuadores % (Resistor/Ventoinha)\n")

    log_csv = [datetime.now().strftime("%d-%m-%Y %H:%M:%S"), temp_int, temp_amb, temp_ref, sinal_controle]

    with open(nome_arquivo, mode="a") as arquivo:
        writer = csv.writer(arquivo)
        writer.writerow(log_csv)