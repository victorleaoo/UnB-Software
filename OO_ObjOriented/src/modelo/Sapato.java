package modelo;

/**
 * Classe modelo de Sapato. Possui seus atributos, construtor e gets/sets.
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */

public class Sapato implements Model {
	
	/**
	 * Atributos de Sapato.
	 */
	private String nomeSapato;
	private String marca;
	private char modelo;
	private double preco;
	private double menorTam;
	private double maiorTam;
	private String descricao;
	private String fotoSapato;
	private int qntdEstoque;

	/**
	 * Construtor de Sapato.
	 * @param nS -> String contendo nome do Sapato.
	 * @param m  -> String contendo marca do Sapato.
	 * @param mod-> Char contendo modelo do Sapato:
	 * (1) 'C'/'c' para Casual
	 * (2) 'S'/'s' para Sandália
	 * (3) 'E'/'e' para Esportivo
	 * @param p  -> Double contendo preço do Sapato.
	 * Grade de Tamanho:
	 * @param men-> Double contendo menor tamanho disponível do Sapato.
	 * @param mai-> Double contendo maior tamanho disponível do Sapato.
	 * @param d  -> String contendo descrição do Sapato.
	 * @param q  -> Int contendo quantidade em estoque do Sapato.
	 * @param img-> String contendo a URL/diretório para a imagem do sapato. Posteriormente, será exibida como ImageIcon.
	 */
	public Sapato(String nS, String m, char mod, double p, double men, double mai, String d, int q, String img) {
		nomeSapato = nS;
		marca = m;
		modelo = mod;
		preco = p;
		menorTam = men;
		maiorTam = mai;
		descricao = d;
		qntdEstoque = q;
		fotoSapato = img;
	}

	public String getNomeSapato() {
		return nomeSapato;
	}
	public void setNomeSapato(String nomeSapato) {
		this.nomeSapato = nomeSapato;
	}

	public String getMarca() {
		return marca;
	}
	public void setMarca(String marca) {
		this.marca = marca;
	}
	
	public char getModelo() {
		return modelo;
	}

	public void setModelo(char modelo) {
		this.modelo = modelo;
	}

	public double getPreco() {
		return preco;
	}
	public void setPreco(double preco) {
		this.preco = preco;
	}

	public double getMenorTam() {
		return menorTam;
	}
	public void setMenorTam(double menorTam) {
		this.menorTam = menorTam;
	}

	public double getMaiorTam() {
		return maiorTam;
	}
	public void setMaiorTam(double maiorTam) {
		this.maiorTam = maiorTam;
	}

	public String getDescricao() {
		return descricao;
	}
	public void setDescricao(String descricao) {
		this.descricao = descricao;
	}
	
	public String getFotoSapato() {
		return fotoSapato;
	}
	public void setFotoSapato(String fotoSapato) {
		this.fotoSapato = fotoSapato;
	}
	
	public int getQntdEstoque() {
		return qntdEstoque;
	}

	public void setQntdEstoque(int qntdEstoque) {
		this.qntdEstoque = qntdEstoque;
	}

	/**
	 * Função para implementar a interface Model (não é realmente usada no programa).
	 * @return String
	 */
	@Override
	public String getModel() {
		return nomeSapato + " - " + marca;
	}
	
}
