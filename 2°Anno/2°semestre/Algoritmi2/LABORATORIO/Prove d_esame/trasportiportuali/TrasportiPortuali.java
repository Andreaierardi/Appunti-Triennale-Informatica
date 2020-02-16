package trasportiportuali;

import java.util.ArrayList;

public class TrasportiPortuali {

	private int[] gd;
	private int[] A;
	private ArrayList<Integer> sol;
	
	public TrasportiPortuali(int[] guadagno)
	{
		gd= guadagno;
	}
	
	
	private void solOttimale()
	{
		A = new int[gd.length+1];
		A[0]=0;
		A[1]=gd[0];
		
		for (int i = 2; i<=gd.length;i++)
			A[i]=Math.max(A[i-1],A[i-2]+gd[i-1]);	
		
		sol=new ArrayList<Integer> ();
		int i =A.length-1;
		while(i>0)
		{
			if(A[i]>A[i-1])
			{
				sol.add(i-1);
				i=i-2;
			}
			else
				i--;
		}
		
	}
	
	public boolean accettareCarico(int s)
	{
		solOttimale();
		if(!sol.contains(s))
			return false;
		return true;
	}
	
}
