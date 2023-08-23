import pandas as pd
import matplotlib.pyplot as plt

# Carregar dados do arquivo CSV
df = pd.read_csv('./log_csv/log_manual.csv')

# Converter a coluna 'Datetime' para o formato de data e hora
df['Datetime'] = pd.to_datetime(df['Datetime'])

df['Seconds'] = (df['Datetime'] - df['Datetime'].min()).dt.total_seconds()

# Plotar gráfico das temperaturas em função do tempo
plt.figure(figsize=(10, 6))
plt.plot(df['Seconds'], df['Temp Interna'], label='Temp Interna')
plt.plot(df['Seconds'], df['Temp Ambiente'], label='Temp Ambiente')
plt.plot(df['Seconds'], df['Temp Referencia'], label='Temp Referencia')
plt.xlabel('Tempo (s)')
plt.ylabel('Temperatura (°C)')
plt.title('Temperaturas x Tempo')
plt.legend()
plt.grid(True)
plt.savefig('grafico_temperaturas_manual.png')  # Salvar gráfico em arquivo de imagem
plt.show()

# Plotar gráfico do acionamento dos atuadores em função do tempo
plt.figure(figsize=(10, 6))
plt.plot(df['Seconds'], df['Acionamento Atuadores % (Resistor/Ventoinha)'], label='Acionamento Atuadores')
plt.xlabel('Tempo (s)')
plt.ylabel('Acionamento Atuadores (%)')
plt.title('Acionamento dos Atuadores x Tempo')
plt.grid(True)
plt.savefig('grafico_acionamento_atuadores_manual.png')  # Salvar gráfico em arquivo de imagem
plt.show()