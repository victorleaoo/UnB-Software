package view;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.border.TitledBorder;
import javax.swing.table.DefaultTableModel;

import controle.ControleVenda;
import modelo.ItensVenda;
import modelo.Venda;

/**
 * Tela que apresenta os dados da Venda (vazios ou preenchidos dependendo do selecionado na TelaVenda). Pode-se alterar os dados da Venda ou excluí-la. Além disso, pode-se excluir os Itens de uma Venda.
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */
public class TelaDetalheVenda implements ActionListener {
	private JPanel janela;
	private JPanel pai;
	private JPanel editarVenda;
	private JPanel cadastrarVenda;
	private JLabel labelCliente = new JLabel("Cliente: ");
	private JTextField valorCliente;
	private JLabel labelFuncionario = new JLabel("Funcionário: ");
	private JTextField valorFuncionario;
	private JLabel labelMetPag = new JLabel("Método de Pagamento: ");
	private JTextField valorMetPag;
	private JLabel labelID = new JLabel("ID da venda: ");
	private JTextField valorID;
	private JButton botaoAlterar = new JButton("Salvar");
	private JButton botaoExcluir = new JButton("Excluir");
	private JButton botaoVoltar = new JButton("Voltar");
	private JButton botaoVoltarCadastro = new JButton("Voltar");
	private JButton botaoSalvar = new JButton("Salvar");
	private JButton botaoItem = new JButton("Adicionar Item");
	private String[] novoDado = new String[9];
	private static ControleVenda dados;
	private int posicao;
	
	private Venda venda;
	private JTable table = new JTable();
	
	/**
	 * Design dos elementos da tela.
	 * @param d -> Dados de Venda.
	 * @return JPanel: uma vez que a TelaVenda e essa tela são a mesma.
	 */
	public JPanel inserirEditar(ControleVenda d) {
			
		dados = d;
			
		janela = new JPanel(new GridLayout(2, 2));
		
		this.janela.setSize(900, 400);
		
		venda = null;		
		valorCliente = new JTextField(200);
		valorFuncionario = new JTextField(200);
		valorMetPag = new JTextField(1);	
		valorID = new JTextField(2);				
										
		table.setName("table");
		table.setModel(createTableModel());
		
		JPanel panel = new JPanel();
		panel.setBorder(BorderFactory.createTitledBorder(
		         BorderFactory.createEtchedBorder(), "Itens", TitledBorder.CENTER, TitledBorder.TOP));
		var scrollPane = new JScrollPane(table);
		scrollPane.setSize(200, 50);
		panel.add(scrollPane);						
		
		JPanel panelDados = new JPanel(new GridLayout(5, 2));
				
		editarVenda = new JPanel();
		editarVenda.add(botaoAlterar);
		editarVenda.add(botaoVoltar);
		editarVenda.add(botaoExcluir);
		editarVenda.add(botaoItem);
		editarVenda.setVisible(true);
		cadastrarVenda = new JPanel();						
		cadastrarVenda.setSize(400, 400);
		cadastrarVenda.add(botaoVoltarCadastro);
		cadastrarVenda.add(botaoSalvar);
		cadastrarVenda.setVisible(false);
								
		panelDados.add(labelCliente);
		panelDados.add(valorCliente);
		panelDados.add(labelFuncionario);
		panelDados.add(valorFuncionario);
		panelDados.add(labelMetPag);
		panelDados.add(valorMetPag);
		panelDados.add(labelID);
		panelDados.add(valorID);
		panelDados.add(editarVenda);
		panelDados.add(cadastrarVenda);
		
		janela.add(panelDados);
		janela.add(panel);
				
		this.janela.setVisible(true);
		
		botaoAlterar.addActionListener(this);
		botaoExcluir.addActionListener(this);
		botaoVoltarCadastro.addActionListener(this);
		botaoVoltar.addActionListener(this);
		botaoItem.addActionListener(this);
		botaoSalvar.addActionListener(this);		
		table.setRowSelectionAllowed(true);
        table.setColumnSelectionAllowed(false);        
        table.addMouseListener(new MouseAdapter() {
        	public void mouseClicked(MouseEvent e) {
				 JTable target = (JTable)e.getSource();
				 int row = target.getSelectedRow();
				 var confirma = JOptionPane.showConfirmDialog(pai, "Deseja excluir esse item?");
				 if(confirma == JOptionPane.YES_OPTION) {								 
					 for(ItensVenda item : venda.getSapatos()) {
						 if(item.getS().getNomeSapato().equals(table.getValueAt(row, 0).toString())) {
							 dados.deletarItem(item, posicao);
							 venda = dados.getLista()[posicao];
							 var mTable = createTableModel();
							 for (ItensVenda item1 : venda.getSapatos()) {				
								mTable.addRow(new Object[]{
										item1.getS().getNomeSapato(), item1.getQntdVenda(), false});
							 }			
							 table.setModel(mTable);
							 table.updateUI();
						 }
					 }		
				 }					 
			 }
		});	
        
		return janela;
	}

