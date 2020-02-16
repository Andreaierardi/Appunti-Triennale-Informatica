package knapsack;

public class Knapsack {
	
	private int capy;
	private int l;
	private int[] vol;
	private int[] val;
	private int[][] tabella;
	
	public	Knapsack(int[]	value,	int[]	volume,	int	capacity)
	{
		vol = volume;
		val = value;
		capy = capacity;
		l=vol.length;
		inizializza();
	}
		
	private void inizializza()
	{
		tabella = new int[l+1][capy+1];
		for(int i = 0; i<=capy;i++)
			tabella[0][i] = 0 ;
	}
		
	public	int	getMaxVal()
	{
		inizializza();
		for(int n = 1; n<=l;n++)
			for(int cap =0;cap<=capy; cap++)
			{
				if(vol[n-1]<=cap)
					tabella[n][cap]= Math.max(tabella[n-1][cap-vol[n-1]]+val[n-1],tabella[n-1][cap]);
				else
					tabella[n][cap]= tabella[n-1][cap];
					
			}
		return tabella[l][capy];
		
	}

}
