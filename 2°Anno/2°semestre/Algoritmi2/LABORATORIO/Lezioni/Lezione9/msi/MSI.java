package msi;

import java.util.ArrayList;

public class MSI {

	private int[] A;
	private int[] tmp;

	private ArrayList<Integer> S;
	public	MSI(int[]	w)	
	{
		tmp = w;
	}
	
	private int max(int a, int b)
	{
		if(a>=b)
			return a;
		else
			return b;
	}
	private void inizializza()
	{
		A = new int[tmp.length+1];
		A[0]= 0 ;
		A[1]= tmp[0];
		
		for(int i = 2; i<=tmp.length; i++)
			A[i]= max(A[i-1],A[i-2]+tmp[i-1]);
	
	}
	
	private void solOttimale()
	{
		inizializza();
		S = new ArrayList<Integer>();
		int i = A.length-1;
		
		while(i>0)
		{
			if(A[i]>A[i-1])
			{
				S.add(i);
				i = i-2;
			}
			else
				i=i-1;
				
		}
	}
	
	public	int	getMaxVal()
	{
		solOttimale();
		return A[tmp.length];
	}
	
	public	ArrayList<Integer>	getOptSol()
	{
		solOttimale();
		return S;
	}
}
