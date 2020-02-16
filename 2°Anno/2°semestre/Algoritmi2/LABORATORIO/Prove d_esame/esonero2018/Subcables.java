package esonero2018;

import it.uniupo.algoTools.MinHeap;
import it.uniupo.algoTools.*;
import it.uniupo.graphLib.*;

public class Subcables {

	//Grafo g d'appoggio per poter utilizzare i metodi del grafo dentro la classe
	private UndirectedGraph g;
	//Struttura MinHeap e UnionFind per l'implementazione dell'algoritmo di Kruskal
	private MinHeap<Edge, Integer> heap;
	private UnionFind uf;

	//Array cost per poter utilizzare i costi all'interno della classe, idem min max 
	private int[][] cost;
	private int min;
	private int max;
	//Intero MST per registrare i pesi del MST
	private int MST;
	
	//numS salviamo il numero dei set quindi verifichiamo quanti cluster vi sono per controllare che l'albero creato sia connesso
	private int numS;
	
	//Costruttore della classe
	public Subcables(UndirectedGraph submap, int[][] costs)
	{
		cost = costs;
		g = submap;
	}
	
	//Metodo per inizializzare heap, union find e la somma degli archi del MST
	private void init()
	{
		heap = new MinHeap<Edge, Integer>();
		uf = new UnionByRank(g.getOrder());
		MST = 0 ;
	}
	
	//Si usa Kruskal poichè è richiesta la "soluzione di costo minimo" dalla consegna. 
	//Si parla di distanze e costo minimo, allora bisogna calcolare MST
	//Si potrebbe usare Prim ma kruskal è piu' veloce da implementare
	private void kruskal()
	{
		//Algoritmo di Kruskal(aggiunta archi nell'heap
		for(int i =0 ; i<g.getOrder();i++)
			for(Edge v : g.getIncidentEdges(i))
				//NB. In questo caso non aggiungo v e il peso dell'arco v ma ordino in base al costo nell'array dei costi
				//Questo perchè è richiesto che il cammino sia di costo minimo
				heap.add(v,cost[v.getTail()][v.getHead()]);
		
		while(!heap.isEmpty())
		{
			
			Edge e = heap.extractMin();
			int u = e.getTail();
			int v = e.getHead();
			if(uf.find(u)!=uf.find(v) && e.getWeight()>min && e.getWeight()<max) //Controllo per verificare che il peso sia compreso tra min e max
			{
				MST+=cost[u][v]; //Invece di aggiungere il peso dell'arco aggiungo il costo
				uf.union(uf.find(u), uf.find(v));
			}
		}
		numS= uf.getNumberOfSets(); //in questo modo verifichiamo quanti cluster vi sono dopo l'applicazione dell'algoritmo 
		//in questo modo vediamo se l'albero dei cammini minimi è connesso
	}
	
	//Metodo richiesto dalla consegna
	public int cost(int minDepth,int maxDepth)
	{
		//Assegno minDepth a min (idem per max) in modo da poter usare nella classe questi due campi
		min  = minDepth;
		max = maxDepth;
		//Controllo come da consegna, restituisce eccezione
		if(min> max || min<0 || max < 0)
			throw new  java.lang.IllegalArgumentException();
		//Inizializzazione
		init();
		//Richiamo dell'algoritmo
		kruskal();
		//Se viene generato un albero non conneso allora ritorna -1
		if(numS!=1)
			return -1;
		//Ritorno la somma dei costi trovati
		return MST;
	}
 }
