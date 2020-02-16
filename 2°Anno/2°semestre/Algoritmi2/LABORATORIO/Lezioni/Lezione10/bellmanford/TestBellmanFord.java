package bellmanford;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.*;

public class TestBellmanFord {

	@Test
	public void testgetDist() {
		
		DirectedGraph g = new DirectedGraph("4;0 1 6;0 2 7;2 1 -2;3 2 -1;1 3 5");
		BellmanFord bf = new BellmanFord(g,0);
		assertEquals(bf.getDist(2),7,0.1);
		
		/*	DirectedGraph g = new DirectedGraph("8;1 2 -3;1 0 1;1 5 -1;2 5 -2;3 1 2;3 2 6;3 6 3;4 2 2;4 5 3;4 7 3;4 3 2");
		BellmanFord bf = new BellmanFord(g,4);
		bf.getDist(3);
		//assertEquals(bf.getDist(2),7,0.1);*/
	}

}
