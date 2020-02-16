package db;

import it.uniupo.algoTools.MaxHeap;

public class DB {

	private double sR;
	private double[] t;
	private double[] d;
	private double[] dose;
	private int[] quant;
	private double valT;
	private MaxHeap<Integer, Double> heap;
	
	public DB(double[]	dim,	double[] time)
	{
		if (dim.length!=time.length)
			throw new java.lang.IllegalArgumentException();
		
		for (int i =0 ; i<dim.length;i++)
			if(dim[i]<0 || time[i]<0)
				throw new java.lang.IllegalArgumentException();
		d = dim;
		t = time;
		inizializza();
	}

	private void inizializza()
	{
		dose = new double[d.length];
		quant =new int[d.length];
		valT =0;
		for (int i = 0 ; i<d.length; i++)
			dose[i]= 0 ;
		heap = new MaxHeap<Integer, Double>();
	}
	private void zaino()
	{
		inizializza();
		for (int i = 0 ; i<d.length; i++)
			{
				dose[i]= 0 ;
				quant[i]=0;
				heap.add(i, t[i]/d[i]);
			}
		while(sR >0 && !heap.isEmpty())
		{
			int m = (int) heap.extractMax();
			if (sR >= d[m] )
			{
					dose[m]=1;
					quant[m]=(int) d[m];
					valT+= t[m];
			}
			else
			{
				dose[m] = sR /d[m];
				quant[m]=(int) sR;
				valT += t[m]*dose[m];
			}
			sR-=d[m];
		}
		
	}
	public int []memorize(int memSpace)
	{
		if(memSpace<0)
			throw new java.lang.IllegalArgumentException();
		sR=memSpace;
		zaino();
		return quant;
	}
	public	double	timeSaved(int memSpace)
	{
		if(memSpace<0)
			throw new java.lang.IllegalArgumentException();
		sR=memSpace;
		zaino();
		return valT;
	}
}
