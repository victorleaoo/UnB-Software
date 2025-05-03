import unittest
from parameterized import parameterized
from main.Fornecedor import Fornecedor

class TestFornecedor(unittest.TestCase):
    def test_criar_fornecedor_valido(self):
        fornecedor = Fornecedor(1, "Fornecedor A", "Endereço A", "2023-01-01")
        self.assertEqual(fornecedor.id, 1)
        self.assertEqual(fornecedor.nome, "Fornecedor A")
        self.assertEqual(fornecedor.endereco, "Endereço A")
        self.assertEqual(fornecedor.data_contrato, "2023-01-01")

    def test_criar_fornecedor_com_id_invalido(self):
        with self.assertRaises(ValueError):
            Fornecedor(None, "Fornecedor B", "Endereço B", "2023-01-01")
    
    def test_criar_fornecedor_com_id_invalido_vazio(self):
        with self.assertRaises(ValueError):
            Fornecedor('', "Fornecedor C", "Endereço C", "2023-01-01")

    def test_criar_fornecedor_id_string(self):
        with self.assertRaises(ValueError):
            Fornecedor("abc", "Fornecedor D", "Endereço D", "2023-01-01")

    def test_criar_fornecedor_nome_vazio(self):
        with self.assertRaises(ValueError):
            Fornecedor(1, '', "Endereço D", "2023-01-01")

    def test_criar_fornecedor_endereco_vazio(self):
        with self.assertRaises(ValueError):
            Fornecedor(1, "Fornecedor E", '', "2023-01-01")
    
    def test_criar_fornecedor_data_invalida(self):
        with self.assertRaises(ValueError):
            Fornecedor(1, "Fornecedor E", "Endereço E", "data_invalida")

    @parameterized.expand([
        (None, "Fornecedor B", "Endereço B", "2023-01-01"),
        ('', "Fornecedor C", "Endereço C", "2023-01-01"),
        ("abc", "Fornecedor D", "Endereço D", "2023-01-01"),
        (123.5, "Fornecedor E", "Endereço E", "2023-01-01")  # Adicionando um número decimal para testar
    ])
    def test_criar_fornecedor_com_id_invalido_param(self, id, nome, endereco, data_contrato):
        with self.assertRaises(ValueError):
            Fornecedor(id, nome, endereco, data_contrato)
        
if __name__ == '__main__':
    unittest.main()
