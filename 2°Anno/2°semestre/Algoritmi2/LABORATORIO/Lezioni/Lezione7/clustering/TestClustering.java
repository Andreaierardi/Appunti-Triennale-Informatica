package clustering;

import static org.junit.Assert.*;

import org.junit.Test;
import it.uniupo.graphLib.UndirectedGraph;

public class TestClustering {

	@Test
	public void testCreate() {
		
		UndirectedGraph g = new UndirectedGraph("10;0 2 9;0 5 6;0 4 17;0 9 8;1 5 12;1 2 15;1 4 18;1 8 13;2 6 7;2 8 5;3 6 16;3 7 19;4 8 14;5 6 10");
		Clustering testC = new Clustering(g,3);
		assertEquals(testC.spaziamento(),16);
		
	}
	@Test
	public void testSameCluster()
	{
		UndirectedGraph g = new UndirectedGraph("10;0 2 9;0 5 6;0 4 17;0 9 8;1 5 12;1 2 15;1 4 18;1 8 13;2 6 7;2 8 5;3 6 16;3 7 19;4 8 14;5 6 10");
		Clustering testC = new Clustering(g,3);
		
		assertTrue(testC.sameCluster(3, 2));
		assertTrue(testC.sameCluster(3, 1));
		assertFalse(testC.sameCluster(9, 2));
		

	}

}
