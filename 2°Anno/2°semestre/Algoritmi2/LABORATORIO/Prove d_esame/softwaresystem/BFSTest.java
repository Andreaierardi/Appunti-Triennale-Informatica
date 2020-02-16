package softwaresystem;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.*;

public class BFSTest {
	
	@Test
	public void testCreate()
	{
		GraphInterface grafo = new DirectedGraph(3);
		BFS bfsTest = new BFS(grafo);
		assertNotNull(bfsTest);
	}
	@Test
	public void testScoperti()
	{
		GraphInterface grafo =new DirectedGraph ("3;0 1;1 2;2 0");
		BFS bfsTest = new BFS(grafo);
		bfsTest.getNodesInOrderOfVisit(0);	
	}

	



	@Test
	public void testNumeroNodiVisitati()
	{
		GraphInterface grafo = new UndirectedGraph("4;0 2;0 1;2 3;1 3");
		
		 BFS bfsTest = new BFS(grafo);
		 assertEquals(4,bfsTest.getNodesInOrderOfVisit(2).size());
	}
	
	@Test
	public void  testBFSOrder()
	{
		GraphInterface	grafo	=	new	UndirectedGraph	("4;0 2;0 1;2 3;1 3");	
		BFS	bfsTest	=	new	BFS(grafo);
		assertTrue(	(bfsTest.getNodesInOrderOfVisit(2).get(2)==0||
				bfsTest.getNodesInOrderOfVisit(2).get(2)==3));
		
		assertFalse(bfsTest.getNodesInOrderOfVisit(2).get(2)==1);
	}
	
	@Test
	public void testInitContenuti()
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");
		BFS bfsTest = new BFS(grafo); //<<-	creato	una	volta	sola	

		assertTrue(bfsTest.getNodesInOrderOfVisit(2).get(2)!=1);
		assertTrue(bfsTest.getNodesInOrderOfVisit(1).get(2)!=0);
		assertTrue(bfsTest.getNodesInOrderOfVisit(0).get(2)!=3);	

	}
	
	@Test
	public void testInitLunghezza() 
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");

		BFS bfsTest = new BFS(grafo); //<<-	creato	una	volta	sola	
		assertEquals(4, bfsTest.getNodesInOrderOfVisit(0).size()); //<<-due	chiamate	del	metodo	
		assertEquals(4, bfsTest.getNodesInOrderOfVisit(2).size());

	}
	
	@Test
	public void testInitDistanza() 
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");
		GraphInterface grafo2 =new UndirectedGraph ("1");

		BFS bfsTest = new BFS(grafo); //<<-	creato	una	volta	sola	
		assertTrue(bfsTest.getDistance(2)[2]==0 && bfsTest.getDistance(2)[0]==1 && bfsTest.getDistance(2)[1]==2 && bfsTest.getDistance(2)[3]==1 ); //<<-due	chiamate	del	metodo	
		assertEquals(4, bfsTest.getNodesInOrderOfVisit(2).size());

		assertTrue(bfsTest.getDistance(3)[3]==0 && bfsTest.getDistance(3)[0]==2 && bfsTest.getDistance(3)[1]==1 && bfsTest.getDistance(3)[2]==1 ); //<<-due	chiamate	del	metodo	
		assertEquals(4, bfsTest.getNodesInOrderOfVisit(2).size());
		
		bfsTest = new BFS(grafo2);
		assertTrue(bfsTest.getDistance(0)[0]==0); //<<-due	chiamate	del	metodo	

		assertEquals(1, bfsTest.getNodesInOrderOfVisit(0).size());

	}
	
	@Test
	public void testDimensioneAlbero()
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");
		GraphInterface grafo2 =new UndirectedGraph ("2;0 1");		
		BFS bfsTest = new BFS(grafo); //<<-	creato	una	volta	sola	
		assertEquals(bfsTest.bfsTree(0).getOrder(),4);
		assertEquals(bfsTest.bfsTree(3).getEdgeNum(),3);
		assertEquals(bfsTest.bfsTree(1).getOrder(),4);
		assertEquals(bfsTest.bfsTree(3).getEdgeNum(),3);
		assertEquals(bfsTest.bfsTree(3).getOrder(),4);
		assertEquals(bfsTest.bfsTree(3).getEdgeNum(),3);

		
		bfsTest = new BFS(grafo2); //<<-	creato	una	volta	sola	
		assertEquals(bfsTest.bfsTree(0).getOrder(),2);
		assertEquals(bfsTest.bfsTree(0).getEdgeNum(),1);
		assertEquals(bfsTest.bfsTree(1).getOrder(),2);
		assertEquals(bfsTest.bfsTree(1).getEdgeNum(),1);

	}
	
	@Test
	public void testArchiAlbero()
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");
		BFS bfsTest = new BFS(grafo); //<<-	creato	una	volta	sola	
		assertTrue(bfsTest.bfsTree(2).hasEdge(2,0)&& bfsTest.bfsTree(2).hasEdge(2,3));
		assertTrue((bfsTest.bfsTree(2).hasEdge(0,1)&& !bfsTest.bfsTree(2).hasEdge(1,3))||!(bfsTest.bfsTree(2).hasEdge(0,1)&& bfsTest.bfsTree(2).hasEdge(1,3)));

				
	}

	@Test
	public void testInitAlbero() 
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");
		BFS bfsTest = new BFS(grafo);
		assertTrue(bfsTest.bfsTree(2).hasEdge(2,0)&& bfsTest.bfsTree(2).hasEdge(2,3));
		assertEquals(bfsTest.bfsTree(2).getEdgeNum(),3);

		assertTrue((bfsTest.bfsTree(1).hasEdge(2,0)&& !bfsTest.bfsTree(1).hasEdge(2,3))||!(bfsTest.bfsTree(1).hasEdge(2,0)&& bfsTest.bfsTree(1).hasEdge(2,3)));
		assertEquals(bfsTest.bfsTree(1).getEdgeNum(),3);

	}
	
	@Test
	public void testOrderOfVisit()
	{
		GraphInterface grafo =new UndirectedGraph ("4;0 2;0 1;2 3;1 3");
		BFS bfsTest = new BFS(grafo);
		assertTrue(bfsTest.getOrderOfVisit(2).length==4);
		assertTrue(bfsTest.getOrderOfVisit(2)[0]==1 && bfsTest.getOrderOfVisit(2)[1]==3 && bfsTest.getOrderOfVisit(2)[2]==0 && bfsTest.getOrderOfVisit(2)[3]==2);
	}
	
	@Test
	public void testgetNodesInOrderOfVisitGeneralGraph()
	{
		GraphInterface grafo =new UndirectedGraph ("9;0 1;1 3;1 2;2 3;3 4;7 6;6 8");
		BFS bfsTest = new BFS(grafo);
		assertEquals(bfsTest.getNodesInOrderOfVisitGeneralGraph().size(),9);
	}
	@Test
	public void testgetNumberOfConnectedComponents()
	{
		GraphInterface grafo =new UndirectedGraph ("9;0 1;1 3;1 2;2 3;3 4;7 6;6 8");
		BFS bfsTest = new BFS(grafo);
		assertEquals(bfsTest.getNumberOfConnectedComponents(),3);
	}
	@Test
	public void testTopologicalOrder()
	{
		GraphInterface grafo =new DirectedGraph ("8;0 1;0 3;0 4;2 0;5 0;5 6;7 6;6 4;7 3");
		BFS bfsTest = new BFS(grafo);
		assertEquals(bfsTest.getTopologicalOrder().size(),8);
	}
}