	/**
	 * Set do JPanel pai.
	 * @param pai -> JPanel pai
	 */
	public void setParent(JPanel pai) {
		this.pai = pai;
	}
	
	/**
	 * Set dos dados de uma venda que vai ser alterada ou cadastrada.
	 * @param pos -> Analisa se deve mostrar os dados de uma venda ou os JTextField vazios para que se possa cadastrar uma nova Venda.
	 */
	public void setVenda(int pos) {
		posicao = pos;
		if(pos >= 0) {	
			venda = dados.getLista()[pos];						
			valorCliente.setText(venda.getC().getNome());
			valorFuncionario.setText(venda.getF().getNome());
			valorMetPag.setText(String.valueOf(venda.getMetPag()));
			valorID.setText(String.valueOf(venda.getID()));
			var mTable = createTableModel();
			var itens = venda.getSapatos();			
			for (ItensVenda item : itens) {				
				mTable.addRow(new Object[]{
						item.getS().getNomeSapato(), item.getQntdVenda(), false});
			}			
			table.setModel(mTable);
			cadastrarVenda.setVisible(false);
			editarVenda.setVisible(true);		
		}
		else {
			valorCliente.setText(null);
			valorFuncionario.setText(null);
			valorMetPag.setText(null);
			valorID.setText(null);
			cadastrarVenda.setVisible(true);
			editarVenda.setVisible(false);
			table.setModel(createTableModel());
		}
	}

	@SuppressWarnings("serial")
	private DefaultTableModel createTableModel() {		
		return new DefaultTableModel(null, new String[] { "Nome", "Quantidade" }) {
		    public boolean isCellEditable(int row, int column)
		    {
		      return false;
		    }
		};
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		Object src = e.getSource();
		
		janela.setVisible(false);
		this.pai.setVisible(true);		
		
		if(src == botaoSalvar) {
			try {
				boolean res;				
				novoDado[1] = valorMetPag.getText();
				novoDado[2] = valorFuncionario.getText();
				novoDado[3] = valorCliente.getText();
				novoDado[4] = valorID.getText();
				novoDado[0] = Integer.toString(dados.getQtd());
				res = dados.inserir(novoDado);
								
				if(res) {
					mensagemSucessoCadastro();
				} else mensagemErroCadastro();
			}
			catch (NullPointerException exc1) {
				mensagemErroCadastro();
			} catch (NumberFormatException exc2) {
				mensagemErroCadastro();
			}
		}
		
		if(src == botaoAlterar) {
			try {
				boolean res;
				novoDado[1] = valorMetPag.getText();
				novoDado[2] = valorFuncionario.getText();
				novoDado[3] = valorCliente.getText();
				novoDado[4] = valorID.getText();
				novoDado[0] = Integer.toString(posicao);
				res = dados.editar(novoDado);
												
				if(res) {
					mensagemSucessoCadastro();
				} else mensagemErroCadastro();
			}
			catch (NullPointerException exc1) {
				mensagemErroCadastro();
			} catch (NumberFormatException exc2) {
				mensagemErroCadastro();
			}
		}
		
		if(src == botaoExcluir) { 
			boolean res = false;
		 
		//exclui cliente
			res = dados.remover(posicao);
			if (res) mensagemSucessoExclusao(); 
			else mensagemErroExclusao(); 
		}
		
		if(src == botaoItem) {
			new TelaInserirItem().inserirItem(posicao);
		}
	}
	
	/**
	 * Mensagem de Sucesso de cadastro.
	 */
	public void mensagemSucessoCadastro() {
		JOptionPane.showMessageDialog(null, "Os dados foram salvos com sucesso!", null, 
				JOptionPane.INFORMATION_MESSAGE);
	}
	
	/**
	 * Mensagem de Sucesso de exclusão.
	 */
	public void mensagemSucessoExclusao() {
		JOptionPane.showMessageDialog(null, "Os dados foram excluidos com sucesso!", null, 
				JOptionPane.INFORMATION_MESSAGE);
	}
	
	/**
	 * Mensagem de Erro de cadastro.
	 * Aparece caso todos os campos não estejam preenchidos, dados com tipo inválido ou cliente/funcionário inserido inexistente.
	 */
	public void mensagemErroCadastro() {
		JOptionPane.showMessageDialog(null,"ERRO AO SALVAR OS DADOS!\n " + "Nem todos os campos foram preenchidos, \n"
	+ "Dados com tipos inválidos\n" + "OU Cliente/Funcionário inexistente.", null, 
				JOptionPane.ERROR_MESSAGE);
	}
	
	/**
	 * Mensagem de Erro de exclusão
	 */
	public void mensagemErroExclusao() {
		JOptionPane.showMessageDialog(null,"Ocorreu um erro ao excluir o dado.\n"+ 
							"Dê o refresh antes de excluir a próxima venda.", null, 
				JOptionPane.ERROR_MESSAGE);
	}
}
