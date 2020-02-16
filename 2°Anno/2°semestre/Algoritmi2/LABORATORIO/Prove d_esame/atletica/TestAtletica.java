package atletica;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestAtletica {

	//Test del metodo richiesto dalla consegna
	@Test
	public void testScelta() {
		
		int[] rend1 = {8,4,2,6,3};
		int[] rend2 = {3,10,7,7,4};
		Atletica at = new Atletica(5);
		assertEquals(at.scelta(rend1,rend2),2);
		
		rend2[3]=4;
		assertEquals(at.scelta(rend1,rend2),0);		
	}
	
	//Test eccezioni
	@Test (expected = IllegalArgumentException.class)
	public void testEccezione() 
	{
		int[] rend1 = {8,4,2,6,3,1};
		int[] rend2 = {3,10,7,7,4};
		Atletica at = new Atletica(5);
		at.scelta(rend1,rend2);
	}

}
