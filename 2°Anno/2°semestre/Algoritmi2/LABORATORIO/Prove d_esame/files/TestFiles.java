package files;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestFiles {

	@Test
	public void testCreate() {
		int [] dim = {5,8,3};
		int [] time = {3,11,9};
		Files f= new Files(dim,time);
		assertNotNull(f);
	}

	@Test
	public void testisSufficient() {
		int [] dim = {5,8,3};
		int [] time = {3,11,9};
		Files f= new Files(time,dim);
		assertTrue(f.isSufficient(10,13));
		assertFalse(f.isSufficient(0,20));
		assertTrue(f.isSufficient(20,0));

	}
	@Test (expected = java.lang.IllegalArgumentException.class)
	public void testEccezione() {
		int [] dim = {5,8,3};
		int [] time = {3,11,9};
		Files f= new Files(time,dim);
		assertTrue(f.isSufficient(-4,2));

	}
	@Test (expected = java.lang.IllegalArgumentException.class)
	public void testEccezione2() {
		int [] dim = {5,8,3};
		int [] time = {3,11,9};
		Files f= new Files(time,dim);
		assertTrue(f.isSufficient(4,-1));

	}
	
}
