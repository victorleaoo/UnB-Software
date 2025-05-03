import pytest
from main.Produto import Produto, DescricaoEmBrancoException

def test_consulta_estoque_nome():
    produto = Produto("Produto A", "123456789", 10.0, 15.0, 10, "Lote A", "2023-12-31")
    resultado_consulta = produto.consulta_estoque_nome(produto.nome)
    assert resultado_consulta == produto

def test_consulta_estoque_codigo():
    produto = Produto("Produto B","123456789", 10.0, 15.0, 10, "Lote A", "2023-12-31")
    resultado_consulta = produto.consulta_estoque_codigo(produto.codigo_barras)
    assert resultado_consulta == produto 

#O produto pode ter o mesmo nome, mas não o mesmo codigo.
def test_consulta_estoque():
    produto = Produto("Produto B","123456789", 10.0, 15.0, 10, "Lote A", "2023-12-31")
    resultado_consulta = produto.consulta_estoque(produto.nome,produto.codigo_barras)
    assert resultado_consulta == produto 
    
test_data = [
    ("Produto A","123456789", 10.0, 15.0, 100, "Lote A", "2023-12-31"),
    ("Produto B","987654321", 12.5, 18.0, 80, "Lote B", "2024-05-15"),
    ("Produto C","111222333", 8.0, 12.0, 50, "Lote C", "2023-08-20"),
    ("Produto D","444555666", 15.0, 20.0, 200, "Lote D", "2024-10-10"),
    ("Produto E","777888999", 20.0, 25.0, 300, "Lote E", "2023-06-30"),
]

@pytest.mark.parametrize(
    "nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade",
    test_data
)
def test_consulta_estoque_nome(nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade):
    produto = Produto(nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade)
    resultado_consulta = produto.consulta_estoque_nome(produto.nome)
    assert resultado_consulta == produto

@pytest.mark.parametrize(
    "nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade",
    test_data
)
def test_consulta_estoque_codigo(nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade):
    produto = Produto(nome,codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade)
    resultado_consulta = produto.consulta_estoque_codigo(produto.codigo_barras)
    assert resultado_consulta == produto

@pytest.mark.parametrize(
    "nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade",
    test_data
)
def test_consulta_estoque(nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade):
    produto = Produto(nome,codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade)
    resultado_consulta = produto.consulta_estoque(produto.nome, produto.codigo_barras)
    assert resultado_consulta == produto
