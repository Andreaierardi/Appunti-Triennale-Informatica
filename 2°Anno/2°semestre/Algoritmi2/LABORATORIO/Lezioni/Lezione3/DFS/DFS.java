package dfs;

import java.util.ArrayList;

import it.uniupo.graphLib.*;

public class DFS {

	private boolean[] scoperti;
	private ArrayList<Integer> risultato;
	private GraphInterface grafo;

	public DFS(GraphInterface g)
	{
		this.grafo = g ;
	}
	
	private void dfs(int s)
	{
		scoperti[s] = true;
		this.risultato.add(s);

		for (int vicino : grafo.getNeighbors(s))
			if(scoperti[vicino]==false)
				{
					dfs(vicino);
				}
	}

	private void dfsTree(int s,GraphInterface albero)
	{
		scoperti[s] = true;
		this.risultato.add(s);
		for (int vicino : grafo.getNeighbors(s))
			{
				if(scoperti[vicino]==false)
				{
					albero.addEdge(s, vicino);
					dfsTree(vicino,albero);
				}
			}
				
	}
	
	private void dfsFine(int s, ArrayList<Integer> terminazione)
	{
		scoperti[s] = true;
		for (int vicino : grafo.getNeighbors(s))
			if(scoperti[vicino]==false)
				
					dfsFine(vicino,terminazione);
			
		terminazione.add(s);
	}
	//VISITA GENERICA
	public void dfsVisit(int s)
	{
		scoperti= new boolean [grafo.getOrder()];
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		this.risultato= new ArrayList<Integer>();
		dfs(s);
	}
	//ALBERO DI VISITA
	public GraphInterface getTree(int s)
	{
		scoperti= new boolean [grafo.getOrder()];
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		this.risultato= new ArrayList<Integer>();
		GraphInterface albero = grafo.create();	
		dfsTree(s, albero);
		return albero;
	}

	//ORDINE DI VISITA
	public	ArrayList<Integer> getNodesInOrderPostVisit(int s)	
	{
		ArrayList<Integer> terminati = new ArrayList<Integer>();
		scoperti= new boolean [grafo.getOrder()];
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		dfsFine(s,terminati);

		return terminati;
		
	}
	//FORESTA
	public GraphInterface getForest()
	{
		scoperti= new boolean [grafo.getOrder()];
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		this.risultato= new ArrayList<Integer>();
		GraphInterface albero = grafo.create();	
		for (int i =0 ; i<grafo.getOrder();i++)
			if(scoperti[i]==false)
				dfsTree(i, albero);
		return albero;
	}
	
	//RISULTATO VISITA
	public ArrayList<Integer> getNodesInOrderOfVisit(int s)
	{
		dfsVisit(s);
		return this.risultato;
	}
	//ARRAY ORDINE DI VISITA
	public int[] getOrderOfVisit(int s) 
	{
		int [] ordine = new int [grafo.getOrder()];
		for (int x : this.getNodesInOrderOfVisit(s))
			ordine[x]=this.getNodesInOrderOfVisit(s).indexOf(x);
		return ordine;	
	}
	//ARRAY ORDINE DI POST VISITA
	public int[] getOrderPostVisit(int s)
	{
		int [] ordine = new int [grafo.getOrder()];
		for (int x : this.getNodesInOrderPostVisit(s))
			ordine[x]=this.getNodesInOrderPostVisit(s).indexOf(x);
		return ordine;	
	}
}
