package softwaresystem2;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.DirectedGraph;

public class TestSoftwareSystem2 {

	
	//Test per l'inzializzazione
	@Test
	public void testInit() {
		DirectedGraph g = new DirectedGraph("7;0 3;0 4;0 5;1 0;1 3;2 5;3 2;4 1;4 3;6 2");
		SoftwareSystem2 ss= new SoftwareSystem2(g);
		assertNotNull(ss);
		
	
	}
	//Test suggeriti dalla consegna
	@Test
	public void testDepends() {
		DirectedGraph g = new DirectedGraph("7;0 3;0 4;0 5;1 0;1 3;2 5;3 2;4 1;4 3;6 2");
		SoftwareSystem2 ss= new SoftwareSystem2(g);
		assertEquals(ss.depends(3, 1),1);
		assertEquals(ss.depends(5, 4),1);
		assertEquals(ss.depends(3, 5),2);
		assertEquals(ss.depends(3, 6),0);
		assertEquals(ss.depends(0, 4),-3);
		assertEquals(ss.depends(1, 1),-2);
		assertEquals(ss.depends(1, 7),-1);
		assertEquals(ss.depends(8, -3),-1);


		
	
	}


}
