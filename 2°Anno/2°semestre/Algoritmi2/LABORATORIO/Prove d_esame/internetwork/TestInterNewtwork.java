package internetwork;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.UndirectedGraph;

public class TestInterNewtwork {

	
	//Test che l'oggetto venga creato e non sia nullo
	@Test
	public void testInit() {
		
		UndirectedGraph g = new UndirectedGraph("6;0 1;0 2;0 3;0 5;1 4;1 3;2 5;2 3;3 4;");
		InterNetwork in = new InterNetwork(g);
		assertNotNull(in);
	}

	//Test suggeriti dalla consegna
	@Test
	public void testNumberOfHopes()
	{
		UndirectedGraph g = new UndirectedGraph("6;0 1;0 2;0 3;0 5;1 4;1 3;2 5;2 3;3 4;");
		InterNetwork in = new InterNetwork(g);
		assertEquals(in.numberOfHops(3,1),2);
		assertEquals(in.numberOfHops(5,4),4);
		assertEquals(in.numberOfHops(4,2),3);
		assertEquals(in.numberOfHops(1,1),1);
		assertEquals(in.numberOfHops(1,6),-1);
		assertEquals(in.numberOfHops(7,-3),-1);

	}
}
