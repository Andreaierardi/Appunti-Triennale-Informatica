package bellmanford;

import it.uniupo.graphLib.*;

public class BellmanFord {

	private int sorg;
	private DirectedGraph g;
	private DirectedGraph trasp;
	private Double sol[][];
	
	public BellmanFord(DirectedGraph	grafo,	int	sorgente)
	{
		g = grafo;
		trasp = it.uniupo.graphLib.GraphUtils.reverseGraph(g);
		sorg = sorgente;
	}
	
	private double getMin(int v, int i )
	{
		double min = Double.POSITIVE_INFINITY;
		

		for(Edge u : trasp.getIncidentEdges(v))
			if(u.getWeight()+sol[i-1][u.getHead()]< min)
				min = u.getWeight()+sol[i-1][u.getHead()];
		return min;
	}
	private void bellmanford()
	{
		sol = new Double[g.getOrder()][g.getOrder()];
		for (int i =0 ; i<g.getOrder(); i++)
			if(i!=sorg)
				sol[0][i]=Double.POSITIVE_INFINITY;
		sol[0][sorg] = (double) 0;

		for(int i = 1 ; i<g.getOrder();i++)
			for(int v = 0; v<g.getOrder();v++)
					sol[i][v]= Math.min(sol[i-1][v], getMin(v,i));
		
					
	}
	public	Double	getDist(int	u)	
	{
		bellmanford();
		for(int i = 0; i<g.getOrder();i++)
			{	System.out.println();
				for (int j= 0;j<g.getOrder();j++ )
					System.out.print(sol[i][j]+" ");
			}
		return sol[g.getOrder()-1][u];
	}
}
