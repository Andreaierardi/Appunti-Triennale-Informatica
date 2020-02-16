package db;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestDB {

	@Test
	public void test() {
		
		double[] vol ={3,2,4};
		double[] val={2,5,1};
		DB zaino = new DB(vol,val);
		assertEquals(zaino.timeSaved(10),8,0.001);
		int [] d = zaino.memorize(10);
		assertTrue(d[0]==3 && d[1]==2 && d[2]==4);
		
		vol[0]= 70; vol[1]=12; vol[2]=3;
		val[0]= 10; val[1]=2; val[2]=0.3;
		zaino = new DB(vol,val);
		assertEquals(zaino.timeSaved(3),0.5,0.001);
		d = zaino.memorize(3);
		assertTrue(d[0]==0 && d[1]==3 && d[2]==0);


		vol[0]= 4; vol[1]=3; vol[2]=4;
		val[0]= 5; val[1]=3; val[2]=1;
		zaino = new DB(vol,val);
		assertEquals(zaino.timeSaved(10),8.75,0.001);
		d = zaino.memorize(10);
		assertTrue(d[0]==4 && d[1]==3 && d[2]==3);
		
		
		
	}
	@Test ( expected= IllegalArgumentException.class)
	public void testEccezione() {
		double[] vol ={3,2,4};
		double[] val={2,5,1};
		DB zaino = new DB(vol,val);
		int[] d = zaino.memorize(-1);
		assertTrue(d[0]==4 && d[1]==3 && d[2]==3);

	}
}

