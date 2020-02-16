package softwaresystem;

import java.util.ArrayList;

import it.uniupo.graphLib.*;

public class DFS {

	private boolean[] scoperti;
	private ArrayList<Integer> risultato;
	private GraphInterface grafo;
	private GraphInterface albero;
	private int[] padre;
	private boolean ciclo;
	
	public DFS(GraphInterface g)
	{

		this.grafo = g ;
		this.padre=new int[grafo.getOrder()];
		this.ciclo= false;
		this.scoperti= new boolean [grafo.getOrder()];
		this.risultato= new ArrayList<Integer>();


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

	private void dfsTree(int s)
	{
		scoperti[s] = true;
		this.risultato.add(s);
		for (int vicino : grafo.getNeighbors(s))
			{
				if(scoperti[vicino]==false)
				{
					albero.addEdge(s, vicino);
					dfsTree(vicino);
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
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		this.risultato= new ArrayList<Integer>();
		dfs(s);
	}
	//ALBERO DI VISITA
	public GraphInterface getTree(int s)
	{
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		albero = grafo.create();	
		dfsTree(s);
		return albero;
	}

	//ORDINE DI VISITA
	public	ArrayList<Integer> getNodesInOrderPostVisit(int s)	
	{
		ArrayList<Integer> terminati = new ArrayList<Integer>();
		
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		dfsFine(s,terminati);

		return terminati;
		
	}
	//FORESTA
	public GraphInterface getForest()
	{
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		albero = grafo.create();	
		for (int i =0 ; i<grafo.getOrder();i++)
			if(scoperti[i]==false)
				dfsTree(i);
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
	
	//GRAFO NON ORIENTATO CONNESSO 
	public boolean isConnected()
	{
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		dfs(0);
		for (int i=0 ;i< grafo.getOrder(); i++)
			if(scoperti[i]==false)
				return false;
		return true;
	}
	//COMPONENTI CONNESSE IN GRAFO NON ORIENTATO
	private void dfsComp(int u, int []CC,int count)
	{
		scoperti[u] = true;
		CC[u]=count;
		for (int vicino : grafo.getNeighbors(u))
			if(scoperti[vicino]==false)
				{
					dfsComp(vicino,CC,count);
				}
	}
	public int[] connectedComponents()
	{
		for (int i=0 ;i< grafo.getOrder(); i++)
			scoperti[i]=false;
		int[] CC = new int[grafo.getOrder()];
		int count = 0;

		for (int i = 0; i<grafo.getOrder(); i++)
			if(scoperti[i]==false)
			{
				dfsComp(i,CC,count);
				count++;
			}
		
		return CC;
		
	}
	
	//CICLO IN GRAFI NON ORIENTATI
	
	public boolean hasUndirectedCycle()
	{
		for(int i = 0; i<grafo.getOrder();i++)
		{
			this.padre[i]=-1;
			scoperti[i]=false;
		}
		this.ciclo= false;

		for(int i = 0; i<grafo.getOrder();i++)
			if(scoperti[i]==false)
				dfsCicle(i);
		return ciclo;
	}
	private void dfsCicle(int u)
	{
		scoperti[u]=true;
		for (int vicino : grafo.getNeighbors(u))
			{
				if (scoperti[vicino]==false)
				{
					this.padre[vicino]=u;
					dfsCicle(vicino);
				}
				else if(this.padre[u]!=vicino)
				{
					ciclo=true;
				}
			}
			
				
	}
	
}
