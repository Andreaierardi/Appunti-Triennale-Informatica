package kruskal;

import it.uniupo.algoTools.*;
import it.uniupo.graphLib.*;

public class Kruskal implements MST {
	private UndirectedGraph g;
	private MinHeap<Edge,Integer>heap=new	MinHeap<Edge,Integer>();
	private UndirectedGraph tree;
	private int cost;
	private UnionFind uf;
	
	public Kruskal(UndirectedGraph grafo){
		g= grafo;
	}
	
	
	//il metodo create e’ implementato
	@Override
	public MST create(UndirectedGraph g) {
		return new Kruskal(g);  
	}
	
	private void inizializza(){
	
		heap= new	MinHeap<Edge,Integer>();
		uf = new UnionByRank(g.getOrder());
		tree=(UndirectedGraph) g.create();
		
	}
	
	private void kruskal()
	{
		for(int i =0 ; i<g.getOrder();i++)
			for (Edge vicino: g.getIncidentEdges(i))
				heap.add(vicino,vicino.getWeight());
		
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
	
			int w=e.getHead();
			int u =e.getTail();
	
			if(uf.find(u)!=uf.find(w))
			{
				tree.addEdge(u, w);
				cost+=e.getWeight();
				uf.union(uf.find(u), uf.find(w));
			}
				

		}
		
	}
	@Override
	public UndirectedGraph getMST(){
		inizializza();
		kruskal();
		return tree;
		
	}
	
	@Override
	public int getCost(){
		inizializza();
		kruskal();
		return cost;
		
	}
	
}