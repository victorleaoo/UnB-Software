from datetime import datetime, timedelta

class DescricaoEmBrancoException(Exception):
    pass

class ValorInvalidoException(Exception):
    pass

class Produto:
    def __init__(
        self, 
        nome,
        codigo_barras, 
        preco_compra, 
        preco_venda, 
        quantidade_inicial,
        lote,
        data_validade,
        limite_estoque=10
    ):
        if (nome is None or
            codigo_barras is None or
            preco_compra is None or
            preco_venda is None or
            quantidade_inicial is None or
            lote is None or
            data_validade is None or
            data_validade.strip() == ""
            ):
            raise DescricaoEmBrancoException("Todos os atributos devem estar presentes!")
        
        if (preco_compra <= 0.0 or preco_venda <= 0.0 or quantidade_inicial <= 0.0):
            raise ValorInvalidoException("Valor de compra, valor de venda e quantidade inicial de itens devem ser positivos!")

        self.nome = nome
        self.codigo_barras = codigo_barras
        self.preco_compra = preco_compra
        self.preco_venda = preco_venda
        self.quantidade_inicial = quantidade_inicial
        self.lote = lote
        self.data_validade = data_validade
        self.limite_estoque = limite_estoque

    def esta_no_periodo_de_validade(self):
        data_atual = datetime.now()
        data_validade_produto = datetime.strptime(self.data_validade, "%d/%m/%Y")
        return data_validade_produto >= data_atual

    def verificar_estoque_baixo(self):
        return self.quantidade_inicial <= int(self.limite_estoque)

    def consulta_estoque_nome(self, nome):
        if self.nome == nome:
            return self

    def consulta_estoque_codigo(self, codigo): 
        if self.codigo_barras == codigo: 
            return self 
        
    def consulta_estoque(self, nome, codigo): 
        if self.nome == nome  and self.codigo_barras == codigo:
            return self 
        else:  
            return ''