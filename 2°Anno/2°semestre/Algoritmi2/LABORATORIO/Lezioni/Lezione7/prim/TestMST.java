package prim;

import static org.junit.Assert.*;

import org.junit.Test;
import it.uniupo.graphLib.*;
import kruskal.Kruskal;
import it.uniupo.algoTools.MST;


public class TestMST {

	MST mst= new Prim(new UndirectedGraph("1"));
	
	MST mstK = new Kruskal(new UndirectedGraph("1"));
	@Test
	public void testCreate() {
		
		//PRIM
		UndirectedGraph g = new UndirectedGraph("2;1 0 2");
		MST testMST	 = mstK.create(g);
		assertNotNull(testMST);
		
		//KRUSKAL
		testMST= mstK.create(g);
		assertNotNull(testMST);
	}
	
	@Test 
	public void testTree()
	{
		
		//PRIM
		UndirectedGraph g = new UndirectedGraph("2;1 0 2");
		MST testMST	 = mst.create(g);
		UndirectedGraph tree = testMST.getMST();
		assertTrue(tree.hasEdge(1,0));
		
		g = new UndirectedGraph("5;0 1 9;0 2 75;1 2 95;1 3 19;1 4 42;2 3 51;3 4 31;");
		testMST	 = mst.create(g);
		tree = testMST.getMST();
		assertTrue(tree.hasEdge(0,1));
		assertTrue(tree.hasEdge(3,1));
		assertTrue(tree.hasEdge(3,4));
		assertTrue(tree.hasEdge(2,3));
		
		//KRUSKAL
		g = new UndirectedGraph("2;1 0 2");
		testMST	 = mstK.create(g);
		tree = testMST.getMST();
		assertTrue(tree.hasEdge(1,0));
		
		g = new UndirectedGraph("5;0 1 9;0 2 75;1 2 95;1 3 19;1 4 42;2 3 51;3 4 31;");
		testMST	 = mstK.create(g);
		tree = testMST.getMST();
		assertTrue(tree.hasEdge(0,1));
		assertTrue(tree.hasEdge(3,1));
		assertTrue(tree.hasEdge(3,4));
		assertTrue(tree.hasEdge(2,3));
		
	}
	
	@Test
	public void testCost()
	{
		
		//PRIM
		UndirectedGraph g = new UndirectedGraph("2;1 0 2");
		MST testMST	 = mst.create(g);
		assertEquals(testMST.getCost(),2);
		
		g = new UndirectedGraph("5;0 1 9;0 2 75;1 2 95;1 3 19;1 4 42;2 3 51;3 4 31;");
		testMST	 = mst.create(g);
		assertEquals(testMST.getCost(),110);
		
		//KRUSKAL
		g = new UndirectedGraph("2;1 0 2");
		testMST	 = mstK.create(g);
		assertEquals(testMST.getCost(),2);
		
		g = new UndirectedGraph("5;0 1 9;0 2 75;1 2 95;1 3 19;1 4 42;2 3 51;3 4 31;");
		testMST	 = mstK.create(g);
		assertEquals(testMST.getCost(),110);
	}
	
}
