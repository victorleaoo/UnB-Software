package view;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.ListModel;
import javax.swing.ListSelectionModel;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import controle.ControleVenda;

/**
 * Tela que lista as vendas (funcionário - cliente - ID). Pode-se selecionar alguma Venda na lista para o alterar ou excluir. Também há o botão de cadastro e o de refresh da lista.
 * Há a possibilidade de buscar as vendas pelo nome do funcionário.
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */
public class TelaVenda implements ActionListener, ListSelectionListener {
	private JFrame janela = new JFrame("Vendas");
	private JLabel titulo = new JLabel("Controle de Vendas");
	private JButton botaoCadastrar = new JButton("Cadastrar Venda");
	private JButton refresh = new JButton("Refresh");
	private JTextField busca;
	public static ControleVenda dados;
	private JList<String> listaVendasCadastradas = new JList<String>(createDefaultListModel());
	private String[] listaNomeVendas = new String[50];
	private JPanel panelListaVendas = new JPanel();
	private JPanel manterVenda;
	private TelaDetalheVenda telaDetalheVenda = new TelaDetalheVenda();
	
	/**
	 * Cria o TextField em que se buscará o nome dos funcionários na lista.
	 * @return TextField
	 */
	public JTextField createTextField() {
		final JTextField field = new JTextField("Nome do Funcionário", 200);
        field.getDocument().addDocumentListener(new DocumentListener(){
            @Override public void insertUpdate(DocumentEvent e) { filter(); }
            @Override public void removeUpdate(DocumentEvent e) { filter(); }
            @Override public void changedUpdate(DocumentEvent e) {}
            private void filter() {            	
                filterModel(field.getText());
            }
        });
        return field;
	}
	
	/**
	 * Cria ListModel de vendas (com todas as vendas).
	 * @return ListModel<String>
	 */
	private ListModel<String> createDefaultListModel(){
		dados = new ControleVenda();
		return getModel("");
	}
	
	/**
	 * Atualiza a lista de vendas enquanto ocorre a busca.
	 * @param filter -> String que o usuário escreve em busca da venda pelo nome do funcionário.
	 */
    public void filterModel(String filter) {
    	listaVendasCadastradas.setModel(getModel(filter)); 
    	listaVendasCadastradas.updateUI();
    }
    
    /**
     * Sistema de busca de Venda por nome do funcionário.
     * @param filter -> String que o usuário escreve em busca do venda pelo funcionário (em branco, mostra todos).
     * @return ListModel<String>
     */
	private ListModel<String> getModel(String filter) {
		DefaultListModel<String> model = new DefaultListModel<>();
		listaNomeVendas = dados.getNomeVendas();
        for (String s : listaNomeVendas) {        	
        	if("".equals(filter.trim()) || s.startsWith(filter)) {
        		model.addElement(s);
        	}        	
        }
        return model;
	}
	
	/**
     * Design dos elementos da Tela.
     */
	public void mostrarVendas() {
		
		busca = createTextField();
						
		listaVendasCadastradas.setBounds(20, 50, 350, 120);
		listaVendasCadastradas.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		listaVendasCadastradas.setVisibleRowCount(10);
		titulo.setFont(new Font("Helvetica", Font.BOLD, 20));		
		titulo.setBounds(95, 0, 250, 30);
		busca.setBounds(220, 30, 150, 20);
		botaoCadastrar.setBounds(70, 177, 100, 30);
		refresh.setBounds(200, 177, 100, 30);
						
		panelListaVendas.setLayout(null);
		panelListaVendas.add(titulo);
		panelListaVendas.add(listaVendasCadastradas);
		panelListaVendas.add(botaoCadastrar);
		panelListaVendas.add(refresh);
		janela.add(busca);
		panelListaVendas.setSize(550, 400);
		
		//janela.setLayout(null);
		janela.getContentPane().add(BorderLayout.CENTER, panelListaVendas);
				
		manterVenda = telaDetalheVenda.inserirEditar(dados);
		telaDetalheVenda.setParent(panelListaVendas);
		
		manterVenda.setVisible(false);
		janela.getContentPane().add(BorderLayout.CENTER, manterVenda);
		
		janela.setSize(710, 400);
		janela.setLocationRelativeTo(null);
		janela.setVisible(true);
		
		botaoCadastrar.addActionListener(this);
		refresh.addActionListener(this);
		listaVendasCadastradas.addListSelectionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		Object src = e.getSource();
		
		//Cadastro de nova Venda
		if(src == botaoCadastrar) {
			janela.setTitle("Cadastrar Venda");
			telaDetalheVenda.setVenda(-1);
			panelListaVendas.setVisible(false);
			busca.setVisible(false);
			manterVenda.setVisible(true);
		}
		
		if(src == refresh) {
			listaVendasCadastradas.setListData(dados.getNomeVendas());
			listaVendasCadastradas.updateUI();
			busca.setVisible(true);
		}		
	}
	
	@Override
	public void valueChanged(ListSelectionEvent e) {
		Object src = e.getSource();
		
		if(e.getValueIsAdjusting() && src == listaVendasCadastradas) {
			janela.setTitle("Editar Venda");
			telaDetalheVenda.setVenda(listaVendasCadastradas.getSelectedIndex());
			panelListaVendas.setVisible(false);
			busca.setVisible(false);
			manterVenda.setVisible(true);
		}
		
	}
}
