package softwaresystem;

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

	//NODI IN ORDINE DI VISITA GRAFO GENERALE
	public ArrayList<Integer> getNodesInOrderOfVisitGeneralGraph() {
		inizializza();
		for(int i =0 ; i<grafo.getOrder();i++)
			if(scoperti[i]==false)
				bfs(i);
		return risultato;
	}
	//NUMERO COMPONENTI CONNESSE IN UN GRAFO NON ORIENTATO
	public int getNumberOfConnectedComponents()
	{
		inizializza();
		int count =0;
		for(int i =0 ; i<grafo.getOrder();i++)
			if(scoperti[i]==false)
				{
					bfs(i);
					count++;
				}
		return count;
	}
	
	//BFS ORDINE TOPOLOGICO
	public ArrayList<Integer> getTopologicalOrder()
	{
		inizializza();
		ArrayList<Integer> ot = new ArrayList<Integer>();
		ArrayList<Integer> S=  new ArrayList<Integer>();
		
		S.add(7);
		S.add(5);
		S.add(2);
		
		System.out.println(grafo.getNeighbors(1));
		System.out.println("CODA INIZIALE: "+S.toString());

		while (!S.isEmpty())
		{
			int u =S.get(0);
			scoperti[u]=true;
			ot.add(u);
			S.remove(S.get(0));
			System.out.println("CODA: "+S.toString());
			for(int vicino : grafo.getNeighbors(u))
				if (scoperti[vicino]==false)
					{
						scoperti[vicino]=true;
						S.add(vicino);
					}
		}

		 
		return ot;
	}
}
