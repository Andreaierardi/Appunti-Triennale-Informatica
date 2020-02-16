package webquality;

import java.util.ArrayList;
import java.util.Arrays;

import it.uniupo.graphLib.*;

public class WebQuality {

	private ArrayList<Integer> coda;
	private boolean[]scoperti;
	private int[] dist;
	private int sorg;
	private DirectedGraph g;
	
	public WebQuality(DirectedGraph site, int home)
	{
		g = site;
		sorg = home;
	}
	private void init()
	{
		coda = new ArrayList<Integer>();
		scoperti= new boolean[g.getOrder()];
		dist= new int [g.getOrder()];
		for (int i=0; i<g.getOrder();i++)
		{
			dist[i]=-1;
			scoperti[i]=false;
		}
		
	}
	private void bfs(int s)
	{
		scoperti[s]=true;
		dist[s]=0;
		coda.add(s);
		
		while(!coda.isEmpty())
		{
			int u = coda.remove(0);
			scoperti[u]=true;
			for(int v : g.getNeighbors(u))
				if(scoperti[v]==false)
				{
					coda.add(v);
					scoperti[v]=true;
					dist[v]=dist[u]+1;
					
				}
		}
	}
	
	public int depth(int dest)
	{
		init();
		bfs(sorg);
		if(dest == sorg)
		{
			Arrays.sort(dist);
			return dist[dist.length-1];
		}		
		return dist[dest];
	}
}
