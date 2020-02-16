package rebooking;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestRebooking {

	@Test
	public void test() {
		int cap=10;
		int[] vol ={5,8,3};
		int[] val={3,11,9};
		Rebooking zaino = new Rebooking(cap);
		assertEquals(zaino.maxSaving(vol,val),12);
		
		cap =10;
		zaino = new Rebooking(cap);
		int[] vol2 = {5,8};
		int[] val2= {3,11,9};
		assertEquals(zaino.maxSaving(vol2,val2),-1);
		
		cap=-4;
		zaino = new Rebooking(cap);
		assertEquals(zaino.maxSaving(vol,val),-1);
		
		cap=0;
		zaino = new Rebooking(cap);
		assertEquals(zaino.maxSaving(vol,val),0);
	
		cap=20;
		zaino = new Rebooking(cap);
		assertEquals(zaino.maxSaving(vol,val),23);

		
	}

}
