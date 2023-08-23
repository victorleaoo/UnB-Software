package view;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JTextField;
import javax.swing.ListModel;
import javax.swing.ListSelectionModel;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import controle.ControleCliente;

/**
 * Tela que lista os clientes. Pode-se selecionar algum Cliente na lista para o alterar ou excluir. Também há o botão de cadastro e o de refresh da lista.
 * Há a possibilidade de buscar os clientes por seu nome.
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */
public class TelaCliente implements ActionListener, ListSelectionListener {
	private JFrame janela = new JFrame("Clientes");
	private JLabel titulo = new JLabel("Controle de Clientes");
	private JButton cadastrarCliente = new JButton("Cadastrar Cliente");
	private JButton refresh = new JButton("Refresh");
	private JTextField busca;
	public static ControleCliente dados;
	private JList<String> listaClientesCadastrados = new JList<String>(createDefaultListModel());
	private String[] listaNomesClientes = new String[50];
	
	/**
	 * Cria o TextField em que se buscará o nome dos clientes na lista.
	 * @return TextField
	 */
	public JTextField createTextField() {
		final JTextField field = new JTextField("Nome do Cliente", 200);
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
	 * Cria ListModel de clientes (com todos os clientes).
	 * @return ListModel<String>
	 */
	private ListModel<String> createDefaultListModel(){
		dados = new ControleCliente();
		return getModel("");
	}
	
	/**
	 * Atualiza a lista de clientes enquanto ocorre a busca.
	 * @param filter -> String que o usuário escreve em busca do cliente pelo nome.
	 */
    public void filterModel(String filter) {
    	listaClientesCadastrados.setModel(getModel(filter)); 
        listaClientesCadastrados.updateUI();
    }
    
    /**
     * Sistema de busca de Cliente por seu nome.
     * @param filter -> String que o usuário escreve em busca do cliente pelo nome (em branco, mostra todos).
     * @return ListModel<String>
     */
	private ListModel<String> getModel(String filter) {
		DefaultListModel<String> model = new DefaultListModel<>();
		listaNomesClientes = dados.getNomeClientes();
        for (String s : listaNomesClientes) {        	
        	if("".equals(filter.trim()) || s.startsWith(filter)) {
        		model.addElement(s);
        	}        	
        }
        return model;
	}
	
    /**
     * Design dos elementos da Tela.
     */
	public void mostrarClientes() {
		
		busca = createTextField();
		
		titulo.setFont(new Font("Helvetica", Font.BOLD, 20));
		titulo.setBounds(95, 0, 250, 30);
		busca.setBounds(220, 30, 150, 20);
		listaClientesCadastrados.setBounds(20, 50, 350, 120);
		listaClientesCadastrados.setSelectionMode(ListSelectionModel.SINGLE_INTERVAL_SELECTION);
		listaClientesCadastrados.setVisibleRowCount(10);
		
		cadastrarCliente.setBounds(70, 177, 100, 30);
		refresh.setBounds(200, 177, 100, 30);
		
		janela.setLayout(null);

		janela.add(titulo);
		janela.add(listaClientesCadastrados);
		janela.add(cadastrarCliente);
		janela.add(refresh);
		janela.add(busca);

		janela.setSize(400, 250);
		janela.setLocationRelativeTo(null);
		janela.setVisible(true);
		
		cadastrarCliente.addActionListener(this);
		refresh.addActionListener(this);
		listaClientesCadastrados.addListSelectionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		Object src = e.getSource();
		
		//Cadastro de novo cliente
		if(src == cadastrarCliente)
			new TelaDetalheCliente().inserirEditar(1, dados, this, null);
		
		// Atualiza a lista de nomes de clientes mostrada no JList
		if(src == refresh) {
			listaClientesCadastrados.setListData(dados.getNomeClientes());			
			listaClientesCadastrados.updateUI();
		}
		
	}

	@Override
	public void valueChanged(ListSelectionEvent e) {
		Object src = e.getSource();

		if(e.getValueIsAdjusting() && src == listaClientesCadastrados) {
			new TelaDetalheCliente().inserirEditar(2, dados, this, 
					listaClientesCadastrados.getSelectedValue());
		}
	}
	
}
