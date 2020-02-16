package hikes;

import static org.junit.Assert.*;

import org.junit.Test;
import it.uniupo.graphLib.*;

public class TestHikes {
	
	@Test
	public void testCreate()
	{
		UndirectedGraph g = new UndirectedGraph(3);
		Hikes testC = new Hikes(g);
		assertNotNull(testC);
	}
	@Test
	public void testMinDistanza() {
		
		UndirectedGraph g = new UndirectedGraph("10;0 2 9;0 5 6;0 4 17;0 9 8;1 5 12;1 2 15;1 4 18;1 8 13;2 6 7;2 8 5;3 6 16;3 7 19;4 8 14;5 6 10");
		Hikes testC = new Hikes(g);
		assertEquals(testC.minDistanza(3),16);
		
		g= new UndirectedGraph("5;0 1 13;0 2 16;0 3 19;0 4 9;1 2 7;1 3 14;1 4 22;3 2 12;3 4 26;4 2 15;");
		testC = new Hikes(g);
		assertEquals(testC.minDistanza(3),12);
		assertEquals(testC.minDistanza(2),13);
		assertEquals(testC.minDistanza(2),13);
	}

	@Test  (expected = IllegalArgumentException.class)
	public void testEccezione() {
		
		UndirectedGraph g = new UndirectedGraph("10;0 2 9;0 5 6;0 4 17;0 9 8;1 5 12;1 2 15;1 4 18;1 8 13;2 6 7;2 8 5;3 6 16;3 7 19;4 8 14;5 6 10");
		Hikes testC = new Hikes(g);
		testC.minDistanza(-4);
	}

}
