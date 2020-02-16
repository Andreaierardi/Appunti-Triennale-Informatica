package bfs;

import java.util.ArrayList;

import it.uniupo.graphLib.GraphInterface;

public class BFS {

	ArrayList<Integer> coda;
	boolean[] scoperti;
	ArrayList<Integer> risultato;
	GraphInterface grafo;
	int[] distanza;
	GraphInterface albero;

	public	BFS(GraphInterface	g)
	{
		this.grafo= g;

	}

	private void bfs(int u)
	{
		coda.add(u);
		this.distanza[coda.get(0)] = 0;
		while(!coda.isEmpty())
		{
			if(scoperti[coda.get(0)]==true)
				coda.remove(coda.get(0));
			else if (this.scoperti[coda.get(0)]==false)
			{
				this.scoperti[coda.get(0)]= true;
				for (int x : grafo.getNeighbors(coda.get(0)))
					if(this.scoperti[x]!=true)
					{
						distanza[x]=distanza[coda.get(0)]+1;
						coda.add(x);
					}
				this.risultato.add(coda.get(0));
				coda.remove(coda.get(0));
			}

		}
	}

	private void inizializza()
	{
		this.coda = new ArrayList<Integer>();
		this.scoperti= new boolean [grafo.getOrder()];
		this.distanza= new int [grafo.getOrder()];	
		this.risultato = new ArrayList<Integer>();
		for(int i = 0 ; i<grafo.getOrder() ; i++)
		{
			this.scoperti[i]=false;
			this.distanza[i]=-1;
		}	
	}

	public	ArrayList<Integer>	getNodesInOrderOfVisit(int sorgente) 
	{
		inizializza();
		bfs(sorgente);
		return this.risultato;
	}
	public int[] getDistance(int sorgente)
	{
		inizializza();
		bfs(sorgente);
		return this.distanza;
	}

	public GraphInterface bfsTree(int sorgente)
	{
		GraphInterface tree= grafo.create();
		scoperti = new boolean [grafo.getOrder()];
		scoperti[sorgente] = true;
		coda = new ArrayList<Integer>();

		coda.add(sorgente);
		coda.add(sorgente);
		while(!coda.isEmpty())
		{
			int nodo = coda.remove(0);

			for(int vicino : grafo.getNeighbors(nodo))
				if(scoperti[vicino]==false)
				{
					scoperti[vicino]=true;
					coda.add(vicino);
					tree.addEdge(nodo, vicino);
				}
		}
		return tree;
	}

	public int[] getOrderOfVisit(int s)
	{
		int [] ordine = new int [grafo.getOrder()];
		for (int x : this.getNodesInOrderOfVisit(s))
			ordine[x]=this.getNodesInOrderOfVisit(s).indexOf(x);
		return ordine;	
	}

}

