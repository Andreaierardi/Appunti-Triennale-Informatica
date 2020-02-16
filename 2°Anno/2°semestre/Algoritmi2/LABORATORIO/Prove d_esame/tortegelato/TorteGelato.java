package tortegelato;

import it.uniupo.algoTools.*;
import it.uniupo.graphLib.*;

public class TorteGelato {
	
	private DirectedGraph g;
	private boolean scoperti[];
	private int dist[];
	private int b;
	private int pG;
	private MinHeap<Edge,Integer> heap;
	public TorteGelato(DirectedGraph mappa, int base, int parametroGhiaccio)
	{
		g = mappa;
		b = base;
		pG = parametroGhiaccio;
	
	}
	
	private void init()
	{
		heap = new MinHeap<Edge,Integer> ();
		scoperti= new boolean[g.getOrder()];
		dist = new int[g.getOrder()];
		for (int i = 0 ; i<g.getOrder();i++)
		{
			scoperti[i]=false;
			dist[i]=-1;
		}
	}
	private void dijkstra(int s)
	{
		for(Edge arco : g.getIncidentEdges(s))
				heap.add(arco,dist[s]+arco.getWeight());
		scoperti[s]=true;
		dist[s]=0;
		int u,v,w;
		
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
			v =e.getHead();
			u = e.getTail();
			
			if (scoperti[v]==false)
			{
				scoperti[v]=true;
				dist[v]=dist[u]+e.getWeight();
				for(Edge arco: g.getIncidentEdges(v))
				{
					w = arco.getHead();
					if(scoperti[w]==false)
						heap.add(arco, dist[w]+arco.getWeight());
				}
			}
			
		}
	}
	//>< 
	public int ghiaccioMinimo(int dest,int weight)
	{
		if(weight<0 || dest<0 ||dest>=g.getOrder() )
			throw new  java.lang.IllegalArgumentException();
		
		init();
		dijkstra(b);
		if(scoperti[dest]==false)
			return -1;		
		return dist[dest]*pG*weight;
	}
}
