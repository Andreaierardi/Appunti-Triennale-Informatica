package kosaraju;

import java.util.ArrayList;
import java.util.Collections;

import it.uniupo.graphLib.*;

public class Kosaraju {
	private boolean[] scoperti;
	private ArrayList<Integer> terminati;
	private DirectedGraph g;
	private int CC[] ;
	private int contaCC;
	private boolean ciclo;
	
	public Kosaraju(DirectedGraph grafo)
	{
		this.g = grafo ;
		inizializza();
	}
	
	private void dfs(int s)
	{
		scoperti[s] = true;
		CC[s]=contaCC;
		for (int vicino : g.getNeighbors(s))
			if(scoperti[vicino]==false)
					dfs(vicino);
			else if(!terminati.contains(vicino))
				ciclo= true; 
		this.terminati.add(s);

	}
	
	private void inizializza()
	{		
		this.CC = new int [g.getOrder()];
		this.ciclo=false;
		this.contaCC = 0;
		this.scoperti = new boolean[g.getOrder()];
		for (int i = 0 ; i< g.getOrder(); i++)
			scoperti[i]=false;
		this.terminati = new ArrayList<Integer>();
		
	}
	

	//ORDINE TOPOLOGICO
	public	ArrayList<Integer>	topologicalOrder()
	{
		inizializza();
		for (int i = 0 ; i<g.getOrder();i++)
			if(scoperti[i]==false)
				dfs(i);
		Collections.reverse(terminati);
		return terminati;
	}
	//ALGORITMO DI KOSARAJU

	public ArrayList<Integer> orderOfSecondVisit()
	{
		inizializza();
		for (int i = 0 ; i<g.getOrder();i++)
			if(scoperti[i]==false)
				dfs(i);
		Collections.reverse(terminati);
		return terminati;
	}
	private static DirectedGraph reverseGraph(DirectedGraph graph) 
	{
		return GraphUtils.reverseGraph(graph);
	}
	
	public int[] getSCC()
	{
		inizializza();
		for(int i = 0 ; i<g.getOrder(); i++)
			if(scoperti[i]==false)
				{
					dfs(i);
					this.contaCC++;
				}	
		return CC;
	}
	
	//ORDINE TOPOLOGICO+ VERIFICA DAG
		public	ArrayList<Integer>	DAGtopologicalOrder()
		{
			inizializza();
			for (int i = 0 ; i<g.getOrder();i++)
				if(scoperti[i]==false)
					dfs(i);
			if (ciclo==true)
				throw new IllegalArgumentException();
			Collections.reverse(terminati);
			return terminati;
		}
		
	//VERIFICA SCC SIANO LE STESSE DI UN GRAFO TRASPOSTO
	public boolean sameSCC()
	{
		int [] comp1=getSCC();
		this.g= GraphUtils.reverseGraph(g);	
		int [] comp2=getSCC();

		for(int i =0 ; i<g.getOrder();i++)
			{
			System.out.println(comp1[i]+" -- "+comp2[i]);
				/*if(comp1[i]!=comp2[i])
					return false;*/

			}

		return true;
	}
}
