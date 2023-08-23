package view;

import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

/**
 * Menu principal do sistema, em que, por meio de botões, pode-se acessar as telas das outras classes.
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */

public class MenuPrincipal implements ActionListener {
	
	private static JFrame janela = new JFrame("Loja de Sapatos");
	private static JLabel titulo = new JLabel("Tela Inicial");
	private static JButton empresa = new JButton("Empresa");
	private static JButton sapato = new JButton("Sapato");
	private static JButton cliente = new JButton("Cliente");
	private static JButton funcionario = new JButton("Funcionário");
	private static JButton venda = new JButton("Venda");
	
	/**
	 * Design dos elementos do Menu.
	 */
	public MenuPrincipal() {
		titulo.setFont(new Font("Helvetica", Font.BOLD, 20));
		titulo.setBounds(140, 10, 150, 30); //Posição X, Posição Y, Tamanho X, Tamanho Y
		
		janela.setLayout(null);
		janela.setLocationRelativeTo(null);
		
		empresa.setBounds(140, 60, 100, 30);
		sapato.setBounds(140, 100, 100, 30);
		cliente.setBounds(140, 140, 100, 30);
		funcionario.setBounds(140, 180, 100, 30);
		venda.setBounds(140, 220, 100, 30);
		
		janela.add(titulo);
		janela.add(empresa);
		janela.add(sapato);
		janela.add(cliente);
		janela.add(funcionario);
		janela.add(venda);
		
		janela.setSize(400, 350);
		janela.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		janela.setVisible(true);
	}
	
	public static void main(String[] args) {
		MenuPrincipal menu = new MenuPrincipal();

		empresa.addActionListener(menu);
		sapato.addActionListener(menu);
		cliente.addActionListener(menu);
		funcionario.addActionListener(menu);
		venda.addActionListener(menu);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		Object src = e.getSource();
		
		if(src == empresa) 
			new TelaEmpresa().mostrarEmpresa();
		
		if(src == sapato) 
			new TelaSapato().mostrarSapatos();
		
		if(src == cliente) 
			new TelaCliente().mostrarClientes();
		
		if(src == funcionario) 
			new TelaFuncionario().mostrarFuncionarios();
		
		if(src == venda) 
			new TelaVenda().mostrarVendas();
	}

}
