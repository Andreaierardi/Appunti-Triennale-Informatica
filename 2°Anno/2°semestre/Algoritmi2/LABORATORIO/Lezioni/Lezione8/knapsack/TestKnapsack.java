package knapsack;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestKnapsack {

	@Test
	public void test() {
		int cap=7;
		int[] vol ={4,4,6,6,1};
		int[] val={8,3,10,2,8};
		Knapsack zaino = new Knapsack(val,vol,cap);
		assertEquals(18,zaino.getMaxVal());
		
		
		cap=4;
		int[] vol1 ={4,1,3,3,3};
		int[] val1={1,3,2,10,11};
		zaino = new Knapsack(val1,vol1,cap);
		assertEquals(14,zaino.getMaxVal());
		
		cap=6;
		int[] vol2 ={4,4,3,2,6};
		int[] val2={12,4,5,10,5};
		zaino = new Knapsack(val2,vol2,cap);
		assertEquals(22,zaino.getMaxVal());
		
		cap=4;
		int[] vol3 ={2,2,1,6,1};
		int[] val3={5,1,8,2,1};
		zaino = new Knapsack(val3,vol3,cap);
		assertEquals(14,zaino.getMaxVal());
		
		cap=6;
		int[] vol4 ={6,3,5,3,2};
		int[] val4={4,3,6,9,6};
		zaino = new Knapsack(val4,vol4,cap);
		assertEquals(15,zaino.getMaxVal());
		
		cap=10;
		int[] vol5 ={6,5,5,7};
		int[] val5={9,5,5,15};
		zaino = new Knapsack(val5,vol5,cap);
		assertEquals(15,zaino.getMaxVal());
	}


}
