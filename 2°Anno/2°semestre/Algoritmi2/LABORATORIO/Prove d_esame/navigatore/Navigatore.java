package navigatore;

import it.uniupo.algoTools.MinHeap;
import it.uniupo.graphLib.*;

public class Navigatore {
	private MinHeap<Edge,Integer> heap;
	private boolean[] scoperti;
	private DirectedGraph g;
	private boolean evita;
	private int sorg;
	private boolean[][] as;
	private int[] dist;
	
	public Navigatore(DirectedGraph carta, int partenza, boolean[][] autostrada)
	{
		g= carta;
		sorg = partenza;
		as= autostrada;
	}
	
	private void init()
	{
		
		heap = new  MinHeap<Edge,Integer>();
		scoperti = new boolean[g.getOrder()];
		dist = new int[g.getOrder()];
		for(int i =0 ;i <g.getOrder();i++)
		{
				scoperti[i]=false;
				dist[i]=-1;
		}
		
	}
	private void dijkstra(int s)
	{
		scoperti[s]= true;
		dist[s]=0;
		for (Edge vicino: g.getIncidentEdges(s))
			heap.add(vicino,dist[s]+vicino.getWeight());			
		
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
			int u = e.getTail();
			int v = e.getHead();
			if(as[u][v]==true && evita)
				continue;
			if(scoperti[v]==false)
			{
				scoperti[v]=true;
				dist[v]=dist[u]+e.getWeight();
				for(Edge arco: g.getIncidentEdges(v))
				{
					int w = arco.getHead();
					if(scoperti[w]==false)
					{
						
						heap.add(arco,dist[v]+arco.getWeight());
					}
				}
			}
				
		}
		
	}
	
	public int distance(int destinazione, boolean evitaAutostrada)
	{
		init();
		if(destinazione<0 || destinazione>=g.getOrder())
			return -1;
		evita = evitaAutostrada;
		dijkstra(sorg);
		return dist[destinazione];
	}
}
