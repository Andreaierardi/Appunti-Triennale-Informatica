package garden;

import it.uniupo.algoTools.MinHeap;
import it.uniupo.algoTools.*;
import it.uniupo.graphLib.*;

public class Garden {
	
	private UndirectedGraph g;
	private MinHeap<Edge,Integer> heap ;
	private UnionFind uf;
	private UndirectedGraph albero;
	private Edge arco;
	private int MST;
	
	public Garden(UndirectedGraph garden)
	{
		g = garden;
	}
	
	private void init()
	{
		heap = new MinHeap<Edge,Integer> ();
		uf = new UnionByRank(g.getOrder());
		albero = (UndirectedGraph) g.create();
		MST = 0;
	}
	private void kruskal()
	{
		for(int i = 0 ; i<g.getOrder();i++)
			for(Edge vicino: g.getIncidentEdges(i))
				heap.add(vicino,vicino.getWeight());
		
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
			
			
			if(uf.find(e.getHead())!=uf.find(e.getTail()))
				{
					if((e.getTail()==arco.getTail() && e.getHead()==arco.getHead() )||(e.getHead()==arco.getTail() &&e.getTail()==arco.getHead()))
							arco = e;
						
					uf.union(uf.find(e.getTail()),uf.find(e.getHead()));
					albero.addEdge(e);
					MST+=e.getWeight();
				}
		}
	}
	
	public int cable(int u, int v)
	{
		if(v>=g.getOrder() || u>=g.getOrder())
			throw new java.lang.IllegalArgumentException();
		init();
			
		arco = new Edge(u,v,-1);
		kruskal();
		
		if(u==-1)
			return MST;
		return arco.getWeight();
	}
	
	
}
