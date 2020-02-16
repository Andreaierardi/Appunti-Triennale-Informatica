package msi;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestMSI {

	@Test
	public void test() {
		
		int w[]={4,3,2,9,4};
		MSI msi = new MSI(w);
		assertEquals(msi.getMaxVal(),13);
		assertEquals(msi.getOptSol().size(),2);
		assertEquals(msi.getOptSol().get(0).intValue(),4);
		assertEquals(msi.getOptSol().get(1).intValue(),1);

	}

}
