package modelo;

import java.util.ArrayList;
import java.util.List;

/**
 * Classe modelo de Venda. Possui seus atributos, construtor e gets/sets.
 * Caso de Agregação
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */

public class Venda implements Model {

	/**
	 * Atributos de Venda.
	 */
	private char metPag; // 'C'/'c' para Cartão - 'B'/'b' para Boleto - 'P'/'p' para Pix
	private Funcionario f;
	private Cliente c; 
	private List<ItensVenda> sapatos;
	private int id;
	
	/**
	 * Construtor de Venda.
	 * @param mP -> Char contendo metódo de pagamento da Venda:
	 * (1) 'C'/'c' para Cartão
	 * (2) 'B'/'b' para Boleto
	 * (3) 'P'/'p' para Pix
	 * @param fun-> Funcionario contendo funcionário responsável pela Venda.
	 * @param cli-> Cliente contendo cliente que comprou a Venda.
	 * @param ID -> Int contendo ID da Venda.
	 */
	public Venda(char mP, Funcionario fun, Cliente cli, int ID) {
		metPag = mP;
		f = fun;
		c = cli;
		sapatos = new ArrayList<>();
		id = ID;
	}

	public char getMetPag() {
		return metPag;
	}
	public void setMetPag(char metPag) {
		this.metPag = metPag;
	}

	public Funcionario getF() {
		return f;
	}
	public void setF(Funcionario f) {
		this.f = f;
	}

	public Cliente getC() {
		return c;
	}
	public void setC(Cliente c) {
		this.c = c;
	}

	public List<ItensVenda> getSapatos() {
		return sapatos;
	}
	public void setSapatos(List<ItensVenda> sapatos) {
		this.sapatos = sapatos;
	}
	
	public int getID() {
		return id;
	}

	public void setID(int iD) {
		id = iD;
	}
	
	/**
	 * Adiciona um item à lista de Itens da Venda.
	 * @param s -> ItensVenda contendo o item a ser adicionado à lista de itens da Venda.
	 */
	public void addItem(ItensVenda s) {
		s.getS().setQntdEstoque(s.getS().getQntdEstoque() - s.getQntdVenda());
		sapatos.add(s);
	}
	
	/**
	 * Deleta um item da Venda.
	 * @param s -> ItensVenda contendo o item a ser deletado da Venda. 
	 */
	public void deletarItem(ItensVenda s) {
		sapatos.remove(s);
	}

	/**
	 * Função para implementar a interface Model (não é realmente usada no programa).
	 * @return String
	 */
	@Override
	public String getModel() {
		return "ID";
	}
	
}
