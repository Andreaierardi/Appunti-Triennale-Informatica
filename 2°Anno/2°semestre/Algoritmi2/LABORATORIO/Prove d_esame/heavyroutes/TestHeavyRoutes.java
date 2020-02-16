package heavyroutes;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.*;

public class TestHeavyRoutes {

	@Test
	public void testDistance() {
		DirectedGraph g = new DirectedGraph("5;0 1 3;1 3 5;2 0 5;3 0 7;3 2 12;4 1 5;4 3 6");
		int[][] maxWeight= new int[g.getOrder()][g.getOrder()];
		maxWeight[0][1] = 6;
		maxWeight[1][3] = 7;
		maxWeight[2][0] = 6;
		maxWeight[3][0] = 3;
		maxWeight[3][2] = 8;
		maxWeight[4][1] = 4;
		maxWeight[4][3] = 7;

		HeavyRoutes hr = new HeavyRoutes(g, maxWeight);
	    assertEquals(hr.distance(4, 1, 3),5);
		assertEquals(hr.distance(3, 0, 2),7);
		assertEquals(hr.distance(3, 0, 5),17);
		assertEquals(hr.distance(2, 0, 8),-1);
		assertEquals(hr.distance(0, 4, 1),-1);
		assertEquals(hr.distance(2, 3, 0),-2);
		assertEquals(hr.distance(1,-1, 4),-2);





	}

}
