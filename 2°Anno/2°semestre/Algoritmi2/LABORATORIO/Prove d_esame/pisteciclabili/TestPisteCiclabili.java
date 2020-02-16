package pisteciclabili;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.UndirectedGraph;

public class TestPisteCiclabili {

	@Test
	public void testPossibileEntro() {
		UndirectedGraph g = new UndirectedGraph("5;0 2 2;0 1 3;0 3 7;1 4 5;1 3 4;2 3 12;3 4 6");
		int [][]tempo = new int[g.getOrder()][g.getOrder()];
		for (int i =0 ;i<tempo.length;i++)
			for (int j =0 ;j<tempo[i].length;j++)
				tempo[i][j]=0;

		tempo[0][1]=6;
		tempo[0][2]=5;
		tempo[0][3]=9;
		tempo[1][4]=4;
		tempo[1][3]=7;
		tempo[4][3]=3;
		tempo[3][2]=8;

		
		PisteCiclabili pc = new PisteCiclabili(g,tempo);
		assertTrue(pc.possibileEntro(25));
		assertFalse(pc.possibileEntro(21));
		assertTrue(pc.possibileEntro(22));

	}

}
