package view;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import controle.ControleSapato;
import controle.ControleVenda;
import modelo.ItensVenda;

/**
 * Tela para inserir item a uma venda. Lista os sapatos, podendo, então, selecionar um e adicionar a quantidade vendida.
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */
public class TelaInserirItem implements ActionListener, ListSelectionListener {
	private JFrame janela = new JFrame("Inserir Item em Venda");
	private JLabel titulo = new JLabel("Inserção de Item");
	private JButton inserirItem = new JButton("Inserir");
	private JLabel labelQntdVendida = new JLabel("Quantidade vendida: ");
	private JTextField valorQntdVendida;
	private int posicao;
	public static ControleVenda dados;
	public static ControleSapato dadosSapatos;
	private JList<String> listaSapatosCadastrados;
	private String[] listaNomesSapatos = new String[50];
	
	private int indexSapato;
	private ItensVenda item;
	
	/**
	 * Design dos elementos da Tela.
	 * @param pos -> Posição da venda em que o item será inserido.
	 */
	public void inserirItem(int pos) {
		
		posicao = pos;
		
		dadosSapatos = new ControleSapato();
		
		listaNomesSapatos = dadosSapatos.getNomeSpts();
		listaSapatosCadastrados = new JList<String>(listaNomesSapatos);
		
		titulo.setFont(new Font("Helvetica", Font.BOLD, 20));
		titulo.setBounds(115, 10, 250, 30);
		listaSapatosCadastrados.setBounds(20, 50, 350, 120);
		listaSapatosCadastrados.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		listaSapatosCadastrados.setVisibleRowCount(10);
		
		valorQntdVendida = new JTextField(4);
		
		labelQntdVendida.setBounds(30, 180, 150, 25);
		valorQntdVendida.setBounds(180, 180, 180, 25);
		
		inserirItem.setBounds(140, 220, 100, 30);
		
		janela.setLayout(null);
		janela.setLocationRelativeTo(null);

		janela.add(titulo);
		janela.add(listaSapatosCadastrados);
		janela.add(inserirItem);
		janela.add(labelQntdVendida);
		janela.add(valorQntdVendida);

		janela.setSize(400, 300);
		janela.setVisible(true);
		
		inserirItem.addActionListener(this);
		listaSapatosCadastrados.addListSelectionListener(this);
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		Object src = e.getSource();

		if(e.getValueIsAdjusting() && src == listaSapatosCadastrados) {
			indexSapato = listaSapatosCadastrados.getSelectedIndex();
		}
		
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object src = e.getSource();
		
		if(src == inserirItem) {
			try {
				boolean res;
				dados = new ControleVenda();
				item = new ItensVenda(dadosSapatos.getDados().getdSapatos()[indexSapato], Integer.valueOf(valorQntdVendida.getText()));
				res = dados.addItem(item, posicao);
				if (res) {
					mensagemSucessoCadastro();
				}else {
					mensagemErroCadastro();
				}
				
			}
			catch (NullPointerException exc1) {
				exc1.printStackTrace();
				mensagemErroCadastro();
			} catch (NumberFormatException exc2) {
				exc2.printStackTrace();
				mensagemErroCadastro();
			}
		}
		
	}
	
	/**
	 * Mensagem de Sucesso de inserção.
	 */
	public void mensagemSucessoCadastro() {
		JOptionPane.showMessageDialog(null, "Item adicionado com sucesso!", null, 
				JOptionPane.INFORMATION_MESSAGE);
		janela.dispose();
	}
	
	/**
	 * Mensagem de Erro de inserção.
	 * Aparece caso todos os campos não estejam preenchidos ou a quantidade vendida é inválida.
	 */
	public void mensagemErroCadastro() {
		JOptionPane.showMessageDialog(null,"ERRO AO SALVAR OS DADOS!\n " + "Nem todos os campos foram preenchidos OU \n" + "Quantidade vendida maior que a quantidade em Estoque!", null, 
				JOptionPane.ERROR_MESSAGE);
	}
}
