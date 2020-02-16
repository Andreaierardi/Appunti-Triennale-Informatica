package esamehikes;

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
	//Campo max
	private int max;
	//Campo spaziamento
	private int cntZones;
	
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
	
	//In questo caso abbiamo bisogno di kruskal per poter ottenere il numero di Cluster
	private void kruskal()
	{
	
		//vengono aggiunti tutti gli archi del grafo 
		for(int i= 0 ;i<g.getOrder();i++)
			for (Edge arco : g.getIncidentEdges(i))
					{
						if(arco.getWeight()<0) //qui avviene il controllo che i pesi siano positivi come richiesto nella consegna
							throw new  java.lang.IllegalArgumentException();

						heap.add(arco, arco.getWeight());
					}
		//do while in modo da poter fare il controllo sul peso dell'arco.
		//Quando supero il massimo significa che devo fermarmi e controllare il numero di rappresentanti prima che avvenga l'ultima union
		//Infatti cntZones viene posto prima della union per evitare di calcolare la union finale
		Edge e;
		do
		{
			e = heap.extractMin();
			cntZones= uf.getNumberOfSets();
			uf.union(uf.find(e.getTail()), uf.find(e.getHead()));	
		}while(!heap.isEmpty()&& e.getWeight()<=max);

	}
	
	//Funzione dellla consegna
	public int zones(int maxDistanza)
	{
		//Controllo che maxDistanza sia maggiore di 0
		if(maxDistanza<=0)
			throw new  java.lang.IllegalArgumentException();
		//inizializza campi
		inizializza();
		//Si assegna max a maxDistanza in modo da poterlo usare in tutta la classe
		max = maxDistanza; 
		//Si richiama l'algoritmo di kruskal
		kruskal();
		return cntZones;
	}
}
