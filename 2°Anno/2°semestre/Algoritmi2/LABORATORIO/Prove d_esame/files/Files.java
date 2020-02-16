package files;

public class Files {

	private int c;
	private int l;
	private int[] vol;
	private int[] val;
	private int[][] sol;
	private int sumV;
	
	public	Files(int[]	value,	int[]	volume)
	{
		vol = volume;
		val = value;
		l=vol.length;
	}

		
	public boolean isSufficient(int memSpace,int maxTime)
	{
		if(memSpace <0 || maxTime<0)
			throw new java.lang.IllegalArgumentException();

		c =memSpace;
		l = vol.length;
		sol = new int[l+1][c+1];
		sumV=0;
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

		if(	sumV-sol[l][c]>maxTime)
			return false;
		return true;
		
	}
	
}
