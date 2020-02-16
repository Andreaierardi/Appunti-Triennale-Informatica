package esonero2018;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.UndirectedGraph;

public class TestSubcables {

	//Test per verificare che la classe creata non sia a NULL
	@Test
	public void testCreate() {

		UndirectedGraph g = new UndirectedGraph("3;0 2 3;2 1 5;0 1 7");
		int [][] cost = new int[g.getOrder()][g.getOrder()];
		cost[0][0]=0;
		cost[0][1]=1;
		cost[0][2]=2;
		cost[1][0]=1;
		cost[1][1]=0;
		cost[1][2]=4;
		cost[2][0]=2;
		cost[2][1]=4;
		cost[2][2]=0;
		Subcables s = new Subcables(g,cost);
		assertNotNull(s);
	
	}
	//Test come da consegna del metodo cost
	@Test
	public void testCost() {

		UndirectedGraph g = new UndirectedGraph("3;0 2 3;2 1 5;0 1 7");
		int [][] cost = new int[g.getOrder()][g.getOrder()];
		cost[0][0]=0;
		cost[0][1]=1;
		cost[0][2]=2;
		cost[1][0]=1;
		cost[1][1]=0;
		cost[1][2]=4;
		cost[2][0]=2;
		cost[2][1]=4;
		cost[2][2]=0;

		Subcables s = new Subcables(g,cost);
		assertEquals(s.cost(0, 12),3);
		assertEquals(s.cost(4, 10),5);
		assertEquals(s.cost(1, 6),6);
		assertEquals(s.cost(4, 6),-1);

	}
	//Test delle eccezioni
	@Test (expected = IllegalArgumentException.class)
	public void testEccezzione() {

		UndirectedGraph g = new UndirectedGraph("3;0 2 3;2 1 5;0 1 7");
		int [][] cost = new int[g.getOrder()][g.getOrder()];
		cost[0][0]=0;
		cost[0][1]=1;
		cost[0][2]=2;
		cost[1][0]=1;
		cost[1][1]=0;
		cost[1][2]=4;
		cost[2][0]=2;
		cost[2][1]=4;
		cost[2][2]=0;

		Subcables s = new Subcables(g,cost);
		s.cost(5, 3);


	}

}
