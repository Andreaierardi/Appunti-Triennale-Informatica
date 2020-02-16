package heavyroutes;

import it.uniupo.algoTools.MinHeap;
import it.uniupo.graphLib.*;

public class HeavyRoutes {
	private GraphInterface g;
	private int[][] maxW;
	
	private MinHeap<Edge,Integer> heap;
	private boolean[] scoperti;
	private int[] dist;
	private int w;
	public HeavyRoutes(GraphInterface carta,int[][]maxWeight)
	{
		maxW=maxWeight;
		g = carta;
	}
	
	private void init()
	{
		heap = new MinHeap<Edge,Integer>();
		scoperti = new boolean[g.getOrder()];
		dist = new int[g.getOrder()];
		for (int i =0 ; i<g.getOrder();i++)
		{
			dist[i]=-1;
			scoperti[i]=false;
		}
		
	}
	
	private void dijkstra(int sorg)
	{
		scoperti[sorg]=true;
		dist[sorg]=0;
		for(Edge vicino:g.getIncidentEdges(sorg))
				heap.add(vicino,dist[sorg]+vicino.getWeight());
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
			int u = e.getTail();
			int v= e.getHead();
			if(maxW[u][v]<=w)
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
	
	public int distance(int partenza, int destinazione, int weight)
	{
		init();
		w=weight;
		if(partenza <0 || destinazione <0 ||partenza >=g.getOrder()||destinazione >=g.getOrder() ||w<=0)
			return -2;
		dijkstra(partenza);
		return dist[destinazione];
	}
	
}
