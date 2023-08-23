package pacoteTestes;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;
import controle.ControleSapato;
import controle.ControleVenda;
import modelo.ItensVenda;
import controle.ControleCliente;

/**
 * Pacote com os testes unitários. 
 * Teste de métodos relacionados ao CRUD das classes, uma vez que são cruciais para o funcionamento do Software (boa parte dele é rodeado por esses). Além do teste da inserção de item em uma venda:
 * (1) crUd: Teste do método de edição. Foi usado o da classe ControleSapato, já que possui uma grande variedade de atributos, mas a lógica desse método é a mesma para as outras classes. Além disso, os métodos de cadastro, também tem uma dinâmica parecida a desse método.
 * (2) cruD: Teste do método de remoção. Foi usado o da classe ControleCliente, mas para todas as classes, a ideia do método é a mesma.
 * (3) Teste do método de inserção de um item em uma venda. 
 * @author Victor Leão
 * @version 1.0 (Out. 2021)
 */
class TesteCRUD {
	
	ControleSapato s = new ControleSapato();
	ControleCliente c = new ControleCliente();
	ControleVenda v = new ControleVenda();
	
	@Test
	void testEditar() {
		String[] teste1 = {"1", "Sapato 1", "Marca 1", "C", "1000.00", "37.0", "40.0", "Tênis casual, marca 1", "25", "imagens/airjordan-obsidian.jpg"};
		String[] teste2 = {"2", "Sapato 2", "Marca 2", "S", "-5000.00", "10.0", "40.0", "Tênis kine, marca 2", "50", "imagens/slx-rider.jpg"};
		String[] teste3 = {"3", "Sapato 3", "Marca 3", "K", "1000.00", "37.0", "40.0", "Tênis casual, marca 1", "25", "imagens/dunk-brazil.png"};
		assertEquals(true, s.editar(teste1));
		assertEquals(false, s.editar(teste2));
		assertEquals(false, s.editar(teste3));
	}

	@Test
	void testRemover() {
		assertTrue(c.remover(0));
		assertFalse(c.remover(10));
	}

	
	@Test
	void testAddItem() {
		ItensVenda item1 = new ItensVenda(s.getDados().getdSapatos()[0], 1);
		ItensVenda item2 = new ItensVenda(s.getDados().getdSapatos()[0], 30);
		assertTrue(v.addItem(item1, 1));
		assertFalse(v.addItem(item2, 1));
	}
}
