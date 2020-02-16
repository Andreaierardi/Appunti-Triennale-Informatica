package zainomsi;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestZainoMSI {

	@Test
	public void test() {
		
		int p  = 7;
		int vol[]={4,4,6,6,1};
		int val[]= {8,3,10,2,8};
		ZainoMSI ZainoMSI = new ZainoMSI(p,vol,val);
		System.out.println(ZainoMSI.getOptSol().toString());

	}
}
