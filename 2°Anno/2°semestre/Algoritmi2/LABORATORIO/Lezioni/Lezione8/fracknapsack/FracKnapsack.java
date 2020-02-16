package fracknapsack;

import it.uniupo.algoTools.MaxHeap;

public class FracKnapsack {

	private double cap;
	private double[] vol;
	private double[] val;
	private double[] dose;
	private double[] quant;
	private double valT;
	private MaxHeap<Integer, Double> heap;
	
	public FracKnapsack(double	capacity, double[]	volume,	double[] value)
	{
		
		vol = volume;
		val = value;
		cap = capacity;
		inizializza();
	}

	private void inizializza()
	{
		dose = new double[vol.length];
		quant =new double[vol.length];
		valT =0;
		for (int i = 0 ; i<vol.length; i++)
			dose[i]= 0 ;
		heap = new MaxHeap<Integer, Double>();
	}
	private void zaino()
	{
		inizializza();
		for (int i = 0 ; i<vol.length; i++)
			{
				dose[i]= 0 ;
				quant[i]=0;
				heap.add(i, val[i]/vol[i]);
			}
		double sR = cap;
		while(sR >0 && !heap.isEmpty())
		{
			int m = (int) heap.extractMax();
			if (sR >= vol[m] )
			{
					dose[m]=1;
					quant[m]=vol[m];
					valT+= val[m];
			}
			else
			{
				dose[m] = sR /vol[m];
				quant[m]=sR;
				valT += val[m]*dose[m];
			}
			sR-=vol[m];
		}
		
	}
	public	double	maxVal()
	{
		zaino();
		return valT;
	}
	public	double	dose(int i)
	{
		return dose[i];
	}
}
