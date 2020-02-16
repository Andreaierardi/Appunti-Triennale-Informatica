package softwaresystem;

import java.util.ArrayList;

import it.uniupo.graphLib.*;

public class SoftwareSystem {

	private GraphInterface g;
	private boolean scoperti[];
	private boolean ciclo;
	private ArrayList<Integer> terminati;
	private int[] padre;
	private ArrayList<Integer> dirCicle;
	
	public SoftwareSystem (DirectedGraph system)
	{
		this.g = system;
		this.terminati = new ArrayList<Integer>();
		this.scoperti=new boolean [g.getOrder()];
		this.dirCicle=new ArrayList<Integer>();
		this.padre= new int[g.getOrder()];
		this.ciclo =false;

	}
	
	private void dfs(int u)
	{
		scoperti[u]=true;
		for (int vicino : g.getNeighbors(u))
			{
				if (scoperti[vicino]==false)
				{
					dfs(vicino);
				}
				else if(!terminati.contains(vicino))
				{
					ciclo=true;
				}
			}
		this.terminati.add(u);
				
	}
	//VERIFICA CICLO
	public boolean hasCycle() 
	{
		
		for(int i = 0; i<g.getOrder();i++)
			scoperti[i]=false;
	

		for(int i = 0; i<g.getOrder();i++)
			if(scoperti[i]==false)
				dfs(i);
		
		return ciclo;
	}
	//OTTERE NODI CHE GENERANO CICLO
	private void dfs2(int u)
	{
		scoperti[u]=true;
		for (int vicino : g.getNeighbors(u))
			{
				if (scoperti[vicino]==false)
				{
					padre[vicino]=u;
					dfs2(vicino);
				}
				else if(!terminati.contains(vicino))
				{
					ciclo=true;
					dirCicle.add(vicino);
					dirCicle.add(u);
				}
			}
		this.terminati.add(u);
				
	}
	//dirCicle.add(vicino);
	//dirCicle.add(u);
	//padre[vicino]=u;
	public ArrayList<Integer> getDirCycle()
	{
		 for(int i = 0; i<g.getOrder();i++)
				{
			 		scoperti[i]=false;
			 		padre[i]=-1;
				}
		
		 dfs2(0);
		 int testa=this.dirCicle.get(0);
		 int coda =this.dirCicle.get(1);
		 while(coda!=testa)
		 {
			 dirCicle.add(padre[coda]);
			 coda=padre[coda];
		 }
		 dirCicle.remove(this.dirCicle.get(dirCicle.size()-1));
		 System.out.println(dirCicle);
		 return dirCicle;
	}
}
