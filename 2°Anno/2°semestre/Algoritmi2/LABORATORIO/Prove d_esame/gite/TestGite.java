package gite;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.*;

public class TestGite {

	//Test di creazione della classe
	@Test
	public void testCreazione() {
		
		UndirectedGraph g = new UndirectedGraph("5;0 2 6;0 4 10;1 2 1;1 4 13;2 4 9;3 4 8");
		int diff[][] = new int[g.getOrder()][g.getOrder()];
		for (int i =0 ; i<g.getOrder();i++)
			for(int j =0; j< g.getOrder();j++)
				diff[i][j]=0;
		
		diff[0][2]=2; diff[0][4]=8;
		
		diff[1][2]=1; diff[1][4]=6;

		diff[2][0]=2; diff[2][1]=1;
		diff[2][4]=3; diff[3][4]=2;

		diff[4][0]=8; diff[4][1]=6;
		diff[4][2]=3; diff[4][3]=2;

		Gite gt = new Gite(g,diff);
		assertNotNull(gt);
	}
	
	//Test del metodo richiesto
	@Test
	public void testDislivelloTotale() {
		
		UndirectedGraph g = new UndirectedGraph("5;0 2 6;0 4 10;1 2 1;1 4 13;2 4 9;3 4 8");
		int diff[][] = new int[g.getOrder()][g.getOrder()];
		for (int i =0 ; i<g.getOrder();i++)
			for(int j =0; j< g.getOrder();j++)
				diff[i][j]=0;
		
		diff[0][2]=2; diff[0][4]=8;
		
		diff[1][2]=1; diff[1][4]=6;

		diff[2][0]=2; diff[2][1]=1;
		diff[2][4]=3; diff[3][4]=2;

		diff[4][0]=8; diff[4][1]=6;
		diff[4][2]=3; diff[4][3]=2;

		Gite gt = new Gite(g,diff);
		assertEquals(gt.dislivelloTotale(3,0,10),18);
		assertEquals(gt.dislivelloTotale(3,1,10),21);
		assertEquals(gt.dislivelloTotale(3,1,5),18);
		assertEquals(gt.dislivelloTotale(3,0,6),23);
		assertEquals(gt.dislivelloTotale(3,0,1),-1);

	}
	//Test delle eccezioni
	@Test (expected = IllegalArgumentException.class)
	public void testEccezione() {
		
		UndirectedGraph g = new UndirectedGraph("5;0 2 6;0 4 10;1 2 1;1 4 13;2 4 9;3 4 8");
		int diff[][] = new int[g.getOrder()][g.getOrder()];
		for (int i =0 ; i<g.getOrder();i++)
			for(int j =0; j< g.getOrder();j++)
				diff[i][j]=0;
		
		diff[0][2]=2; diff[0][4]=8;
		
		diff[1][2]=1; diff[1][4]=6;

		diff[2][0]=2; diff[2][1]=1;
		diff[2][4]=3; diff[3][4]=2;

		diff[4][0]=8; diff[4][1]=6;
		diff[4][2]=3; diff[4][3]=2;

		Gite gt = new Gite(g,diff);
		gt.dislivelloTotale(3,6,5);
	}
}
