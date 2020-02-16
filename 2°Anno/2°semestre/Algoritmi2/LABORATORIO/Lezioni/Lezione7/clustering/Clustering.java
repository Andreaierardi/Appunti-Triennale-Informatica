package clustering;

import it.uniupo.algoTools.*;
import it.uniupo.graphLib.*;

public class Clustering {
	private UndirectedGraph g;
	private MinHeap<Edge,Integer>heap=new	MinHeap<Edge,Integer>();
	private int numC;
	private int spaziamento;
	private UnionFind uf;	
	
	public Clustering(UndirectedGraph grafo, int numCluster) {
		g = grafo;
		numC = numCluster;
	}
	
	private void inizializza(){
	
		heap= new MinHeap<Edge,Integer>();
		uf = new UnionByRank(g.getOrder());
	}
	
	private void clustering()
	{
		for(int i =0 ; i<g.getOrder();i++)
			for (Edge vicino: g.getIncidentEdges(i))
				heap.add(vicino,vicino.getWeight());
		
		while(!heap.isEmpty() && uf.getNumberOfSets()>=numC)
		{
			Edge e = heap.extractMin();
			int w=e.getHead();
			int u =e.getTail();
			uf.union(uf.find(u), uf.find(w));
		}
		
		spaziamento= heap.extractMin().getWeight();
		
	}
	public int spaziamento(){
		inizializza();
		clustering();
		return spaziamento;
		
	}

	public boolean sameCluster(int a, int b){
		inizializza();
		clustering();
		System.out.println(uf.toString());
		if(uf.find(a)==uf.find(b))
			return true;	
		return false;
		
	}
	
}