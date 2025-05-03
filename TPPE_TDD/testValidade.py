# -*- coding: utf-8 -*-
import pytest
from main.produto import Produto, DescricaoEmBrancoException
from datetime import datetime, timedelta

def test_produto_fora_validade():
    data_atual = datetime.now()
    produto = Produto(
        nome="Shampoo na validade",
        codigo_barras="123456789",
        preco_compra=5.50,
        preco_venda=15.20,
        quantidade_inicial=10,
        lote=0,
        data_validade= "12/01/1999"
    )
    assert produto.esta_no_periodo_de_validade() == False

def test_data_vazia():
    with pytest.raises(DescricaoEmBrancoException):
        produto = Produto(
            nome="Shampoo na validade",
            codigo_barras="123456789",
            preco_compra=5.50,
            preco_venda=15.20,
            quantidade_inicial=10,
            lote=0,
            data_validade=""
        )
    assert "produto" not in locals()

@pytest.mark.parametrize("nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade, esperado", [
    ("Produto A", "1234567890", 10.0, 15.0, 5, "Lote A", "15/03/2001", False),
    ("Produto B", "1111111111", 50.0, 70.0, 25, "Lote F", "15/04/2025", True),
    ("Produto C", "2222222222", 50.0, 70.0, 25, "Lote F", "17/06/1999", False),
    ("Produto D", "3333333333", 50.0, 70.0, 25, "Lote F", "17/06/2024", True),
    ("Produto E", "4444444444", 50.0, 70.0, 25, "Lote F", "01/01/2025", True),
    ("Produto F", "5555555555", 50.0, 70.0, 25, "Lote F", "07/02/1966", False),
    ("Produto G", "6666666666", 50.0, 70.0, 25, "Lote F", "23/12/2029", True),
    ("Produto H", "7777777777", 50.0, 70.0, 25, "Lote F", "01/01/2001", False),
])
def test_produto_validade(nome, codigo_barras, preco_compra, preco_venda, quantidade_inicial, lote, data_validade, esperado):
    produto = Produto(
        nome=nome,
        codigo_barras=codigo_barras,
        preco_compra=preco_compra,
        preco_venda=preco_venda,
        quantidade_inicial=quantidade_inicial,
        lote=lote,
        data_validade=data_validade
    )
    assert produto.esta_no_periodo_de_validade() == esperado
    