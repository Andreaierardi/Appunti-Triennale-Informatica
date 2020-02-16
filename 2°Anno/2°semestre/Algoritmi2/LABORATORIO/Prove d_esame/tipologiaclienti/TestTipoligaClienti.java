package tipologiaclienti;

import static org.junit.Assert.*;

import org.junit.Test;

import it.uniupo.graphLib.UndirectedGraph;

public class TestTipoligaClienti {

	@Test
	public void testnumeroTipologie() 
	{
		UndirectedGraph g = new UndirectedGraph("4;0 1 -2;0 2 3;0 3 8;1 2 4;1 3 7;2 3 9");
		TipoligaClienti tc = new TipoligaClienti(g);
		assertEquals(tc.numeroTipologie(-5),4);
		assertEquals(tc.numeroTipologie(1),3);
		assertEquals(tc.numeroTipologie(10),1);
		assertEquals(tc.numeroTipologie(4),2);
		assertEquals(tc.numeroTipologie(7),2);
		assertEquals(tc.numeroTipologie(8),1);

	}

}
