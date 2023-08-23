package modelo;

/**
 * Classe modelo de Cliente e filha de PessoaFisica. Possui seus atributos, construtor e gets/sets.
 * Caso de Herança
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */

public class Cliente extends PessoaFisica implements Model {
	
	/**
	 * Atributos de Cliente.
	 */
	private String email;
	private String endCliente;
	
	/**
	 * Construtor de Cliente.
	 * @param nP -> String contendo nome do Cliente.
	 * @param t  -> String contendo telefone do Cliente. 
	 * @param em -> String contendo e-mail do Cliente.
	 * @param eC -> String contendo endereço do Cliente.
	 */
	public Cliente(String nP, String t, String em, String eC) {
		nome = nP;
		telefone = t;
		email = em;
		endCliente = eC;
	}

	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}

	public String getEndCliente() {
		return endCliente;
	}
	public void setEndCliente(String endCliente) {
		this.endCliente = endCliente;
	}

	/**
	 * Função para implementar a interface Model (não é realmente usada no programa).
	 * @return String
	 */
	@Override
	public String getModel() {
		return nome + " - " + telefone;
	}
	
}
