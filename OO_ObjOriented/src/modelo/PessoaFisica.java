package modelo;

/**
 * Classe abstrata de PessoaFisica e pai de Cliente e Funcionario. Possui seus atributos e gets/sets.
 * Caso de Herança + Caso de classe abstrata
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */

public abstract class PessoaFisica {
	
	/**
	 * Atributos de PessoaFisica.
	 */
	protected String nome;
	protected String telefone;
	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public String getTelefone() {
		return telefone;
	}
	public void setTelefone(String telefone) {
		this.telefone = telefone;
	}
	
}
