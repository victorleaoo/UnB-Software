import unittest
from main.GestaoTransacoes import GerenciadorDeInventario, ValorInvalidoException
from main.produto import Produto, DescricaoEmBrancoException

class TesteTransacoesDeInventario(unittest.TestCase):

    def setUp(self):
        self.gerenciador = GerenciadorDeInventario()
        # Adicionando produtos ao estoque
        produto = Produto("Produto A", "12345", 10.0, 15.0, 50, "LoteA", "2023-12-31")
        self.gerenciador.adicionar_produto(produto, "001")  # Supondo que "001" é a filial


    def teste_transacoes_variadas(self):
        # Dados de teste parametrizados
        transacoes = [
            ("recebimento", "12345", 20, "LoteA"),
            ("venda", "12345", 10, "LoteA"),
            ("devolucao", "12345", 3, "LoteA"),
            ("ajuste", "12345", -2, "LoteA")
        ]

        for transacao in transacoes:
            with self.subTest(transacao=transacao):
                tipo, codigo_barras, quantidade, lote = transacao
                resultado = getattr(self.gerenciador, f"registrar_{tipo}")(codigo_barras, quantidade, lote)
                self.assertTrue(resultado)

                # Verificando se o estoque foi atualizado corretamente
                if tipo != "transferencia":  # Transferências requerem lógica adicional
                    estoque_atual = self.gerenciador.consultar_estoque(codigo_barras, lote)
                    self.assertIsNotNone(estoque_atual)


    def _testar_transferencia(self):
            # Testar transferência positiva entre lotes do mesmo produto
            codigo_barras = "12345"
            quantidade = 5
            lote_origem = "LoteA"
            lote_destino = "LoteB"

            # Transferência do LoteA para o LoteB
            self.gerenciador.registrar_transferencia(lote_origem, lote_destino, codigo_barras, quantidade)

            # Verificar se a quantidade foi reduzida em LoteA e aumentada em LoteB
            estoque_lote_origem = self.gerenciador.consultar_estoque(codigo_barras, lote_origem)
            estoque_lote_destino = self.gerenciador.consultar_estoque(codigo_barras, lote_destino)
            self.assertEqual(estoque_lote_origem, 45)  # 50 - 5
            self.assertEqual(estoque_lote_destino, 35)  # 30 + 5

    def teste_transacoes_quantidades_negativas(self):
        # Dados de teste parametrizados
        transacoes = [
            ("venda", "12345", -10, "LoteA"),
            # Transferência negativa - precisa ser ajustada manualmente
            ("devolucao", "12345", -3, "LoteA")
        ]

        for transacao in transacoes:
            with self.subTest(transacao=transacao):
                tipo, codigo_barras, quantidade, lote = transacao
                if tipo == "transferencia":
                    self._testar_transferencia_negativa()
                else:
                    with self.assertRaises(ValorInvalidoException):
                        getattr(self.gerenciador, f"registrar_{tipo}")(codigo_barras, quantidade, lote)

    def _testar_transferencia_negativa(self):
        # Testar transferência negativa entre lotes do mesmo produto
        codigo_barras = "12345"
        quantidade_negativa = -5
        lote_origem = "LoteA"
        lote_destino = "LoteB"

        # Transferência negativa do LoteA para o LoteB
        with self.assertRaises(ValorInvalidoException):
            self.gerenciador.registrar_transferencia(lote_origem, lote_destino, codigo_barras, quantidade_negativa)


    def teste_ajuste_estoque_negativo(self):
        codigo_barras = "12345"
        quantidade_ajuste_negativa = -100
        lote = "LoteA"
        with self.assertRaises(ValorInvalidoException):
            self.gerenciador.registrar_ajuste(codigo_barras, quantidade_ajuste_negativa, lote)

if __name__ == "__main__":
    unittest.main()