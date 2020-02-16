package it.uniupo.algo2.grafi;

import java.util.ArrayList;

import it.uniupo.libPrimoLab.Edge;
import it.uniupo.libPrimoLab.GraphInterfaceEs;

public class DirectedGraph implements GraphInterfaceEs{
	/******************************
	 * aggiungete le variabili di istanza che vi servono
	 * io ce ne ho messa una
	 ******************************/
	private int numberOfEdges=0;
	private int matrice[][];
	private int peso[][];
	private int ordine;

	//costruisce un grafo con nVert nodi e nessun arco
	public DirectedGraph(int nVert) { 
		this.matrice = new int [nVert] [nVert];
		this.peso = new int [nVert] [nVert];
		this.ordine = nVert;
		for(int i= 0 ; i<nVert; i++)
			for (int j =0 ; j<nVert;j++)
				{
					matrice[i][j]=0;
					peso[i][j]=-1;
				}
		
	}
	//restituisce il numero di nodi del gafo
	@Override
	public int getOrder() { 
		return ordine;
	}	
	
	//restituisce il numero di archi del grafo
	@Override
	public int getEdgeNum(){
    	return numberOfEdges;
    }

    //aggiunge un arco non pesato al grafo
	@Override
	public void addEdge(int tail, int head) {
		matrice[tail][head]=1;
		this.numberOfEdges++;
	
	}
	
	//aggiunge un arco pesato al grafo
	@Override
	public void addEdge(int tail, int head, int weight) { 
		matrice[tail][head]=matrice[tail][head]=1;
		peso[tail][head]= weight;
		this.numberOfEdges++;
	}
	
	//restituisce true se (u,v) e' un arco del grafo, false altrimenti
	@Override
	public boolean hasEdge(int u, int v) {
		if (matrice[u][v]==1)
			return true;
		return false;
	}

	//restituisce i nodi adiacenti al nodo dato
	@Override
	public Iterable<Integer> getNeighbors(int u) { 
		ArrayList <Integer> neightbors = new ArrayList<Integer>();
		for (int i=0 ;i<this.ordine;i++)
			if(matrice[u][i]==1)
				neightbors.add(i);
		return neightbors;
	}

	//restituisce gli archi uscenti dal nodo dato
	@Override
	public Iterable<Edge> getIncidentEdges(int u) { 
		ArrayList <Edge> edges = new ArrayList<Edge>();
		for (int i=0 ;i<this.ordine;i++)
			if(matrice[u][i]==1)
				edges.add(new Edge(u,i,peso[u][i]));
		return edges;
	}
	
//	  /**
//  * Removes the specified edge from the graph (if the egde exists)
//  * @param tail tail of the edge to be removed
//  * @param head head of the edge to be removed
//  */
  public void removeEdge(int tail, int head){ //delete edge (tail,head)
	 
	if(matrice[tail][head]==1)
	{
		matrice[tail][head]=0;
		 peso[tail][head]=-1;
		 this.numberOfEdges--;
	}

 }


}
