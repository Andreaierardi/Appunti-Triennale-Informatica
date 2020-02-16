package trasportiportuali;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestTrasportiPortuali {

	@Test
	public void testAccettareCarico() 
	{
		int [] guadagno = {2,4,12,18,7,3,8};
		TrasportiPortuali tp= new TrasportiPortuali(guadagno);
		
		assertTrue(tp.accettareCarico(1));
		assertTrue(tp.accettareCarico(3));
		assertFalse(tp.accettareCarico(5));
		assertFalse(tp.accettareCarico(-3));
		assertFalse(tp.accettareCarico(8));
		
		int [] guadagno2 = {2,-4,12,18,7,3,8};
		tp= new TrasportiPortuali(guadagno2);	
		assertFalse(tp.accettareCarico(3));

	}

}
