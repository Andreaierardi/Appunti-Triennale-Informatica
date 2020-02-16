package fracknapsack;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestFracKnapsack {

	@Test
	public void test() {
		
		double cap=6;
		double[] vol ={2,4,5,1};
		double[] val={1,2,100,5};
		FracKnapsack zaino = new FracKnapsack(cap,vol,val);
		//zaino.maxVal();
	/*	System.out.println(zaino.maxVal());
		System.out.println(zaino.dose(0));
		System.out.println(zaino.dose(1));
		System.out.println(zaino.dose(2));
		System.out.println(zaino.dose(3));*/
		
		cap=10;
		double[] vol2 ={6,5,5};
		double[] val2={9,5,5};
		zaino = new FracKnapsack(cap,vol2,val2);
		zaino.maxVal();

		System.out.println(zaino.maxVal());
		System.out.println(zaino.dose(0));
		System.out.println(zaino.dose(1));
		System.out.println(zaino.dose(2));
	

	}

}
