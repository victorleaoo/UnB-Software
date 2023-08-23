[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/OJtG4ZlI)
# Trabalho 1 (2023-1) - Controle de Estacionamentos

**Aluno**: Victor Hugo Oliveira Leão

**Matrícula**: 200028367

[Enunciado do trabalho](https://github.com/FGA-FSE/fse-trabalho-1-2023-1---controle-de-estacionamentos-victorleaoo/blob/main/enunciado.md)

## Instruções de execução

### Variáveis

Mude os seguintes arquivos com as informações desejadas (portas e pinos):

- [server_config](https://github.com/FGA-FSE/fse-trabalho-1-2023-1---controle-de-estacionamentos-victorleaoo/blob/main/projeto/utils/server_config.py):
    * HOST: endereço IP do servidor central
    * PORT_ANDAR1: porta do andar 1 (servidor distribuído 1)
    * PORT_ANDAR2: porta do andar 2 (servidor distribuído 2)
    * VALOR_TAXA: valor da taxa cobrada por minuto

- [andar1_config](https://github.com/FGA-FSE/fse-trabalho-1-2023-1---controle-de-estacionamentos-victorleaoo/blob/main/projeto/andares/andar1_utils/andar1_config.py):
    * HOST: endereço IP do servidor central
    * PORT_ANDAR1: porta do andar 1 (servidor distribuído 1)
    * PINOS: direcionamento de cada pino da GPIO

- [andar_2config](https://github.com/FGA-FSE/fse-trabalho-1-2023-1---controle-de-estacionamentos-victorleaoo/blob/main/projeto/andares/andar2_utils/andar2_config.py):
    * HOST: endereço IP do servidor central
    * PORT_ANDAR2: porta do andar 2 (servidor distribuído 2)
    * PINOS: direcionamento de cada pino da GPIO

### Execução

Instale as dependências: ```pip install -r requirements.txt```

- Para executar o **Servidor Central** (interface gráfica): ```python3 ./projeto/server_init.py```
- Para executar o **Andar 1**: ```python3 ./projeto/andares/andar1_init.py```
- Para executar o **Andar 2**: ```python3 ./projeto/andares/andar2_init.py```

É aconselhável executar o comando ```python3 reset_gpio.py``` antes, a fim de resetar os pinos da GPIO.

## Vídeo

[Link do vídeo apresentando o trabalho](https://drive.google.com/file/d/1xMBBpMyW3HJd9zEpT-ktmg-cFb84A6NZ/view?usp=sharing)

## Melhorias

1. Caso algum servidor distribuído pare de funcionar, eles não se reconectam de forma automática.
2. O monitoramento do estacionamento por meio de entradas do usuário (manualmente) não foi possível de implementar, assim, o controle é apenas automático.
3. Tentar melhorar o uso de CPU (muitas threads são utilizadas), talvez, por meio de interrupções.
4. Identificador para cada carro que entrou, em que vaga estacionou e os horários, já que o valor total está sendo computado de forma geral.
