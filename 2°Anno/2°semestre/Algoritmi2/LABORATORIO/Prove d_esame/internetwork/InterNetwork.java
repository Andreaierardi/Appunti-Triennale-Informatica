package internetwork;

import java.util.ArrayList;
import it.uniupo.graphLib.*;

public class InterNetwork {
	
	//Dichiaro i campi della classe che mi serviranno
	
	//g mi servirà per poter utilizzare i metodi dei grafi nella classe
	private UndirectedGraph g;
	//Scoperti tiene traccia dei scoperti
	private boolean scoperti[];
	//Array dist ci aiuta a tenere traccia delle distanza
	private int dist[];
	//ArrayList che utilizzeremo come coda per la bfs
	private ArrayList<Integer> coda;
	
	//Costruttore della classe
	public InterNetwork(UndirectedGraph net)
	{
		g = net;
	}
	
	//Metodo privato per inizializzare tutti i campi
	private void init()
	{
		coda = new ArrayList<Integer>();
		scoperti= new boolean[g.getOrder()];
		dist = new int[g.getOrder()];
		for (int i = 0 ; i<g.getOrder();i++)
		{
			scoperti[i]=false;
			dist[i]=1; //dist[i] inizializzata a 1 poichè bisogna tenere conto anche del nodo stesso
			//come dice l'esercizio:
			//"contando anche r1 ed r2"
		}
	}
	
	//Algoritmo utilizzato è quello della BFS con le distanze
	//Questo perchè richiede il cammino minimo non pesato
	private void bfs(int s)
	{
		scoperti[s]=true;
		coda.add(s);
		while(!coda.isEmpty() )
		{
			int e = coda.remove(0);
			for(int vicino : g.getNeighbors(e))
				{
					if (scoperti[vicino]==false)
						{
							scoperti[vicino]=true;
							coda.add(vicino);	
							dist[vicino]=dist[e]+1;
						}
				}
		}
	}
	
	//Metodo per il numero di Hops
	public int numberOfHops(int r1, int r2)
	{
		
		//Verifico che i nodi passati come input esistano nel grafo e siano maggiori o uguali a 0
		if(r1>=g.getOrder() || r2>=g.getOrder() ||r1<0 ||r2<0)
			return -1;
		//funzione init per inizializzare tutti i campi
		init();
		
		//richiamo della bfs
		bfs(r1);
		
		//ritorno la distanza dalla sorgente r1 e il nodo r2
		return dist[r2];
	}
}
