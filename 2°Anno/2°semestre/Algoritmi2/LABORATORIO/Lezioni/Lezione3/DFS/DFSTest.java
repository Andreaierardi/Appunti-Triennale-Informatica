package dfs;

import static org.junit.Assert.*;

import org.junit.Test;

import bfs.BFS;
import it.uniupo.graphLib.*;

public class DFSTest {

	@Test
	public void testCreate()
	{
		GraphInterface grafo = new DirectedGraph(3);
		DFS dfsTest = new DFS(grafo);
		assertNotNull(dfsTest);
	}
	@Test
	public void testScoperti()
	{
		GraphInterface grafo = new DirectedGraph ("3;0 1;1 2;2 0");
		DFS dfsTest = new DFS(grafo);
		dfsTest.getTree(0);
	}
	
	
	@Test
	public void testNumeroArchi()
	{
		GraphInterface grafo = new DirectedGraph ("3;0 1;1 2;2 0");
		DFS dfsTest = new DFS(grafo);
		assertEquals(dfsTest.getTree(2).getEdgeNum(),2);
		
		GraphInterface grafo2 = new DirectedGraph ("2;0 1;1 0");
		DFS dfsTest1 = new DFS(grafo2);
		assertEquals(dfsTest1.getTree(0).getEdgeNum(),1);
		
		GraphInterface grafo3 = new UndirectedGraph ("4;0 1;0 2;2 3;1 3");
		DFS dfsTest3 = new DFS(grafo3);
		assertEquals(dfsTest3.getTree(1).getEdgeNum(),3);
	}


	@Test
	public void testNumeroNodiRaggiunti()
	{
		GraphInterface grafo = new UndirectedGraph("4;0 2;0 1;2 3;1 3");
		DFS dfsTest = new DFS(grafo);
		GraphInterface albero = dfsTest.getTree(0);
		//per	contare	i	nodi	visita4:	usare	il	metodo	getNodesInOrderOfVisit(int)	della	classe	
		BFS	bfs	=	new	BFS(albero);	
		assertEquals(grafo.getOrder(),bfs.getNodesInOrderOfVisit(0).size());
		
	    GraphInterface grafo2 = new UndirectedGraph("7;0 1;0 2;0 3;0 5;1 5;2 3;2 4;2 6;3 6");
		DFS dfsTest2 = new DFS(grafo2);
		assertEquals(dfsTest2.getNodesInOrderOfVisit(0).size(),7);
	}
	
	@Test
	public void  testArchiDFS()
	{
		GraphInterface	grafo	=	new	UndirectedGraph	("4;0 2;0 1;2 3;1 3");	
		DFS	dfsTest	=	new	DFS(grafo);
		assertTrue((dfsTest.getTree(2).hasEdge(0,2)&& dfsTest.getTree(2).hasEdge(0,1) && dfsTest.getTree(2).hasEdge(1,3))||(dfsTest.getTree(2).hasEdge(0,1)&& dfsTest.getTree(2).hasEdge(1,3) && dfsTest.getTree(2).hasEdge(3,2)));
		assertFalse((dfsTest.getTree(2).hasEdge(0,1)&& dfsTest.getTree(2).hasEdge(0,2) && dfsTest.getTree(2).hasEdge(2,3))||(dfsTest.getTree(2).hasEdge(0,2)&& dfsTest.getTree(2).hasEdge(2,3) && dfsTest.getTree(2).hasEdge(1,3)));

	}

	@Test
	public void testInitAlbero()
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");
		DFS dfsTest = new DFS(grafo); //<<-	creato	una	volta	sola	
		
