package navigatore;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.DirectedGraph;

public class TestNavigatore {

	@Test
	public void test() 
	{
		DirectedGraph g = new DirectedGraph("5;0 1 6;0 2 2;1 3 2;1 4 3;2 3 2;2 4 3;3 4 2;3 1 1;");
		boolean[][] autostrada = new boolean[g.getOrder()][g.getOrder()];
		for(int i =0 ;i<autostrada.length;i++)
			for(int j =0 ;j<autostrada[i].length;j++)
				autostrada[i][j]=false;
		
		autostrada[1][4]=true;
		autostrada[3][4]=true;
		autostrada[2][4]=true;
		autostrada[2][3]=true;

		Navigatore n = new Navigatore(g,0,autostrada);
		assertEquals(n.distance(1,false),5);
		assertEquals(n.distance(1,true),6);
		assertEquals(n.distance(-3,false),-1);
		assertEquals(n.distance(8,true),-1);
		assertEquals(n.distance(4,true),-1);
		assertEquals(n.distance(4,false),5);
		
		n = new Navigatore(g,2,autostrada);
		assertEquals(n.distance(4,false),3);
		assertEquals(n.distance(3,true),-1);

	}

}
