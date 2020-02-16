package gite;

import java.util.ArrayList;

import it.uniupo.graphLib.*;

public class Gite {
	
	private UndirectedGraph g;
	private int [][] df;
	private int max;
	
	//Strutture per poter gestire l'algoritmo BFS
	
	int dist[];
	boolean scoperti[];
	ArrayList<Edge> coda; //In questo caso la coda è di Edge poichè il grafo è pesato

	//Costruttore della classe
	public Gite(UndirectedGraph sentieri,int[][]diff)
	{
		g = sentieri;
		df = diff;
	}
	
	//Inizializzazione delle strutture dati
	private void init()
	{
		dist = new int[g.getOrder()];
		scoperti = new boolean[g.getOrder()];
		for (int i =0 ; i<g.getOrder();i++)
		{
			dist[i]=-1;
			scoperti[i] = false;
		}
		coda = new ArrayList<Edge>();
	}
	
	//L'algoritmo da utilizzare è una BFS e non Dijkstra.
	//Il motivo principale è perchè il grafo è non orientato
	//(Dijkstra è applicabile sia in grafi orientati che non però negli esercizi solo su orientati)
	//Inoltre l'algoritmo che si presta meglio dopo Dijkstra per le distanza è cercatamente la BFS
	
	//Nella consegna c'è un indizio "che richieda il minimo numero di giorni possibile (ovvero, equivalentemente,di passare per il minimo numero di rifugi possibile)
	
	//Per usare BFS con pesi bisogna usare una sorta di Dijkstra ma con una Lista
	private void bfs(int s)
	{
		
		//Scorro tutti i vicini della sorgente e li aggiungo nella coda
		//Inoltre, inizializzo a 0 la distanza della sorgente
		for(Edge vicino :g.getIncidentEdges(s))
		{ 
				coda.add(vicino);
				dist[vicino.getTail()]=0;
		}
	
		while(!coda.isEmpty())
		{
			//Estraggo l'arco coda
			Edge e= coda.remove(0);
			//Per semplicità assegno la coda a u e la tail a w
			int u = e.getTail();
			int v = e.getHead();
			
			//Se il nodo v non è ancora stato scoperto e difficoltà è minore del massimo passato in input
			if(scoperti[v]==false && max>df[u][v])
			{
				//Lascio la print commentata in caso tu voglia vedere come vengono estratti gli archi
				//System.out.println("Arco: ("+u+","+w+")");
				
				// Allora procedo con la scoperta del nodo e l'aggiornamento della distanza
				scoperti[v]=true;
				dist[v]=dist[u]+e.getWeight();
				//Come in dijkstra cerco tutti i vicini del nodo e aggiorno le distanze e aggiungo gli archi in coda
				for (Edge arco : g.getIncidentEdges(v))
				{	
					//assegnoa  z per semplificare
					int z = arco.getHead();
					//Se z non è ancora stato scoperto allora aggiungo in coda e aggiorno la sua distanza
					if(this.scoperti[z]==false)
					{
						coda.add(arco);
						dist[z]=dist[v]+arco.getWeight();
					}
						
				}
			}
			
		}
	}
	//Funzione richiesta dalla consegna
	public int dislivelloTotale(int partenza, int arrivo, int maxDiff)
	{
		//Se non rientra nei nodi allora lancio eccezione
		if(partenza < 0 || arrivo<0 || partenza>=g.getOrder() ||arrivo>=g.getOrder())
			throw new IllegalArgumentException();
		//Assegno il massimo ad un campo per poterlo usare in tutta la classe
		max = maxDiff;
		//Inizializzo strutture dati
		init();
		//Lancio visita dalla sorgente
		bfs(partenza);
		//Ritorno distanza trovata
		return dist[arrivo];
	}
}
