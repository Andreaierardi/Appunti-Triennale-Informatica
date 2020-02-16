package db_esame;

import it.uniupo.algoTools.MaxHeap;

public class DB {

	//Campi necessari per l'algoritmo
	MaxHeap<Integer,Double> heap;
	double ValT;
	double [] d;
	int [] vol;
	double [] val;
	double sR;

	//SumT è la somma di tutti i valori
	double sumT;

	//Costruttore dove assegno vol e val per poterli utilizzare nella classe
	public DB (int []dim , double[] time )
	{
		vol = dim;
		val = time;
	}
	//Metodo per inizializzare tutti i campi
	private void init()
	{
		d = new double[vol.length];
		heap = new MaxHeap<Integer,Double>();
		ValT=0;
		sumT=0;
	}
	//Algoritmo dello zaino frazionario
	//Questo perchè dobbiamo prendere una certa quantità e pesarla
	//Quindi si utilizza questo algoritmo
	private void zainoFraz()
	{
		for(int i =0 ; i<vol.length; i++)
		{
			d[i]=0;
			heap.add(i, val[i]/vol[i]);
			sumT+=val[i];
		}
		
		while(!heap.isEmpty() && sR>0)
		{
			int x = heap.extractMax();

			if(sR>=vol[x])
			{
				d[x]=1;
				ValT+= val[x];
			}
			else
			{	

				d[x]=sR/vol[x];
				ValT+=d[x]*val[x];
			}
			
			sR-=vol[x];
		}
		
	}
	//Metodo richiesto dall'esercizio
	//Salvo la somma di tutti i tempi e la sottraggo al tempo migliore
	//In questo modo ottengo il "complementare"
	//Infatti l'esercizio richiede il tempo per ricostruire i record NON SCELTI
	//Se fosse il tempo dei record presi in considerazione basterebbe Val(S) che è il valore
	//della soluzione
	public double timeToRebuild(int memSpace)
	{
		//inizializzo
		init();
		//Controllo su memspace per lanciare eccezione
		if(memSpace<0)
			throw new IllegalArgumentException();
		
		//assegno sR a memspace in modo da poter utilizzare in tutta la classe
		sR= memSpace;
		//Richiamo l'algoritmo
		zainoFraz();
		
		//Ritorno quindi il complementare 
		return sumT-ValT;		
	}

}
