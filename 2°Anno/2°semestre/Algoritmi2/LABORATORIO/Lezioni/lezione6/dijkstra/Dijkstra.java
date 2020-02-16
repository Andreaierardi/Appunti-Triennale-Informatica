package dijkstra;

import java.util.ArrayList;

import it.uniupo.algoTools.*;
import it.uniupo.graphLib.*;

public class Dijkstra {

	private GraphInterface g;
	private boolean[] scoperti;
	private int [] distanze;
	private MinHeap<Edge,Integer>heap=new	MinHeap<Edge,Integer>();
	private GraphInterface tree;
	private Edge[] arrayCammini;
	
	public Dijkstra(GraphInterface	grafo)
	{
		this.g = grafo;
		checkWeight();

		inizializza();
	}
	
	private void checkWeight()
	{
		inizializza();
		
		for (int i = 0; i<g.getOrder();i++)
			for (Edge vicini: g.getIncidentEdges(i))
				if(vicini.getWeight()<0)
					throw new java.lang.IllegalArgumentException("Errore, pesi negativi");

		
	}
	private void inizializza()
	{
		scoperti= new boolean[g.getOrder()];
		distanze= new int[g.getOrder()];
		arrayCammini= new Edge[g.getOrder()];
		for (int i = 0; i<g.getOrder();i++)
			{
				scoperti[i]=false;
				distanze[i]=-1;
			}
		tree=g.create();
	}
	private void dijkstra(int s)
	{
		if(s >= g.getOrder()|| s<0)
			throw new IllegalArgumentException("La sorgente non è un nodo del grafo");

		scoperti[s]=true;
		distanze[s]=0;
		for (Edge vicino: g.getIncidentEdges(s))
				heap.add(vicino,distanze[s]+vicino.getWeight());
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
			int w=e.getHead();
			int u =e.getTail();
			

			if (scoperti[w]==false)
			{
				scoperti[w]=true;
				distanze[w]=distanze[u]+e.getWeight();
				arrayCammini[w]=e;
				tree.addEdge(u, w);

				for(Edge arco:g.getIncidentEdges(w))
					{
						int z =arco.getHead();
						if(scoperti[z]==false)
								heap.add(arco, distanze[w]+arco.getWeight());
							
					}
			}

		}
		
	}
	public	int[]	getDistanze(int	sorg)
	{	
		inizializza();
		dijkstra(sorg);
		
		return distanze;
	}
	
	public	GraphInterface	getAlberoCamminiMinimi(int	sorg)
	{
		inizializza();
		dijkstra(sorg);
		return tree;

	}
	
	public ArrayList<Edge> getCamminoMinimo (int sorg, int destinazione) 
	{
		inizializza();
		dijkstra(sorg);
		ArrayList<Edge> camminoMin= new ArrayList<Edge>();
	
		if(destinazione<0 || destinazione>=g.getOrder())
			throw new java.lang.IllegalArgumentException("Destinazione non è un nodo del grafo");
		///se from[v] = null, allora o v=sorgente oppure v non è
		///nella stessa componente connessa di sorg 
		if(arrayCammini.length==0)
			return null;
		else
		{
			int nodo = arrayCammini[destinazione].getHead();
			while(arrayCammini[nodo]!=null)
			{
				camminoMin.add(arrayCammini[nodo]);
				nodo = arrayCammini[nodo].getTail();
			}
		}
		
		return camminoMin;
	}
		
}
