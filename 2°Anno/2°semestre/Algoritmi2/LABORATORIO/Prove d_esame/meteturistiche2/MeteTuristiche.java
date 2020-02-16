package meteturistiche;

import java.util.ArrayList;
import java.util.Arrays;

import it.uniupo.algoTools.MinHeap;
import it.uniupo.graphLib.*;

public class MeteTuristiche {

	private int[] inte;
	private UndirectedGraph g;
	
	private MinHeap<Edge,Integer> heap;
	private boolean[] scoperti;
	private int [] dist;

	private int ris;
	private int minD;
	private int maxD;
	private ArrayList<Integer> val;
	
	private ArrayList<Edge> coda;
	
	
	public MeteTuristiche(UndirectedGraph mappa, int[] interesse)
	{
		g = mappa;
		inte=interesse;
	}
	private void init()
	{
		scoperti= new boolean [g.getOrder()];
		coda = new ArrayList<Edge>();
		dist = new int [g.getOrder()];
		heap = new MinHeap<Edge,Integer>();
		val = new ArrayList<Integer>();
		for(int i =0 ;i<g.getOrder();i++)
		{
			scoperti[i]=false;
			dist[i]=-1;
		}
		ris = -1;
		
	}
	private void dijkstra(int s)
	{
		
		for(Edge vicino :g.getIncidentEdges(s))
		{ 
				if(vicino.getWeight()>=minD && vicino.getWeight()<=maxD)
					{
						coda.add(vicino);
						dist[vicino.getTail()]=0;
						if(s>=minD && s<= maxD)
							ris = s;
						else
							{
								System.out.println(vicino.getHead());
								ris = vicino.getTail();
							}
					}
				
		}
	
		while(!coda.isEmpty())
		{
			Edge e= coda.remove(0);
			int u = e.getTail();
			int v = e.getHead();
			System.out.println("Estraggo arco: ("+u+";"+v+")");
			System.out.println("RIS : "+ris);
			if(scoperti[v]==false && e.getWeight()>=minD && e.getWeight()<=maxD)
			{
				scoperti[v]=true;
				dist[v]=dist[u]+e.getWeight();
			//	if(inte[v]> inte[ris] && dist[v]>=minD&& dist[v]<=maxD)
				//	ris= v;
				for (Edge arco : g.getIncidentEdges(v))
				{	
					if(dist[v]+arco.getWeight()>=minD &&dist[v]+arco.getWeight()<= maxD)
					{
						int z = arco.getHead();
						if(this.scoperti[z]==false )
						{
							coda.add(arco);
							dist[z]=dist[v]+arco.getWeight();
						}
					}
					
						
				}
			}
			
		}
	}
	/*
	private void dijkstra(int s)
	{
		scoperti[s]=true;
		dist[s]=0;
		if ( dist[s]>= minD && dist[s]<=maxD)
			ris= s;
		for (Edge vicino: g.getIncidentEdges(s))
			if(vicino.getWeight()>= minD && vicino.getWeight()<=maxD)
						{heap.add(vicino,dist[s]+vicino.getWeight());
						 System.out.println(vicino.getTail()+";"+vicino.getHead());
						}
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
			int u =e.getTail();

			int w=e.getHead();
			
			System.out.println("PRendo arco: ("+u+","+w+")");
			if( inte[u]>inte[w] && dist[u]>= minD && dist[u]<=maxD)
				{
					ris = u;
					val.add(u);
					System.out.println("RIS trovato: "+ris+" -->"+inte[u]);
				}
			if( inte[w]>inte[u] && dist[u]+e.getWeight()>= minD && dist[u]+e.getWeight()<=maxD )
			{
				ris = w;
				val.add(u);
				System.out.println("RIS trovato: "+ris+" -->"+inte[u]);
			}
				
			if (scoperti[w]==false)
			{
				
				if(dist[u]+e.getWeight()>= minD && dist[u]+e.getWeight()<=maxD)
						{
							scoperti[w]=true;
							
							dist[w]=dist[u]+e.getWeight();
							for(Edge arco:g.getIncidentEdges(w))
							{
								int z =arco.getHead();
								if(scoperti[z]==false)
										heap.add(arco, dist[w]+arco.getWeight());
									
							}
						}
				
				
			}

		}
		
	}*/
	public int destinazioneConsigliata(int partenza, int minDistanza, int maxDistanza)
	{
		init();
		maxD=maxDistanza;
		minD=minDistanza;
		if(minD>maxD || partenza <0 || partenza>=g.getOrder())
			return -2;
		
		dijkstra(partenza);
		/*for (int i = 0;i<inte.length;i++)
		{
			if(inte[i]==ris)
				return i;
		}*/
		System.out.println(val.toString());
		return ris;
	}
}
