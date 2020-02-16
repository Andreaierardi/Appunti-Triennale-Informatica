package prim;

import it.uniupo.algoTools.*;
import it.uniupo.graphLib.*;

public class Prim implements MST {
	private UndirectedGraph g;
	private boolean[] scoperti;
	private MinHeap<Edge,Integer>heap=new	MinHeap<Edge,Integer>();
	private UndirectedGraph tree;
	private int cost;
	
	public Prim(UndirectedGraph grafo){
		g= grafo;
	}
	
	
	//il metodo create e’ implementato
	@Override
	public MST create(UndirectedGraph g) {
		return new Prim(g);  
	}
	
	private void inizializza(){
		this.scoperti = new boolean[g.getOrder()];
		for (int i = 0; i<g.getOrder();i++)
			scoperti[i]=false;
		heap= new	MinHeap<Edge,Integer>();
		tree=(UndirectedGraph) g.create();
	}
	
	private void prim(int s)
	{
		this.scoperti[s]= true;
		for (Edge vicino: g.getIncidentEdges(s))
			heap.add(vicino,vicino.getWeight());
		
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
	
			int w=e.getHead();
			int u =e.getTail();
	
			if (scoperti[w]==false)
			{
				scoperti[w]=true;
				tree.addEdge(u, w);
				cost+=e.getWeight();
				
				for(Edge arco:g.getIncidentEdges(w))
					{
						int v =arco.getHead();
						if(scoperti[v]==false)
								heap.add(arco, arco.getWeight());	
					}
			}

	}
		
	}
	@Override
	public UndirectedGraph getMST(){
		inizializza();
		prim(0);
		return tree;
		
	}
	
	@Override
	public int getCost(){
		inizializza();
		prim(0);
		return cost;
		
	}
	
}