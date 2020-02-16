package tortegelato;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.*;

public class TestTorteGelato {


	//Test che l'oggetto venga creato e non sia nullo
	@Test
	public void testInit() {
		
		DirectedGraph g = new DirectedGraph("6;0 1;0 2;0 3;0 5;1 4;1 3;2 5;2 3;3 4;");
		TorteGelato torte = new TorteGelato(g,2,3);
		assertNotNull(torte);
	}

	//Test suggeriti dalla consegna
	@Test
	public void testGhiaccioMinimo()
	{
		DirectedGraph g = new DirectedGraph("5;0 1 6;0 2 2;1 4 3;1 3 2;2 4 6;2 3 2;3 4 2;3 1 1;");
		TorteGelato torte = new TorteGelato(g,2,3);
		assertEquals(torte.ghiaccioMinimo(4,3),36);
		assertEquals(torte.ghiaccioMinimo(1,5),45);
		assertEquals(torte.ghiaccioMinimo(0,2),-1);

	}
	
	@Test (expected = IllegalArgumentException.class)
	public void testGhiaccioMinimoDestnonAmmissibile() 
	{
		DirectedGraph g = new DirectedGraph("5;0 1 6;0 2 2;1 4 3;1 3 2;2 4 6;2 3 2;3 4 2;3 1 1;");
		TorteGelato torte = new TorteGelato(g,2,3);
		torte.ghiaccioMinimo(7,1);
	}
	

	@Test (expected = IllegalArgumentException.class)
	public void testGhiaccioMinimoWeightNeg() 
	{
		DirectedGraph g = new DirectedGraph("5;0 1 6;0 2 2;1 4 3;1 3 2;2 4 6;2 3 2;3 4 2;3 1 1;");
		TorteGelato torte = new TorteGelato(g,2,3);
		torte.ghiaccioMinimo(3,-5);
	}

}
