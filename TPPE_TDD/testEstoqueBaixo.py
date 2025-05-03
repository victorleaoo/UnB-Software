import pytest
from main.Produto import Produto, DescricaoEmBrancoException

def test_alerta_estoque_baixo():
    produto = Produto("Produto A", "1234567890", 10.0, 15.0, 5, "Lote A", "2023-12-31")
    assert produto.verificar_estoque_baixo() == True


def test_alteracao_limite_estoque():
    produto = Produto("Produto F", "4444444444", 50.0, 70.0, 25, "Lote F", "2024-12-31")
    assert produto.verificar_estoque_baixo() == False 

    produto.limite_estoque = 30
    assert produto.verificar_estoque_baixo() == True  

def test_limite_estoque():
    produto = Produto("Produto A", "1234567890", 10.0, 15.0, 10, "Lote A", "2023-12-31")
    assert produto.verificar_estoque_baixo() == True

def test_estoque_baixo_com_quantidades_marginais():
    produto_acima_limite = Produto("Produto H", "6666666666", 70.0, 90.0, 11, "Lote H", "2026-01-01")
    assert produto_acima_limite.verificar_estoque_baixo() == False  

    produto_abaixo_limite = Produto("Produto I", "7777777777", 80.0, 100.0, 9, "Lote I", "2027-01-01")
    assert produto_abaixo_limite.verificar_estoque_baixo() == True  

def test_estoque_baixo_com_limites_especificos():
    produto_limite_baixo = Produto("Produto J", "8888888888", 90.0, 110.0, 5, "Lote J", "2028-01-01", 5)
    assert produto_limite_baixo.verificar_estoque_baixo() == True

    produto_limite_alto = Produto("Produto K", "9999999999", 100.0, 120.0, 200, "Lote K", "2029-01-01", 150)
    assert produto_limite_alto.verificar_estoque_baixo() == False  

def test_estoque_com_valores_incomuns():
    produto_limite_baixo = Produto("Produto J", "8888888888", 90.0, 110.0, 5, "Lote J", "2028-01-01", 0x05)
    assert produto_limite_baixo.verificar_estoque_baixo() == True

    produto_limite_baixo = Produto("Produto J", "8888888888", 90.0, 110.0, 5, "Lote J", "2028-01-01", "0")
    assert produto_limite_baixo.verificar_estoque_baixo() == False

    produto_limite_baixo = Produto("Produto J", "8888888888", 90.0, 110.0, 5, "Lote J", "2028-01-01", 0x3)
    assert produto_limite_baixo.verificar_estoque_baixo() == False

# Os parâmetros são: nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade, limite_estoque, esperado
@pytest.mark.parametrize("nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade, limite_estoque, alterar_limite, esperado", [
    ("Produto A", "1234567890", 10.0, 15.0, 5, "Lote A", "2023-12-31", None, None, True),
    ("Produto F", "4444444444", 50.0, 70.0, 25, "Lote F", "2024-12-31", None, 30, True),
    ("Produto A", "1234567890", 10.0, 15.0, 10, "Lote A", "2023-12-31", None, None, True),
    ("Produto H", "6666666666", 70.0, 90.0, 11, "Lote H", "2026-01-01", None, None, False),
    ("Produto I", "7777777777", 80.0, 100.0, 9, "Lote I", "2027-01-01", None, None, True),
    ("Produto J", "8888888888", 90.0, 110.0, 5, "Lote J", "2028-01-01", 5, None, True),
    ("Produto K", "9999999999", 100.0, 120.0, 200, "Lote K", "2029-01-01", 150, None, False),
    ("Produto J", "8888888888", 90.0, 110.0, 5, "Lote J", "2028-01-01", 0x05, None, True),
    ("Produto J", "8888888888", 90.0, 110.0, 5, "Lote J", "2028-01-01", "0", None, False),
    ("Produto J", "8888888888", 90.0, 110.0, 5, "Lote J", "2028-01-01", 0x3, None, False)
])
def test_variados(nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade, limite_estoque, alterar_limite, esperado):
    if limite_estoque is None:
        produto = Produto(nome=nome, codigo_barras=codigo_barras, preco_compra=preco_compra, preco_venda=preco_venda, quantidade_inicial=quantidade_inicial, lote=lote, data_validade=data_validade)
    else:
        produto = Produto(nome=nome, codigo_barras=codigo_barras, preco_compra=preco_compra, preco_venda=preco_venda, quantidade_inicial=quantidade_inicial, lote=lote, data_validade=data_validade, limite_estoque=limite_estoque)

    if alterar_limite is not None:
        produto.limite_estoque = alterar_limite

    assert produto.verificar_estoque_baixo() == esperado