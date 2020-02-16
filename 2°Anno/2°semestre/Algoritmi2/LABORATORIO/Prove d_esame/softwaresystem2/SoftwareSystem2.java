package softwaresystem2;

import java.util.ArrayList;

import it.uniupo.graphLib.*;

public class SoftwareSystem2 {

	//Inizializzo tutti i campi
	//Grafo per poter utilizzare i metodi dei grafi nella classe
	private DirectedGraph g;
	
	//Array degli scoperti per tenere conto dei nodi scoperti in visita
	private boolean [] scoperti;
	
	//Array dei terminati per verificare se vi è un ciclo
	private ArrayList<Integer> terminati;
	//Boolean per dirci se durante la visita è stato trovato il nodo s2(o s1)
	private boolean trovato;
	//Boolean per dirci se ha trovato o no il ciclo
	private boolean ciclo;
	
	//inizializzo la classe
	public SoftwareSystem2(DirectedGraph system)
	{
		g = system;
	}
	
	//metodo per l'inizializzazione di tutti i campi
	private void init()
	{
		scoperti = new boolean[g.getOrder()];
		terminati = new ArrayList<Integer>();
		ciclo = false;
		trovato = false;
	}
	//Metodo della dfs. In questo caso la verifica del ciclo ci fa venire in mente subito l'utilizzo della DFS.
	//Oppure anche solo per verificare le componenti (Se trovo il nodo in una componente significa che uno dipende dall'altro)
	private void dfs(int s,int dest)
	{
		scoperti[s]= true;
		if(s==dest) //Verifico se il nodo visitato è quello trovato
			trovato = true;
		for (int vicino: g.getNeighbors(s))
			{
				if(scoperti[vicino]==false)
					dfs(vicino,dest);
				if(!terminati.contains(vicino))//Se il nodo non ha ancora terminato c'è un ciclo
					ciclo = true;	
			}
				
		terminati.add(s); //Aggiungo a lista dei terminati
	}
	
	//Funzione richiesta dalla consegna
	public int depends(int s1, int s2) 
	{
		init(); //inizializzo i campi
		
		//-1 se s1 o s2 non sono componenti del sistema
		//Quindi se non esistono quei due nodi
		if(s1>=g.getOrder()||s1<0||s2>= g.getOrder()|| s2<0)
			return -1;
		
		//-2 se s1 = s2(e s1 ed s2 sono componenti del sistema)
		if(s1 ==s2) 
			return-2;
		
		//Avvio visita bfs 
		dfs(s1,s2);
		//Se trovo un ciclo ritorno subito -3
		if(ciclo == true)
			return -3;
		
		//Se trovo che s2 lungo il percorso, allora ritorno 2
		if(trovato==true)
			return 2;
	
		//Resetto e faccio la visita al contrario per verificare se trovo s1 nel percorso
		init();
		dfs(s2,s1);
		//Se trovo s2 nel percorso allora ritorno 1
		if(trovato == true)
			return 1;
	
		//Se non trovo nè s1 nè s2 allora ritorno 0.
		return 0;
	}
	
}
