package game;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.DirectedGraph;

public class TestGame {

	//Test del metodo in consegna
	@Test
	public void testWins() 
	{
		DirectedGraph g = new DirectedGraph("7;0 3;1 4;2 5;3 2;3 6;4 3;5 0;5 1");
		int [] conf = new int[g.getOrder()];
		conf[0] =0 ;
		conf[1] =0 ;
		conf[2] =1 ;
		conf[3] =0 ;
		conf[4] =2 ;
		conf[5] =0 ;
		conf[6] =1 ;

		Game gm = new Game(g, conf);
		assertEquals(gm.wins(5,2,2),1);
		assertEquals(gm.wins(5,1,2),0);
		assertEquals(gm.wins(5,1,7),1);
		assertEquals(gm.wins(3,0,1),-1);
		assertEquals(gm.wins(8,1,-1),-1);
		assertEquals(gm.wins(4,2,0),1);

	}

}
