package esamehikes;

import static org.junit.Assert.*;

import org.junit.Test;
import it.uniupo.graphLib.*;

public class TestHikes {
	
	//Verifica che la classe venga creata correttamente
	@Test
	public void testCreate()
	{
		UndirectedGraph g = new UndirectedGraph(3);
		Hikes testC = new Hikes(g);
		assertNotNull(testC);
	}
	//Test consigliati nella consegna
	@Test
	public void testZones() {
		
		UndirectedGraph g = new UndirectedGraph("5;0 1 13;0 2 16;0 3 19;0 4 9;1 2 7;1 3 14;1 4 22;3 2 12;3 4 26;4 2 15;");
		Hikes testC = new Hikes(g);
		assertEquals(testC.zones(10),3);
		assertEquals(testC.zones(12),2);
		assertEquals(testC.zones(20),1);

		
	}
	//test dell'eccezzione. Quando maxDistanza è minore di 0
	@Test  (expected = IllegalArgumentException.class)
	public void testEccezione() {
		
		UndirectedGraph g = new UndirectedGraph("5;0 1 13;0 2 16;0 3 19;0 4 9;1 2 7;1 3 14;1 4 22;3 2 12;3 4 26;4 2 15;");
		Hikes testC = new Hikes(g);
		testC.zones(-4);
	}

}
