package lavorisvincoli;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestLavoriSvincoli {

	@Test
	public void testManutenzione() {
		
		int[] costo = {2,13,7,5};
		LavoriSvincoli ls = new LavoriSvincoli(costo);
		assertFalse(ls.manutenzione(0));
		assertTrue(ls.manutenzione(1));
		assertFalse(ls.manutenzione(2));
		assertTrue(ls.manutenzione(3));
		
		costo[0]=8;costo[1]=4;costo[2]=8; costo[3]=12;
		ls= new LavoriSvincoli(costo);
		assertTrue(ls.manutenzione(0));
		assertFalse(ls.manutenzione(1));
		assertFalse(ls.manutenzione(2));
		assertTrue(ls.manutenzione(3));
		
	}
	
	@Test (expected = IllegalArgumentException.class)
	public void testEccezione() 
	{
		int[] costo = {2,13,7,5};
		LavoriSvincoli ls = new LavoriSvincoli(costo);
		assertFalse(ls.manutenzione(-3));
	}
	
	@Test (expected = IllegalArgumentException.class)
	public void testEccezione2() 
	{
		int[] costo = {2,13,7,5};
		LavoriSvincoli ls = new LavoriSvincoli(costo);
		assertFalse(ls.manutenzione(6));
	}

}
