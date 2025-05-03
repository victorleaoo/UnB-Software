# TP1 - Grupo 6

**Integrantes do Grupo**:

- Gabriel Roger Amorim da Cruz: 200018248
- Iago de Paula Cabral: 190088745
- Joao Pedro de Camargo Vaz: 200020650
- Matheus Soares Arruda: 190093480
- Pedro Henrique Nogueira Gonçalves: 190094486
- Victor Hugo Oliveira Leão: 200028367
- Vinicius Assumpcao de Araujo: 200028472

### Execução

O projeto foi desenvolvido na linguagem **Python** com a biblioteca **pytest**. Então, com o Python instalado na máquina, rode os comandos:
1. Instale o pytest: `pip install pytest parameterized`;
2. Rode o arquivo com os testes das funcionalidades desejadas por meio de: `pytest <test_arquivo>.py` ou `python3 -m pytest <test_arquivo>.py`;
3. Para rodar todos os testes de uma vez: `pytest test*`

## Entendimento do problema

### Diagrama

![Blank diagram](https://github.com/victorleaoo/tp1-g6-tppe/assets/33530818/c74d4cdd-e86f-48d6-9aa4-4e7cd04ab279)

### Funções a serem desenvolvidas

O trabalho deverá apresentar o emprego das três técnicas de TDD (falsificação, duplicação e triangulação) na implementação das seguintes funcionalidades:

* **Cadastro de Produtos:**
  - Garantir que o produto está cadastrado no sistema informando
    obrigatoriamente o nome do produto, seu código de barras, preço de compra, 
    preço de venda e quantidade inicial em estoque.
      - Commits: https://github.com/victorleaoo/tp1-g6-tppe/commit/86ae442a9832b55dd8ab1236ff1ebfbe68200952 a https://github.com/victorleaoo/tp1-g6-tppe/commit/d50cf792d9591394c46a156428878eec28fe9af7
  - Se algum desses itens acima não for informando, garantir que o produto não
    seja cadastrado através do lançamento da exceção `DescricaoEmBrancoException`.
      - Commits: https://github.com/victorleaoo/tp1-g6-tppe/commit/86ae442a9832b55dd8ab1236ff1ebfbe68200952 a https://github.com/victorleaoo/tp1-g6-tppe/commit/d50cf792d9591394c46a156428878eec28fe9af7
  - Se os valores de compra e venda e a quantidade de itens inicial em estoque
    for menor ou igual a zero, garantir que o item não seja cadastrado através
    do lançamento da exceção `ValorInvalidoException`.
      - Commits: https://github.com/victorleaoo/tp1-g6-tppe/commit/8bd822033312f7687d3624b0b7f99db5c2495222 a https://github.com/victorleaoo/tp1-g6-tppe/commit/25f0641965bcf50e4e13db31f1d91756822aa60d + https://github.com/victorleaoo/tp1-g6-tppe/commit/454f84fbfcc4aac427a43e04c9e1c48be5405e29
  
* **Consulta de Estoque:** 
  -  Garantir que o produto seja recuperado toda vez que ele for recuperado em
     buscas pelo seu nome ou pelo seu código de barras.
      - Commits: https://github.com/victorleaoo/tp1-g6-tppe/commit/b37465f407793f471444e1a1ecb1828537cf907c a https://github.com/victorleaoo/tp1-g6-tppe/commit/1db8439e7beb096b3720d282dd07d1fe104477c2

* **Gestão de Transações:**
  - Garantir que os seguintes tipos de transações sejam realizadas e os estoques dos produtos sejam atualizados: recebimento de mercadoria, vendas, transferências entre filiais, devoluções, ajustes de estoque.
    - Commits: https://github.com/victorleaoo/tp1-g6-tppe/commit/ad86c1250dbd3dc0691af5fec7a8c8bc13406f79 a https://github.com/victorleaoo/tp1-g6-tppe/commit/6792057c505888b0bf3bc8d9b085355cbfb1ee10 + https://github.com/victorleaoo/tp1-g6-tppe/commit/8fe29596b3ed4a64926a4a9acbcf7dfcb0686f9c
  - Garantir que não serão informadas quantidades negativas para as transações, exceto para ajustes de estoque. Nos outros casos, lançar exceções do tipo `ValorInvalidoException`. 
    - Commits: https://github.com/victorleaoo/tp1-g6-tppe/commit/ad86c1250dbd3dc0691af5fec7a8c8bc13406f79 a https://github.com/victorleaoo/tp1-g6-tppe/commit/6792057c505888b0bf3bc8d9b085355cbfb1ee10 + https://github.com/victorleaoo/tp1-g6-tppe/commit/8fe29596b3ed4a64926a4a9acbcf7dfcb0686f9c

* **Alertas de Estoque Baixo:**
  - Configuração de alertas automáticos que notificam os usuários quando os níveis de estoque de um produto atingem um limite mínimo predefinido, indicando a necessidade de reabastecimento.
    - Commits: https://github.com/victorleaoo/tp1-g6-tppe/commit/1c9db9887df4e94b6a41cbe142e04897f1253dbf a https://github.com/victorleaoo/tp1-g6-tppe/commit/ae2adc6304d96a6ca4d04b7b74505cc80fcc575c

* **Rastreamento de Lotes e Validade:**
  - Permite o rastreamento detalhado de lotes de produtos, especialmente útil para itens com data de validade. O sistema pode alertar sobre produtos próximos ao vencimento.
    - Commits: https://github.com/victorleaoo/tp1-g6-tppe/commit/c26d834bacd8fd1086c7b6ef21526f29136863a3 a https://github.com/victorleaoo/tp1-g6-tppe/commit/a0695b98b979c90c6a3ac78ea53c10f51035b97a

## Padrão de Commit

Para cada funcionalidade desenvolvida por meio do **TDD**, os *commits* devem ocorrer na seguinte ordem e seguindo o seguinte padrão:

- **falsificaçãoFalha**: git commit -m "falsificacaoFalha: <funcionalidade_desenvolvida>";
- **falsificaçãoPassa**: git commit -m "falsificacaoPassa: <funcionalidade_desenvolvida>";
- **duplicaçãoFalha**: git commit -m "duplicaçãoFalha: <funcionalidade_desenvolvida>";
- **duplicaçãoPassa**: git commit -m "duplicaçãoPassa: <funcionalidade_desenvolvida>";
- **triangulaçãoFalha**: git commit -m "triangulaçãoFalha: <funcionalidade_desenvolvida>";
- **triangulaçãoPassa**: git commit -m "triangulaçãoPassa: <funcionalidade_desenvolvida>";
- **parametrizacao**: git commit -m "parametrizacao: <funcionalidade_desenvolvida>";
