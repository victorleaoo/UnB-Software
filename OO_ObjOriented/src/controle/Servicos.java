package controle;

/**
 * Método que possui métodos de validação de alguns dados das classes de Modelo.
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */
public class Servicos {
	
	/**
	 * Método que valida o e-mail de um cliente. Nesse caso, o e-mail deve conter o '@' e não pode começar com '@'.
	 * @param email -> E-mail a ser verificado
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o e-mail seja válido.
	 * (2) False/Falso: caso o e-mail seja inválido.
	 */
	public static boolean validaEmail(String email) {
		if(email.contains("@") && !(email.startsWith("@"))) {
			return true;
		}
		return false;
	}
	
	/**
	 * Método que valida o ID de um funcionário. Nesse caso, o ID deve ser maior ou igual a 0.
	 * @param id -> ID a ser verificado.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o ID seja válido.
	 * (2) False/Falso: caso o ID seja inválido.
	 */
	public static boolean validaIDFunc(int id) {
		if(id >= 0) {
			return true;
		}
		return false;
	}
	
	/**
	 * Método que valida o ano de ingresso de um funcionário. Nesse caso, o ano deve ser maior ou igual ao ano de fundação da empresa e menor que 2021 (ano atual).
	 * @param ano -> Ano a ser verificado.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o Ano seja válido.
	 * (2) False/Falso: caso o Ano seja inválido.
	 */
	public static boolean validaAnoIng(int ano) {
		ControleEmpresa dadosEmpresa;
		dadosEmpresa = new ControleEmpresa();
		if(ano >= dadosEmpresa.getEmpresa().getAnoFund() && ano <= 2021) {
			return true;
		}
		return false;
	}
	
	/**
	 * Método que valida o ano de fundação de uma empresa. Nesse caso, o ano deve ter no mínimo 4 dígitos.
	 * @param ano -> Ano a ser verificado.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o Ano seja válido.
	 * (2) False/Falso: caso o Ano seja inválido.
	 */
	public static boolean validaAnoFund(int ano) {
		if(ano >= 1000) { //Ter pelo menos 4 dígitos.
			return true;
		}
		return false;
	}

	
	/**
	 * Método que valida o modelo de um sapato. Nesse caso, o sapato tem que ser um dos três modelos: Casual (C/c), Sandália (S/s) ou Esportivo (E/e).
	 * @param modelo -> Caractér a ser verificado.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o Modelo seja válido.
	 * (2) False/Falso: caso o Modelo seja inválido.
	 */
	public static boolean validaModelo(char modelo) {
		if(modelo == 'C' || modelo == 'c' || modelo == 'S' || modelo == 's' || modelo == 'E' || modelo == 'e'){
			return true;
		}
		return false;
	}
	
	/**
	 * Método que valida a quantidade em estoque de um sapato a ser cadastrado.
	 * @param qtdEstoque -> Quantidade a ser verificada.
	 * @return boolean:
	 * (1) True/Verdadeiro: Caso a quantidade seja válida.
	 * (2) False/Falso: Caso a quantidade seja inválida.
	 */
	public static boolean validaEstoque(int qtdEstoque) {
		if(qtdEstoque > 0) {
			return true;
		}
		return false;
	}
	
	/**
	 * Método que valida a grade de tamanhos de um sapato. Nesse caso, o sapato pode ter tamanho mínimo de 15 e tamanho máximo de 46 (tamanhos comuns).
	 * @param tamanho -> Tamanho a ser verificado.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o Tamanho seja válido.
	 * (2) False/Falso: caso o Tamanho seja inválido.
	 */
	public static boolean validaTamanho(double tamanho) {
		if(tamanho >= 15 && tamanho <= 46) {
			return true;
		}
		return false;
	}
	
	/**
	 * Método que valida o método de pagamento de uma venda. Nesse caso, a venda tem que ter um dos três métodos de pagamento: Cartão (C/c), Boleto (B/b) ou Pix (P/p).
	 * @param metpag -> Caractér a ser verificado.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o Método de Pagamento seja válido.
	 * (2) False/Falso: caso o Método de Pagamento seja inválido.
	 */
	public static boolean validaMetPag(char metpag) {
		if(metpag == 'C' || metpag == 'c' || metpag == 'B' || metpag == 'b' || metpag == 'P' || metpag == 'p'){
			return true;
		}
		return false;
	}
	
	/**
	 * Método que valida ser um valor double é maior que zero. Pode ser usado em mais de um caso no programa.
	 * @param valor -> Valor double a ser verificado.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o valor seja válido.
	 * (2) False/Falso: caso o valor seja inválido.
	 */
	public static boolean validaDouble(double valor) { 
		if(valor >= 0) {
			return true;
		}
		return false;
	}

}
