package hikes;

import it.uniupo.algoTools.*;
import it.uniupo.graphLib.*;

public class Hikes {

	//Dichiaro tutti i campi della classe
	
	//Union find 
	private UnionFind uf;
	//Dichiarazione di un grafo che ci permette di poter utilizzare i metodi nella classe
	private UndirectedGraph g;
	
	//Dichiarazione dell'heap per ordinarli in ordine di peso
	private MinHeap<Edge,Integer> heap;
	//Campo zone
	private int nZone;
	//Campo spaziamento
	private int spaziamento;
	
	//Costruttore dove assegno il grafo rifugi a g.
	public Hikes(UndirectedGraph rifugi)
	{
		g = rifugi;
	}
	
	//metodo in cui inizializzare i campi
	private void inizializza()
	{
		heap= new MinHeap<Edge,Integer>();
		uf= new UnionByRank(g.getOrder());
	}
	
	//In questo caso abbiamo bisogno di kruskal per poter ottenere lo spaziamento.
	private void kruskal()
	{
		inizializza();

		for(int i= 0 ;i<g.getOrder();i++)
			for (Edge arco : g.getIncidentEdges(i))
				heap.add(arco, arco.getWeight());
		while(!heap.isEmpty()&& uf.getNumberOfSets()>=nZone)
		{
			Edge e = heap.extractMin();
			uf.union(uf.find(e.getTail()), uf.find(e.getHead()));
		}
		
		spaziamento = heap.extractMin().getWeight();
		
	}
	
	public int minDistanza(int numZones)
	{
		if(numZones<0)
			throw new  java.lang.IllegalArgumentException();
		inizializza();
		nZone = numZones; 
		kruskal();
		return spaziamento;
	}
}
