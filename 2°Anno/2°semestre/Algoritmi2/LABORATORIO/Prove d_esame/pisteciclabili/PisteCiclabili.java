package pisteciclabili;

import it.uniupo.algoTools.MinHeap;
import it.uniupo.graphLib.*;

public class PisteCiclabili {
	
	private MinHeap<Edge,Integer> heap;
	private boolean[] scoperti;
	private int MST;
	private UndirectedGraph g;
	private int [][]t;
	
	public PisteCiclabili(UndirectedGraph mappaCosti, int [][]tempo)
	{
		g = mappaCosti;
		t = tempo;
	}
	
	private void prim(int s)
	{
		scoperti[s]=true;
		for(Edge v : g.getIncidentEdges(s))
			heap.add(v,v.getWeight());
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
			int u = e.getTail();
			int v = e.getHead();
			if(scoperti[v]==false)
			{
				scoperti[v]=true;
				MST+=t[u][v];
				for(Edge arco: g.getIncidentEdges(v))
				{
					int w = arco.getHead();
					if(scoperti[w]==false)
						heap.add(arco,arco.getWeight());
				}
			}
		}
	}
	
	private void  init()
	{
		heap = new MinHeap<Edge,Integer>();
		MST = 0;
		scoperti = new boolean[g.getOrder()];
		for(int i = 0 ; i <g.getOrder(); i++)
			scoperti[i]=false;
	}
	
	public boolean possibileEntro(int maxNumGiorni)
	{
		init();
		prim(0);
		if(maxNumGiorni< MST)
			return false;
		return true;
		
	}
}
