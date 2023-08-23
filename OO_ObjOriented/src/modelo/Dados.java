package modelo;

/**
 * Classe modelo de Dados. Basicamente, é o "banco de dados" do projeto. Possui gets e métodos que inserem ou modificam os dados das classes.
 * Carregamento de dados aleatórios no seu software.
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */

public final class Dados {
	
	/**
	 * Arrays de cada tipo de classe do projeto.
	 * A empresa não é um array porque só é possível a existência de uma empresa no sistema.
	 */
	private static Sapato[] dSapatos = new Sapato[50];
	private static Empresa dEmpresa = new Empresa("Luv Sneakers", "59.546.515/0001-34", 2015, "(11) 4935-2323", "QG Luv Sneakers - DF");
	private static Cliente[] dClientes = new Cliente[50];
	private static Funcionario[] dFuncs = new Funcionario[50];
	private static ItensVenda[] dItens = new ItensVenda[150];
	private static Venda[] dVendas = new Venda[50];
	
	/**
	 * Dados pré carregados.
	 */
	static {
		
		dSapatos[0] = new Sapato("Air Jordan 1 - Obsidian", "Nike", 'C', 1749.99, 34.5, 44.0, "Tênis de Couro/Borracha, com as cores em homenagem a Universidade que Jordan jogou.", 10, "imagens/airjordan-obsidian.jpg");
		dSapatos[1] = new Sapato("Chinelo Slide - SLX", "Rider", 'S', 179.99, 35.0, 44.5, "Chinelo sandália macio, com elementos da NBA e do filme Space Jam para fãs.", 20, "imagens/slx-rider.jpg");
		dSapatos[2] = new Sapato("Gel-Dedicate 6 - Tênis", "Asics", 'E', 275.49, 39.0, 45.0, "Tênis ideal para jogadores de Tênis, especialmente em quadras de Saibro, com muita estabilidade torsional.", 30, "imagens/gel6-asics.jpg");
		dSapatos[3] = new Sapato("Phantom GT2 Elite - Chuteira", "Nike", 'E', 1599.99, 35.0, 44.0, "Chuteira de campo com toque preciso para qualquer clima, além de cano alto, possui palmilha com amortecimento.", 70, "imagens/phantom-nike.jpg");
		dSapatos[4] = new Sapato("Slide Pure - Yeezy", "Adidas", 'S', 650.00, 37.5, 43.5, "Chinelo do modelo slide com acabamento bege. Com espuma EVA injetada, compõe a composição de uma peça única.", 2, "imagens/yeezy-slide.jpeg");
		
		dClientes[0] = new Cliente("Victor", "(61) 99184-4198", "victor@gmail.com", "Rua 1 - Casa 1");
		dClientes[1] = new Cliente("Felipe", "(61) 99635-7291", "felipe@gmail.com", "Rua 2 - Casa 2");
		dClientes[2] = new Cliente("João Pedro", "(61) 99601-7244", "joaopedro@gmail.com", "Rua 3 - Casa 3");
		
		dFuncs[0] = new Funcionario("Jorge", "(61) 98345-7102", 11, 3052.0, 2018);
		dFuncs[1] = new Funcionario("Yure", "(61) 99201-7202", 22, 2320.0, 2019);
		dFuncs[2] = new Funcionario("Daniel", "(61) 93331-7708", 33, 750.55, 2021);
		
		dVendas[0] = new Venda('C', dFuncs[0], dClientes[0], 1);
		dVendas[0].addItem(new ItensVenda(dSapatos[0], 1));
		dVendas[1] = new Venda('B', dFuncs[1], dClientes[1], 2);
		dVendas[1].addItem(new ItensVenda(dSapatos[0], 2));
		dVendas[1].addItem(new ItensVenda(dSapatos[1], 3));
		dVendas[2] = new Venda('P', dFuncs[2], dClientes[2], 3);
		dVendas[2].addItem(new ItensVenda(dSapatos[0], 1));
		dVendas[2].addItem(new ItensVenda(dSapatos[1], 3));
		dVendas[2].addItem(new ItensVenda(dSapatos[2], 5));
	}

	public Sapato[] getdSapatos() {
		return dSapatos;
	}
	public void inserirEditaSapato(Sapato sap, int pos) {
		Dados.dSapatos[pos] = sap;
	}
	public Empresa getdEmpresa() {
		return dEmpresa;
	}
	public void inserirEditaEmpresa(Empresa e) {
		Dados.dEmpresa = e;
	}
	public Cliente[] getdClientes() {
		return dClientes;
	}
	public void inserirEditaCliente(Cliente c, int pos) {
		Dados.dClientes[pos] = c;
	}
	public Funcionario[] getdFuncs() {
		return dFuncs;
	}
	public void inserirEditaFunc(Funcionario f, int pos) {
		Dados.dFuncs[pos] = f;
	}	
	public ItensVenda[] getdItens() {
		return dItens;
	}
	public Venda[] getdVendas() {
		return dVendas;
	}
	public void inserirEditaVenda(Venda v, int pos) {
		Dados.dVendas[pos] = v;
	}
}
