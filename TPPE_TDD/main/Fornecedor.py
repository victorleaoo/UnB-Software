from datetime import datetime

class Fornecedor:
    def __init__(self, id, nome, endereco, data_contrato):
        self.validar_id(id)
        self.validar_nome(nome)
        self.validar_endereco(endereco)
        self.validar_data_contrato(data_contrato)
        self.id = id
        self.nome = nome
        self.endereco = endereco
        self.data_contrato = data_contrato
    
    @staticmethod
    def validar_id(id):
        if id is None or id == '':
            raise ValueError("ID não pode ser nulo ou vazio")
        if not isinstance(id, int):
            raise ValueError("ID deve ser um número inteiro")

    @staticmethod
    def validar_nome(nome):
        if nome is None or nome == '':
            raise ValueError("Nome não pode ser nulo ou vazio")

    @staticmethod
    def validar_endereco(endereco):
        if endereco is None or endereco == '':
            raise ValueError("Endereço não pode ser nulo ou vazio")

    @staticmethod
    def validar_data_contrato(data_contrato):
        try:
            datetime.strptime(data_contrato, '%Y-%m-%d')
        except ValueError:
            raise ValueError("Data de contrato inválida, formato esperado: AAAA-MM-DD")

        
