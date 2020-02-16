package tipologiaclienti;

import it.uniupo.algoTools.MinHeap;
import it.uniupo.algoTools.*;
import it.uniupo.graphLib.*;

public class TipoligaClienti {
	
	private MinHeap<Edge,Integer> heap;
	private UnionFind uf;
	private UndirectedGraph g;
	private int cluster;
	private int p;
	public TipoligaClienti(UndirectedGraph dati)
	{
		g = dati;
	}
	
	private void init()
	{
		heap = new MinHeap<Edge,Integer> ();
		uf = new UnionByRank(g.getOrder());
		cluster=g.getOrder();
	}
	
	private void kruskal()
	{
		for(int i =0 ; i<g.getOrder();i++)
			for(Edge vicino: g.getIncidentEdges(i))
				heap.add(vicino,vicino.getWeight());
		Edge e = new Edge(0,0,0);
		while (!heap.isEmpty() && e.getWeight()<p )
		{
			e = heap.extractMin();

			int u = e.getTail();
			int v = e.getHead();
		
			if(uf.find(u)!=uf.find(v) && e.getWeight()<p)
			{
				uf.union(uf.find(u),uf.find(v));
				cluster=uf.getNumberOfSets();
			}
		}
	}
	
	public int numeroTipologie(int differenzaRichiesta)
	{
		p= differenzaRichiesta;
		init();
		kruskal();
		return cluster;
	}
}
