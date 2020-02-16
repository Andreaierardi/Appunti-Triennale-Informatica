package meteturistiche;

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
	
	
	public MeteTuristiche(UndirectedGraph mappa, int[] interesse)
	{
		g = mappa;
		inte=interesse;
	}
	private void init()
	{
		scoperti= new boolean [g.getOrder()];
		dist = new int [g.getOrder()];
		heap = new MinHeap<Edge,Integer>();
		for(int i =0 ;i<g.getOrder();i++)
		{
			scoperti[i]=false;
			dist[i]=-1;
		}
		ris = -1;
		
	}
	private void dijkstra(int s)
	{
		
		scoperti[s]=true;
		dist[s]=0;
		int interes = -1;

		if(s>=minD && s<=maxD)
		{
			interes = inte[s];
			ris = s;
		}
		for (Edge vicino: g.getIncidentEdges(s))
				heap.add(vicino,dist[s]+vicino.getWeight());
		while(!heap.isEmpty())
		{
			Edge e = heap.extractMin();
			int w=e.getHead();
			int u =e.getTail();
			

			if (scoperti[w]==false && dist[u]+e.getWeight()>=minD && dist[u]+e.getWeight()<=maxD)
			{
				scoperti[w]=true;
				dist[w]=dist[u]+e.getWeight();
				if(inte[w] > interes)
				{
					interes = inte[w];
					ris = w;
				}
						
				for(Edge arco:g.getIncidentEdges(w))
					{
						int z =arco.getHead();
						if(scoperti[z]==false && dist[w]+arco.getWeight()>=minD &&dist[w]+arco.getWeight()<= maxD )
								heap.add(arco, dist[w]+arco.getWeight());
							
					}
			}

		}

	}
	
	public int destinazioneConsigliata(int partenza, int minDistanza, int maxDistanza)
	{
		init();
		maxD=maxDistanza;
		minD=minDistanza;
		if(minD>maxD || partenza <0 || partenza>=g.getOrder())
			return -2;
		
		dijkstra(partenza);
	
		return ris;
	}
}
