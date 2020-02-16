package partita;

import static org.junit.Assert.*;

import org.junit.Test;
import it.uniupo.graphLib.DirectedGraph;

public class TestPartita {

	//Test del metodo richiesto dalla consegna
	@Test
	public void testWinner() {
		
		DirectedGraph g = new DirectedGraph("8;0 1;0 2;0 3;1 4;2 5;2 7;3 6;3 4;3 2;5 1;5 7");
		int [] conf = new int[g.getOrder()];
		conf[0] =-1 ;
		conf[1] =-1  ;
		conf[2] =0 ;
		conf[3] =-1  ;
		conf[4] =1  ;
		conf[5] =-1  ;
		conf[6] =0 ;
		conf[7] =-1;
		Partita p = new Partita(g, conf);
	    assertEquals(p.winner(5),1);
		assertEquals(p.winner(0),0);
		assertEquals(p.winner(3),-1);
		assertEquals(p.winner(2),0);
		assertEquals(p.winner(1),1);
		assertEquals(p.winner(7),-1);


	}

}
