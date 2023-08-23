package modelo;

/**
 * Classe modelo de Funcionário e filha de PessoaFisica. Possui seus atributos, construtor e gets/sets. 
 * Sobrecarga de Método + Caso de Herança 
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */

public class Funcionario extends PessoaFisica implements Model {

	/**
	 * Atributos de Funcionário.
	 */
	private int idFunc;
	private double salario;
	private int anoIngresso;
	
	/**
	 * Construtor de Funcionário com os atributos de PessoaFisica.
	 * @param nP -> String contendo nome do Funcionário.
	 * @param t  -> String contendo telefone do Funcionário.
	 */
	public Funcionario(String nP, String t) {
		nome = nP;
		telefone = t;
	}
	
	/**
	 * Construtor de Funcionário. Sobrecarga do Método acima.
	 * @param nP -> String contendo nome do Funcionário.
	 * @param t  -> String contendo telefone do Funcionário.
	 * @param id -> Int contendo ID do Funcionário.
	 * @param s  -> Double contendo salário do Funcionário.
	 * @param ano-> Int contendo ano de ingresso na empresa do Funcionário
	 */
	public Funcionario(String nP, String t, int id, double s, int ano) {
		nome = nP;
		telefone = t;
		idFunc = id;
		salario = s;
		anoIngresso = ano;
	}
	
	public int getIdFunc() {
		return idFunc;
	}
	public void setIdFunc(int idFunc) {
		this.idFunc = idFunc;
	}

	public double getSalario() {
		return salario;
	}
	public void setSalario(double salario) {
		this.salario = salario;
	}

	public int getAnoIngresso() {
		return anoIngresso;
	}
	public void setAnoIngresso(int anoIngresso) {
		this.anoIngresso = anoIngresso;
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
