package zainomsi;

import java.util.ArrayList;

public class ZainoMSI {

	
	private int capy;
	private int[] vol;
	private int[] val;
	
	
	private int[][] Val;
	private int[] tmp;
	private int numOgg;
	private int cap;
	private ArrayList<Integer> S;
	
	public	ZainoMSI(int C, int[] volume, int value[])	
	{
		val = value;
		vol = volume;
		numOgg = volume.length;
		cap = capy = C;
		zaino();
	}
	
	private int max(int a, int b)
	{
		if(a>=b)
			return a;
		else
			return b;
	}
	
	private void solOttimale()
	{
		S = new ArrayList<Integer>();
		while(numOgg>0 && cap > 0)
		{
			
			if(Val[numOgg][cap]>Val[numOgg-1][cap])
			{
				S.add(numOgg-1);
				numOgg = numOgg-1;
				cap = cap- vol[numOgg-1];
			}
			else
				numOgg = numOgg-1;
				
		}
	}
	
	public	ArrayList<Integer>	getOptSol()
	{
		solOttimale();
		return S;
	}
	
	private void inizializza()
	{
		Val = new int[vol.length+2][capy+1];
		for(int i = 0; i<=capy;i++)
			Val[0][i] = 0 ;
	}
		
	public void zaino()
	{
		inizializza();
		for(int n = 1; n<=Val.length-2;n++)
			for(int cap =0;cap<=capy; cap++)
			{
				if(vol[n-1]<=cap)
					Val[n][cap]= max(Val[n-1][cap-vol[n-1]]+val[n-1],Val[n-1][cap]);
				else
					Val[n][cap]= Val[n-1][cap];
					
			}		
	}
}
