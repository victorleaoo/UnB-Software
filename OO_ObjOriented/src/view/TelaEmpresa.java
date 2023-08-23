package view;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import controle.ControleEmpresa;

/**
 * Tela que apresenta os dados da Empresa. Pode-se alterar os dados da Empresa ou apagá-los.
 * Caso os dados estejam vazios (Empresa foi deletada), o botão de cadastrar empresa ficará ativo e o usuário poderá cadastrá-la.
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */
public class TelaEmpresa implements ActionListener {
	private JFrame janela = new JFrame("Empresa");
	private JLabel titulo = new JLabel("Controle da Empresa");
	private JButton botaoCadastrar = new JButton("Cadastrar Empresa");
	private JButton botaoAlterar = new JButton("Alterar Dados");
	private JButton botaoExcluir = new JButton("Apagar Dados");
	private JLabel labelNome = new JLabel("Nome: ");
	private JTextField valorNome;
	private JLabel labelCNPJ = new JLabel("CNPJ: ");
	private JTextField valorCNPJ;
	private JLabel labelAnoFund = new JLabel("Ano de Fundação: ");
	private JTextField valorAnoFund;
	private JLabel labelTelefone = new JLabel("Telefone: ");
	private JTextField valorTelefone;
	private JLabel labelEndereco = new JLabel("Endereço: ");
	private JTextField valorEndereco;
	public static ControleEmpresa dados;
	private String[] novoDado = new String[9];
	
	
    /**
     * Design dos elementos da Tela.
     */
	public void mostrarEmpresa() {
		dados = new ControleEmpresa();
		
		titulo.setFont(new Font("Helvetica", Font.BOLD, 20));
		titulo.setBounds(90, 10, 250, 30);
		
		if(dados.getEmpresa() == null) {
			valorNome = new JTextField(200);
			valorCNPJ = new JTextField(200);
			valorAnoFund = new JTextField(200);
			valorTelefone = new JTextField(200);
			valorEndereco = new JTextField(200);
		} else {
			valorNome = new JTextField(dados.getEmpresa().getNomeEmpresa(), 200);
			valorCNPJ = new JTextField(dados.getEmpresa().getCNPJ(), 200);
			valorAnoFund = new JTextField(String.valueOf(dados.getEmpresa().getAnoFund()), 200);
			valorTelefone = new JTextField(dados.getEmpresa().getTelEmpresa(), 200);
			valorEndereco = new JTextField(dados.getEmpresa().getEndEmpresa(), 200);
		}
		
		labelNome.setBounds(30, 20, 150, 25);
		valorNome.setBounds(190, 20, 180, 25);
		labelCNPJ.setBounds(30, 50, 150, 25);
		valorCNPJ.setBounds(190, 50, 180, 25);	
		labelAnoFund.setBounds(30, 80, 150, 25);
		valorAnoFund.setBounds(190, 80, 180, 25);	
		labelTelefone.setBounds(30, 110, 150, 25);
		valorTelefone.setBounds(190, 110, 180, 25);	
		labelEndereco.setBounds(30, 140, 150, 25);
		valorEndereco.setBounds(190, 140, 180, 25);
		
		botaoCadastrar.setBounds(20, 175, 110, 30);
		botaoAlterar.setBounds(140, 175, 110, 30);
		botaoExcluir.setBounds(260, 175, 110, 30);
		
		this.janela.add(labelNome);
		this.janela.add(valorNome);
		this.janela.add(labelCNPJ);
		this.janela.add(valorCNPJ);
		this.janela.add(labelAnoFund);
		this.janela.add(valorAnoFund);
		this.janela.add(labelTelefone);
		this.janela.add(valorTelefone);
		this.janela.add(labelEndereco);
		this.janela.add(valorEndereco);
		
		this.janela.add(botaoCadastrar);
		this.janela.add(botaoAlterar);
		this.janela.add(botaoExcluir);

		this.janela.setLayout(null);
		janela.setLocationRelativeTo(null);

		this.janela.setSize(405, 250);
		this.janela.setVisible(true);
		
		botaoCadastrar.addActionListener(this);
		botaoCadastrar.setEnabled(dados.getEmpresa() == null);
		botaoAlterar.addActionListener(this);
		botaoExcluir.addActionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		Object src = e.getSource();
		
		//Cadastro de nova empresa
		if(src == botaoCadastrar) {
			try {
				boolean res;
				novoDado[0] = Integer.toString(dados.getQtd());
				novoDado[1] = valorNome.getText();
				novoDado[2] = valorCNPJ.getText();
				novoDado[3] = valorAnoFund.getText();
				novoDado[4] = valorTelefone.getText();
				novoDado[5] = valorEndereco.getText();
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
			
		if(src == botaoAlterar) {
			boolean res;
			novoDado[1] = valorNome.getText();
			novoDado[2] = valorCNPJ.getText();
			novoDado[3] = valorAnoFund.getText();
			novoDado[4] = valorTelefone.getText();
			novoDado[5] = valorEndereco.getText();
			res = dados.editar(novoDado);
			
			if(res) {
				mensagemSucessoCadastro();
			} else mensagemErroCadastro();
		}
		
		if(src == botaoExcluir) {
			boolean res = false;
			 
			//exclui empresa
			res = dados.remover(1);
			if (res) mensagemSucessoExclusao(); 
			else mensagemErroExclusao();
		}
	}
	
	/**
	 * Mensagem de Sucesso de cadastro.
	 */
	public void mensagemSucessoCadastro() {
		JOptionPane.showMessageDialog(null, "Os dados foram alterados com sucesso!", null, 
				JOptionPane.INFORMATION_MESSAGE);
	}
	
	/**
	 * Mensagem de Sucesso de exclusão.
	 */
	public void mensagemSucessoExclusao() {
		JOptionPane.showMessageDialog(null, "Os dados foram excluidos com sucesso!", null, 
				JOptionPane.INFORMATION_MESSAGE);
		janela.dispose();
	}
	
	/**
	 * Mensagem de Erro de cadastro.
	 * Aparece caso todos os campos não estejam preenchidos ou dados com tipo inválido.
	 */
	public void mensagemErroCadastro() {
		JOptionPane.showMessageDialog(null,"ERRO AO SALVAR OS DADOS!\n " + "Nem todos os campos foram preenchidos OU \n"
	+ "Dados com tipos inválidos", null, 
				JOptionPane.ERROR_MESSAGE);
	}
	
	/**
	 * Mensagem de Erro de exclusão
	 */
	public void mensagemErroExclusao() {
		JOptionPane.showMessageDialog(null,"Ocorreu um erro ao excluir o dado.\n", null, 
				JOptionPane.ERROR_MESSAGE);
	}
	
	
}
