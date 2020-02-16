package db;

import static org.junit.Assert.*;

import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.Test;

public class TestDB {

	@Test
	public void test() {
		
		double[] vol ={3,2,4};
		double[] val={2,5,1};
		DB zaino = new DB(vol,val);
		System.out.println(zaino.timeSaved(10));

	}
}

