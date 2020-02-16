
package game;

import java.util.ArrayList;

import it.uniupo.graphLib.*;

public class Game {
	
	//Campi utili per poter utilizzare i parametri delle funzioni all'interno della classe
	private DirectedGraph g;
	private int [] vinc;
	private int p;
	private int max;
	private int numPlayers;
	private boolean vittoria;
	
	//Campi per implementare l'algoritmo BFS
	private ArrayList<Integer> coda;
	private boolean[] scoperti;
	private int[] dist;
	
	public Game(DirectedGraph gioco, int[] confVincenti)
	{
		g = gioco;
		vinc = confVincenti;
	}
	
	private void init()
	{
		coda = new ArrayList<Integer>();
		scoperti = new boolean [g.getOrder()];
		dist = new int [g.getOrder()];
		vittoria = false;
		numPlayers = 0;
		for (int i = 0; i<g.getOrder(); i++)
		{
			scoperti[i]=false;
			dist[i]=-1;
			if(vinc[i]> numPlayers)
				numPlayers=vinc[i];
		}
		
	}
	private void bfs(int sorg)
	{
		coda.add(sorg);
		scoperti[sorg]=true;
		dist[sorg]= 0;
		while(!coda.isEmpty())
		{
			int v = coda.remove(0);
			scoperti[v]=true;
			if(vinc[v]==p && dist[v]<=max)
				vittoria = true;
			
			for(int i : g.getNeighbors(v))
				if(scoperti[i]==false)
				{
					scoperti[i]=true;
					coda.add(i);
					dist[i]=dist[v]+1;
				}
		}
	
			
	}
	public int wins(int conf, int player, int maxMoves)
	{
		p = player;
		max = maxMoves; 
		init();
		if(p>numPlayers ||p<=0|| max<0 || conf<0 ||conf>=g.getOrder())
			return -1;
		
		bfs(conf);
		if(vittoria)
			return 1;
		return 0;
	}
}
