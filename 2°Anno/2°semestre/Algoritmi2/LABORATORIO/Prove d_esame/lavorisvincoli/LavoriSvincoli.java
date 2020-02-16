package lavorisvincoli;

import java.util.ArrayList;

public class LavoriSvincoli {

	private int[] c;
	private int[] A;
	private ArrayList<Integer> S;
	public LavoriSvincoli(int [] costo)
	{
		c = costo;
	}
	
	public boolean manutenzione(int sv)
	{
		if(sv<0 || sv>=c.length)
			throw new IllegalArgumentException();
		A = new int[c.length+1];
		A[0]=0;
		A[1]=c[0];
		for(int i=2;i<=c.length;i++)
			A[i]=Math.max(A[i-1], A[i-2]+c[i-1]);
		
		S= new ArrayList<Integer> ();
		int i = A.length-1;
		while(i>0)
		{
			if(A[i]>A[i-1])
			{
				S.add(i-1);
				i=i-2;
			}
			else
				i--;
		}
		if(!S.contains(sv))
			return false;
		return true;
	}
}
