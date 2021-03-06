package groups;

public class Groups {

	private int [] val;
	private int [] vol;
	private int c;
	private int l;
	private int sol[][];
	private int sumV;
	
	public Groups (int availableSeats)
	{
		c = availableSeats;
	}
	
	public int optimalRebookingCost(int[] groupSizes, int[] groupCosts)
	{
		val = groupCosts;
		vol= groupSizes;
		if(c<0 || val.length!= vol.length)
			return -1;
		
		l = vol.length;
		sol = new int[l+1][c+1];
		
		for (int i = 0; i<val.length;i++)
			sumV+=val[i];
		
		for (int i = 0 ; i<=c; i++)
			sol[0][i]=0;
		for(int n = 1; n<=l;n++)
			for(int cap =0;cap<=c; cap++)
			{
				if(vol[n-1]<=cap)
					sol[n][cap]= Math.max(sol[n-1][cap-vol[n-1]]+val[n-1],sol[n-1][cap]);
				else
					sol[n][cap]= sol[n-1][cap];
			}

		return sumV-sol[l][c];
	}
}
