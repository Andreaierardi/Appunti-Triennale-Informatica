package kosaraju;

import static org.junit.Assert.*;

import org.junit.*;
import org.junit.rules.ExpectedException;
import it.uniupo.graphLib.*;

public class KosarajuTest {

	@Rule
	public ExpectedException eccezione= ExpectedException.none();
	@Test
	public void testCreate()
	{
		DirectedGraph grafo = new DirectedGraph(3);
		Kosaraju KTest = new Kosaraju(grafo);
		assertNotNull(KTest);
	}
	@Test
	public void testScoperti()
	{
		DirectedGraph grafo = new DirectedGraph ("3;0 1;1 2;2 0");
		Kosaraju KTest = new Kosaraju(grafo);
		KTest.topologicalOrder();
	}


	@Test
	public void TesttopologicalOrder()
	{
		DirectedGraph grafo = new DirectedGraph ("6;0 1;2 1;3 2;4 2;3 5");
		Kosaraju KTest = new Kosaraju(grafo);
		assertEquals(KTest.topologicalOrder().size(),6);
		assertEquals(KTest.topologicalOrder().toString(),"[4, 3, 5, 2, 0, 1]");

		
	}
	@Test
	public void TestorderOfSecondVisit()
	{
		DirectedGraph grafo = new DirectedGraph ("7;0 1;0 3;1 2;2 1;3 4;4 0;4 2;4 5;6 5");
		Kosaraju KTest = new Kosaraju(grafo);
		assertEquals(KTest.orderOfSecondVisit().size(),7);
		assertEquals(KTest.orderOfSecondVisit().toString(),"[6, 0, 3, 4, 5, 1, 2]");
		DirectedGraph grafo2 = new DirectedGraph ("5;0 2;1 2;1 4;2 0;3 1;4 3;4 0");
		Kosaraju KTest2 = new Kosaraju(grafo2);
		assertEquals(KTest2.orderOfSecondVisit().size(),5);
		assertEquals(KTest2.orderOfSecondVisit().toString(),"[1, 4, 3, 0, 2]");
		assertTrue(KTest2.orderOfSecondVisit().indexOf(1)< KTest2.orderOfSecondVisit().indexOf(0));
		assertTrue(KTest2.orderOfSecondVisit().indexOf(1)< KTest2.orderOfSecondVisit().indexOf(2));

		assertTrue(KTest2.orderOfSecondVisit().indexOf(4)< KTest2.orderOfSecondVisit().indexOf(0));
		assertTrue(KTest2.orderOfSecondVisit().indexOf(4)< KTest2.orderOfSecondVisit().indexOf(2));
	
		assertTrue(KTest2.orderOfSecondVisit().indexOf(3)< KTest2.orderOfSecondVisit().indexOf(0));
		assertTrue(KTest2.orderOfSecondVisit().indexOf(3)< KTest2.orderOfSecondVisit().indexOf(2));
	}
	@Test
	public void TestgetSCC()
	{
		DirectedGraph grafo = new DirectedGraph ("7;0 4;1 2;1 3;1 5;2 4;2 5;5 0;6 0");
		Kosaraju KTest = new Kosaraju(grafo);
		assertEquals(KTest.getSCC().length,7);
		assertEquals(KTest.getSCC()[0],0);
		assertEquals(KTest.getSCC()[1],1);
		assertEquals(KTest.getSCC()[2],1);
		assertEquals(KTest.getSCC()[3],1);
		assertEquals(KTest.getSCC()[4],0);
		assertEquals(KTest.getSCC()[5],1);
		assertEquals(KTest.getSCC()[6],2);
	
		DirectedGraph grafo2 = new DirectedGraph("4;0 1;1 2;2 3;3 0");
		Kosaraju KTest2 = new Kosaraju(grafo2);
		assertEquals(KTest2.getSCC().length,4);
		assertEquals(KTest2.getSCC()[0],0);
		assertEquals(KTest2.getSCC()[1],0);
		assertEquals(KTest2.getSCC()[2],0);
		assertEquals(KTest2.getSCC()[3],0);
		
		DirectedGraph grafo3 = new DirectedGraph("5;0 2;1 2;1 4;2 0;3 1; 4 3");
		Kosaraju KTest3 = new Kosaraju(grafo3);
		assertEquals(KTest3.getSCC().length,5);
		assertEquals(KTest3.getSCC()[0],0);
		assertEquals(KTest3.getSCC()[1],1);
		assertEquals(KTest3.getSCC()[2],0);
		assertEquals(KTest3.getSCC()[3],1);
		assertEquals(KTest3.getSCC()[4],1);
		
		DirectedGraph grafo4 = new DirectedGraph("8;0 1;0 2;1 2;1 3;3 4;2 5;7 6");
		Kosaraju KTest4 = new Kosaraju(grafo4);
		assertEquals(KTest4.getSCC().length,8);
		assertEquals(KTest4.getSCC()[0],0);
		assertEquals(KTest4.getSCC()[1],0);
		assertEquals(KTest4.getSCC()[2],0);
		assertEquals(KTest4.getSCC()[3],0);
		assertEquals(KTest4.getSCC()[4],0);
		assertEquals(KTest4.getSCC()[5],0);
		assertEquals(KTest4.getSCC()[6],1);
		assertEquals(KTest4.getSCC()[7],2);
		
	}

	@Test
	public void	TestDAGtopologicalOrder()
	{
		DirectedGraph grafo = new DirectedGraph("5;0 2;1 2;1 4;2 0;3 1; 4 3");
		Kosaraju KTest = new Kosaraju(grafo);
		eccezione.expect(IllegalArgumentException.class);
		KTest.DAGtopologicalOrder();
	}
	@Test
	public void TestsameSCC()
	{
		DirectedGraph grafo = new DirectedGraph("5;0 2;1 2;1 4;2 0;3 1; 4 3");
		Kosaraju KTest = new Kosaraju(grafo);
		assertEquals(KTest.sameSCC(),true);
		
		DirectedGraph grafo4 = new DirectedGraph("8;0 1;0 2;1 2;1 3;3 4;2 5;7 6");
		Kosaraju KTest4 = new Kosaraju(grafo4);
		assertEquals(KTest4.sameSCC(),true);
	}


	
}
