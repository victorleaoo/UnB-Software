package controle;

import modelo.Sapato;

/**
 * Classe de Controle da classe Sapato. Possui os principais métodos relacionados a essa classe, como por exemplo: listar os nomes (geral e por modelo), inserir, editar ou remover sapatos.
 * @author mixer
 * @version 1.0 (Out. 2021)
 */
public class ControleSapato extends ControleDados {

	private Sapato[] spt;
	private int qtdSapatos;
	
	/**
	 * Construtor de ControleSapato:
	 * (1) O array de Sapatos será os sapatos atribuídos à lista de Sapatos.
	 * (2) A quantidade será setada pela quantidade de elementos no array de Sapatos.
	 */
	public ControleSapato() {
		super();
		spt = this.getLista();
		this.setQtd(super.getQtdeLista(spt));
	}
	
	/**
	 * Método que retorna um array (lista) contendo os sapatos cadastrados no software.
	 * @return Sapato[]
	 */
	@Override
	public Sapato[] getLista() {
		return super.getDados().getdSapatos();
	}
	
	/**
	 * Cria um array com os nomes dos sapatos. Será usado na camada view para listar os sapatos cadastrados, independente de seus modelos.
	 * @return Array de String com o nome de cada sapato.
	 */
	public String[] getNomeSpts() {
		String[] s = new String[getQtd()];
		for(int i = 0; i < getQtd(); i++) {
			s[i] = spt[i].getNomeSapato();
		}
		
		return s;
	}
	
	
	public int getQtd() {
		return this.qtdSapatos;
	}

	public void setQtd(int qtd) {
		this.qtdSapatos = qtd;
	}
	
		
	/**
	 * Método que insere um novo sapato cadastrado. Com isso, o número de sapatos é acrescido em 1.
	 * @param dadosSapato -> Um array de String com os dados do novo Sapato a ser inserido.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o sapato tenha sido inserido com sucesso.
	 * (2) False/Falso: caso ocorra um erro ao inserir o sapato, provavelmente algum dado com tipo ou valor inválido.
	 */
	@Override
	public boolean inserir(String[] dadosSapato) {
		if(editar(dadosSapato)) {
			setQtd(getQtd()+1);
			return true;
		}
		return false;
	}
	
	/**
	 * Método que edita os dados de um Sapato (menos o diretório de imagem, uma vez que mostrará o ImageIcon).
	 * @param dadosSapato -> Um array de String com os novos dados do Sapato a ser editado.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o sapato tenha sido editado com sucesso.
	 * (2) False/Falso: caso ocorra um erro ao editar o funcionário, provavelmente algum dado com tipo ou valor inválido.
	 */
	public boolean editar(String[] dadosSapato) { 
		if(Servicos.validaModelo(dadosSapato[3].toCharArray()[0]) && Servicos.validaDouble(Double.valueOf(dadosSapato[4])) && Servicos.validaTamanho(Double.valueOf(dadosSapato[5])) && Servicos.validaTamanho(Double.valueOf(dadosSapato[6])) && Servicos.validaEstoque(Integer.valueOf(dadosSapato[8]))) {
			Sapato s = new Sapato(dadosSapato[1], dadosSapato[2], dadosSapato[3].toCharArray()[0], Double.valueOf(dadosSapato[4]),
					Double.valueOf(dadosSapato[5]), Double.valueOf(dadosSapato[6]), dadosSapato[7],
					Integer.valueOf(dadosSapato[8]), dadosSapato[9]);
			getDados().inserirEditaSapato(s, Integer.parseInt(dadosSapato[0]));
			return true;
		}
		return false;
	}
	
	/**
	 * Método que remove um Sapato. Com isso, o número de sapatos é reduzido em 1 e as posições dos sapatos ajustadas.
	 * @param i -> Posição do sapato a ser removido.
	 * @return boolean:
	 * (1) True/Verdadeiro: caso o sapato tenha sido removido com sucesso.
	 * (2) False/Falso: caso ocorra um erro ao remover o sapato, provavelmente o usuário não tenha dado o refresh após alguma alteração na lista.
	 */
	@Override
	public boolean remover(int i) { 
		if(i > getQtd()) {
			return false;
		}
		
		spt = this.getLista();
		String sapatoRemovido = spt[i].getNomeSapato();		
		
		if(i == (getQtd() -1)) {  //Se o sapato a ser removido está no final do array
			spt[i] = null;
			setQtd(getQtd()-1);
			return true;
		}
		
		int cont = 0;
		while(spt[cont].getNomeSapato().compareTo(sapatoRemovido) != 0) {
			cont++;
		}
		
		for (int j = cont; j < getQtd() - 1; j++) {			
			spt[j] = spt[j+1];
		}
		spt[getQtd()-1] = null;
		setQtd(getQtd() - 1);
		return true;
	}
	
	/**
	 * Cria um array com os nomes dos sapatos com modelo igual a Casual. Será usado na camada view para filtrar os sapatos cadastrados.
	 * @return Array de String com o nome de cada sapato com modelo 'C'/'c'.
	 */
	public String[] getNomeCasual() {
		String[] s = new String[qtdSapatos];
		for(int i = 0; i < qtdSapatos; i++) {
			if(spt[i].getModelo() == 'C' || spt[i].getModelo() == 'c') {
				s[i] = spt[i].getNomeSapato();
			}	
		}
		
		return s;
	}

	/**
	 * Cria um array com os nomes dos sapatos com modelo igual a Sandália. Será usado na camada view para filtrar os sapatos cadastrados.
	 * @return Array de String com o nome de cada sapato com modelo 'S'/'s'.
	 */
	public String[] getNomeSandalia() {
		String[] s = new String[qtdSapatos];
		for(int i = 0; i < qtdSapatos; i++) {
			if(spt[i].getModelo() == 'S' || spt[i].getModelo() == 's') {
				s[i] = spt[i].getNomeSapato();
			}	
		}
		
		return s;
	}
	
	/**
	 * Cria um array com os nomes dos sapatos com modelo igual a Esportivo. Será usado na camada view para filtrar os sapatos cadastrados.
	 * @return Array de String com o nome de cada sapato com modelo 'E'/'e'.
	 */
	public String[] getNomeEsportivo() {
		String[] s = new String[qtdSapatos];
		for(int i = 0; i < qtdSapatos; i++) {
			if(spt[i].getModelo() == 'E' || spt[i].getModelo() == 'e') {
				s[i] = spt[i].getNomeSapato();
			}	
		}
		
		return s;
	}
	
	public String getNome(int i) {		
		return spt[i].getNomeSapato();
	}
	
	public String getMarca(int i) {		
		return spt[i].getMarca();
	}
	
	public String getModelo(int i) {	
		String modelo = String.valueOf(spt[i].getModel());
		return modelo;
	}
	
	public String getPreco(int i) {		
		String preco = String.valueOf(spt[i].getPreco());
		return preco;
	}
	
	public String getMenorTam(int i) {
		String menorTam = String.valueOf(spt[i].getMenorTam());
		return menorTam;
	}
	
	public String getMaiorTam(int i) {	
		String maiorTam = String.valueOf(spt[i].getMaiorTam());
		return maiorTam;
	}
	
	public String getDescricao(int i) {		
		return spt[i].getDescricao();
	}
	
	public String getFotoSapato(int i) {		
		return spt[i].getFotoSapato();
	}
	
	public String getEstoque(int i) {
		String estoque = String.valueOf(spt[i].getQntdEstoque());
		return estoque;
	}
	
}
