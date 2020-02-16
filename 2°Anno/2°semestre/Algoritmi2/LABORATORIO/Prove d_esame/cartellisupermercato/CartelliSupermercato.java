package cartellisupermercato;

import it.uniupo.algoTools.MinHeap;
import it.uniupo.graphLib.*;

public class CartelliSupermercato {
	
	private UndirectedGraph g;
	private int sorg;
	private int [] padri;
	private int [] dist;
	private MinHeap <Edge,Integer> heap;
	private boolean [] scoperti;
	
	public CartelliSupermercato(UndirectedGraph centroAbitato,int posizioneNegozio)
	{
		g=centroAbitato;
		sorg = posizioneNegozio;
	}
	
	private void init()
	{
		padri =new int[g.getOrder()];
		dist =new int[g.getOrder()];

		scoperti= new boolean[g.getOrder()];
		for (int i = 0 ; i<g.getOrder(); i++)
		{
			padri[i]=-2;
			scoperti[i]=false;
			dist[i]=-1;
		}
		heap = new MinHeap <Edge,Integer>();
	}
	
	private void dijkstra(int sorg)
	{
		scoperti[sorg]=true;
		padri[sorg]=-1;
		dist[sorg]=0;
		for(Edge v : g.getIncidentEdges(sorg))
			heap.add(v,v.getWeight());
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
			int u = e.getTail();
			int v = e.getHead();

			if(scoperti[v]==false)
				{
					scoperti[v]=true;
					dist[v]=dist[u]+e.getWeight();
					padri[v]=u;
					
					for(Edge arco: g.getIncidentEdges(v))
					{
						int w = arco.getHead();
						if(scoperti[w]==false)
							heap.add(arco, dist[v]+arco.getWeight());
					}
				}
			
		}
	}
	public int direzioneIndicata(int qui)
	{
		if(sorg == qui)
			return -1;
		init();
		dijkstra(sorg);
		return padri[qui];
	}
}
