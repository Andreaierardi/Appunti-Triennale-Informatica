package db_esame;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestDB {

	//Test per vedere se l'oggetto viene creato correttamente
	@Test
	public void testCreate() {
		
		int[] dim ={70,12,3};
		double[] time={10,2,0.3};
		DB zaino = new DB(dim,time);
		assertNotNull(zaino);
	}
	//Test consigliati dall'esercizio
	@Test
	public void testTimetoRebuild() {
		
		int[] dim ={70,12,3};
		double[] time={10,2,0.3};
		DB zaino = new DB(dim,time);
		assertEquals(zaino.timeToRebuild(3),11.8,0.001);
		
		dim[0]=3; dim[1]=2; dim[2]=4;
		time[0]=2; time[1]=5;time[2]=1;
		zaino = new DB(dim,time);
		assertEquals(zaino.timeToRebuild(10),0,0.001);
		
		dim[0]=4; dim[1]=3; dim[2]=4;
		time[0]=5; time[1]=3;time[2]=1;
		zaino = new DB(dim,time);
		//NB. Sull'esercizio indica 8.75 come soluzione
		//che però sarebbe la soluzione ottimale e non il complementare.
		//Dovrebbe essere errato l'esercizio ma in caso chiedo alla prof per essere sicuro
		assertEquals(zaino.timeToRebuild(10),0.25,0.001);
	}
	//Test dell'eccezione
	@Test (expected = IllegalArgumentException.class)
	public void testEccezione() {
		
		int[] dim ={5,8,3};
		double[] time={3,11,9};
		DB zaino = new DB(dim,time);
		zaino.timeToRebuild(-1);
		
	}
}