		assertTrue(dfsTest.getNodesInOrderOfVisit(2).get(2)==1);	
		assertTrue(dfsTest.getNodesInOrderOfVisit(1).get(2)==2);	
		assertTrue(dfsTest.getNodesInOrderOfVisit(0).get(2)==3);
		assertEquals(dfsTest.getTree(2).getEdgeNum(),3);
		assertEquals(dfsTest.getTree(1).getEdgeNum(),3);


	}
	
	@Test
	public void NodesInOrderPostVisit()
	{
		GraphInterface grafo = new DirectedGraph("7;0 6;1 3;1 5;2 4;2 6;4 2;4 3;5 2;5 4;5 6;6 1;6 3;6 4");
		DFS dfsTest = new DFS(grafo); //<<-	creato	una	volta	sola	
		assertEquals(dfsTest.getNodesInOrderPostVisit(0).size(),7);
		assertTrue(dfsTest.getNodesInOrderPostVisit(0).get(0).equals(3));
		assertTrue(dfsTest.getNodesInOrderPostVisit(0).get(1).equals(4));
		assertTrue(dfsTest.getNodesInOrderPostVisit(0).get(2).equals(2));
		assertTrue(dfsTest.getNodesInOrderPostVisit(0).get(3).equals(5));
		assertTrue(dfsTest.getNodesInOrderPostVisit(0).get(4).equals(1));
		assertTrue(dfsTest.getNodesInOrderPostVisit(0).get(5).equals(6));
		assertTrue(dfsTest.getNodesInOrderPostVisit(0).get(6).equals(0));

	}

	@Test
	public void ForestTest()
	{
		GraphInterface grafo =new UndirectedGraph ("4;");
		DFS dfsTest = new DFS(grafo);
		assertEquals(dfsTest.getForest().getOrder(),4);
		
		GraphInterface grafo2 =new UndirectedGraph ("9;0 1;1 2;2 3;1 3;3 4;7 6;6 8");
		DFS dfsTest2 = new DFS(grafo2);
		assertEquals(dfsTest2.getForest().getOrder(),9);
		assertEquals(dfsTest2.getForest().getEdgeNum(),6);


	}
	@Test
	public void testDFSOrder()
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");
		DFS dfsTest = new DFS(grafo);
		assertTrue(dfsTest.getNodesInOrderOfVisit(2).get(0).equals(2)&& dfsTest.getNodesInOrderOfVisit(2).get(2).equals(1));
		assertFalse(dfsTest.getNodesInOrderOfVisit(2).get(3).equals(1));
	}
	@Test
	public void testInitLunghezza() 
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");

		DFS dfsTest = new DFS(grafo); //<<-	creato	una	volta	sola	
		assertEquals(4, dfsTest.getNodesInOrderOfVisit(0).size()); //<<-due	chiamate	del	metodo	
		assertEquals(4, dfsTest.getNodesInOrderOfVisit(2).size());

	}
	
	@Test
	public void testInitContenuti()
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");
		DFS dfsTest = new DFS(grafo); //<<-	creato	una	volta	sola	

		assertTrue(dfsTest.getNodesInOrderOfVisit(2).get(3)!=1);
		assertTrue(dfsTest.getNodesInOrderOfVisit(1).get(1)!=2);
		assertTrue(dfsTest.getNodesInOrderOfVisit(0).get(2)!=1);	

	}
	@Test
	public void testArrayOfVisit()
	{
		GraphInterface grafo =new DirectedGraph ("6;3 0;0 5;5 1;1 2;2 4");
		DFS dfsTest = new DFS(grafo);
		assertTrue(dfsTest.getOrderOfVisit(3)[0]== 1);
		assertTrue(dfsTest.getOrderOfVisit(3)[1]== 3);
		assertTrue(dfsTest.getOrderOfVisit(3)[2]== 4);
		assertTrue(dfsTest.getOrderOfVisit(3)[3]== 0);
		assertTrue(dfsTest.getOrderOfVisit(3)[4]== 5);
		assertTrue(dfsTest.getOrderOfVisit(3)[5]== 2);
	}
	@Test
	public void testArrayPostVisit()
	{
		GraphInterface grafo =new DirectedGraph ("6;3 0;0 5;5 1;1 2;2 4");
		DFS dfsTest = new DFS(grafo);
		assertTrue(dfsTest.getOrderPostVisit(3)[0]== 4);
		assertTrue(dfsTest.getOrderPostVisit(3)[1]== 2);
		assertTrue(dfsTest.getOrderPostVisit(3)[2]== 1);
		assertTrue(dfsTest.getOrderPostVisit(3)[3]== 5);
		assertTrue(dfsTest.getOrderPostVisit(3)[4]== 0);
		assertTrue(dfsTest.getOrderPostVisit(3)[5]== 3);
	}//[4, 2, 1, 5, 0, 3]


}

