from main.Produto import *

class ValorInvalidoException(Exception):
    pass

class GerenciadorDeInventario:
    def __init__(self):
        # Inicializa o estoque, agora armazenando objetos Produto
        # Estrutura ajustada para {codigo_barras: {lote: objeto Produto}}
        self.estoque = {
            '12345': {
                'LoteA': Produto("Produto A", "12345", 10.0, 15.0, 50, "LoteA", "2023-12-31"),
                'LoteB': Produto("Produto B", "12345", 12.0, 18.0, 30, "LoteB", "2024-01-15")
            }}

    def adicionar_produto(self, produto, id_filial):
        if produto.codigo_barras not in self.estoque:
            self.estoque[produto.codigo_barras] = {}
        self.estoque[produto.codigo_barras][id_filial] = produto

    def registrar_recebimento(self, codigo_barras, quantidade, id_filial):
        if codigo_barras not in self.estoque or id_filial not in self.estoque[codigo_barras]:
            raise ValorInvalidoException("Produto ou filial não encontrados no estoque")
        self.estoque[codigo_barras][id_filial].quantidade_inicial += quantidade
        return True

    def registrar_venda(self, codigo_barras, quantidade, id_filial):
        if quantidade < 0:
            raise ValorInvalidoException("Quantidade não pode ser negativa para vendas")
        self._atualizar_estoque(codigo_barras, -quantidade, id_filial)
        return True

    def registrar_transferencia(self, id_filial_origem, id_filial_destino, codigo_barras, quantidade):
        if quantidade < 0:
            raise ValorInvalidoException("Quantidade não pode ser negativa para transferências")
        self._atualizar_estoque(codigo_barras, -quantidade, id_filial_origem)
        self._atualizar_estoque(codigo_barras, quantidade, id_filial_destino)
        return True

    def registrar_devolucao(self, codigo_barras, quantidade, id_filial):
        if quantidade < 0:
            raise ValorInvalidoException("Quantidade não pode ser negativa para devoluções")
        self._atualizar_estoque(codigo_barras, quantidade, id_filial)
        return True

    def registrar_ajuste(self, codigo_barras, quantidade, id_filial):
        if codigo_barras not in self.estoque or id_filial not in self.estoque[codigo_barras]:
            raise ValorInvalidoException("Produto ou filial não encontrados no estoque")
        self._atualizar_estoque(codigo_barras, quantidade, id_filial)
        return True

    def _atualizar_estoque(self, codigo_barras, quantidade, id_filial):
        produto = self.estoque[codigo_barras][id_filial]
        novo_estoque = produto.quantidade_inicial + quantidade
        if novo_estoque < 0:
            raise ValorInvalidoException("Estoque não pode ser negativo após a atualização")
        produto.quantidade_inicial = novo_estoque

    def consultar_estoque(self, codigo_barras, id_filial):
        if codigo_barras in self.estoque and id_filial in self.estoque[codigo_barras]:
            return self.estoque[codigo_barras][id_filial].quantidade_inicial
        else:
            raise ValorInvalidoException("Produto ou filial não encontrados no estoque")
