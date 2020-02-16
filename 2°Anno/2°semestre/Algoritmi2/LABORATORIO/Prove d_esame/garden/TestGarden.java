package garden;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.UndirectedGraph;

public class TestGarden {

	@Test
	public void testcable() {
		UndirectedGraph g = new UndirectedGraph("6;0 5 11;5 2 8;0 2 13;0 4 10;2 1 7;4 1 9;4 3 8;3 1 15");      
		Garden gn = new Garden(g);
		assertEquals(gn.cable(5, 2),8);
		assertEquals(gn.cable(0, 5),-1);
		assertEquals(gn.cable(-1, 4),42);

	}
	
	@Test (expected = IllegalArgumentException.class)
	public void testEccezione()
	{
		UndirectedGraph g = new UndirectedGraph("6;0 5 11;5 2 8;0 2 13;0 4 10;2 1 7;4 1 9;4 3 8;3 1 15");      
		Garden gn = new Garden(g);
		gn.cable(8, 0);
	}

}
