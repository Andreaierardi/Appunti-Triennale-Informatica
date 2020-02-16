package dijkstra;

import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Test;
import it.uniupo.graphLib.*;

public class TestDijkstra {

	@Test 
	public void testgetDistanze() {
		GraphInterface grafo = new DirectedGraph("6;0 1 2;0 2 6;0 3 7;1 3 3;1 4 6;2 4 1;3 4 5;");
		Dijkstra Dtest = new Dijkstra(grafo);
		int [] a = Dtest.getDistanze(0);
		assertTrue(a[0]==0 && a[1]==2 && a[2]==6 && a[3]==5 && a[4]==7 && a[5]==-1);
		
	}
	
	@Test (expected = IllegalArgumentException.class) 

	public void testDijkstraNegSorg() 
	{
			GraphInterface grafo = new DirectedGraph("6;0 1 2;0 2 6;0 3 7;1 3 3;1 4 6;2 4 1;3 4 5;");
			Dijkstra Dtest = new Dijkstra(grafo);
			Dtest.getDistanze(-1);
	}
	
	@Test (expected = IllegalArgumentException.class) 
	public void testDijkstraSorgMagDiN() 
	{
			GraphInterface grafo = new DirectedGraph("6;0 1 2;0 2 6;0 3 7;1 3 3;1 4 6;2 4 1;3 4 5;");
			Dijkstra Dtest = new Dijkstra(grafo);
			Dtest.getDistanze(10);
	}
	@Test
	public void testgetAlberoCamminiMinimi()
	{
		GraphInterface grafo = new DirectedGraph("6;0 1 2;0 2 6;0 3 7;1 3 3;1 4 6;2 4 1;3 4 5;");
		Dijkstra Dtest = new Dijkstra(grafo);
		GraphInterface albero = Dtest.getAlberoCamminiMinimi(0);
		assertTrue(albero.hasEdge(0,1)&& albero.hasEdge(0,2) && albero.hasEdge(1,3) && albero.hasEdge(2,4));
		assertTrue(!albero.hasEdge(1,4));
	}
	
	@Test
	public void testgetCamminoMinimo()
	{
		GraphInterface grafo = new DirectedGraph("6;0 1 2;0 2 6;0 3 7;1 3 3;1 4 6;2 4 1;3 4 5;");
		Dijkstra Dtest = new Dijkstra(grafo);
		ArrayList<Edge> camminoMin = Dtest.getCamminoMinimo(0,3);
		assertEquals(camminoMin.size(),2);
		assertTrue(camminoMin.get(0).equals(new Edge(1,3,3)));
		assertTrue(camminoMin.get(1).equals(new Edge(0,1,2)));
		grafo = new DirectedGraph("6;0 1 2;0 2 6;0 3 7;1 3 3;1 4 2;2 4 1;3 1 2;3 4 5;");
		Dtest = new Dijkstra(grafo);
		camminoMin = Dtest.getCamminoMinimo(3,4);
		assertTrue(camminoMin.get(0).equals(new Edge(1,4,2)));
		assertTrue(camminoMin.get(1).equals(new Edge(3,1,2)));
	}
	@Test (expected = IllegalArgumentException.class) 
	public void testgetCamminoMinimoEccezioni()
	{
		GraphInterface grafo = new DirectedGraph("6;0 1 2;0 2 6;0 3 7;1 3 3;1 4 6;2 4 1;3 4 5;");
		Dijkstra Dtest = new Dijkstra(grafo);
		Dtest.getCamminoMinimo(0,7);	
		Dtest.getCamminoMinimo(-1,7);	
		Dtest.getCamminoMinimo(0,-1);		


	}
	@Test (expected = IllegalArgumentException.class) 
	public void testGrafoNeg()
	{
		GraphInterface grafo = new DirectedGraph("6;0 1 2;0 2 6;0 3 7;1 3 3;1 4 6;2 4 1;3 4 -5;");
		Dijkstra Dtest = new Dijkstra(grafo);
		
	}

}