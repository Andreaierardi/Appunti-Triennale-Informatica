package partita;

import java.util.ArrayList;

import it.uniupo.graphLib.*;

public class Partita {

	//Campi utili per poter utilizzare i parametri delle funzioni all'interno della classe
	private DirectedGraph g;
	//Array delle configurazioni vincenti
	private int[] vinc ;
	//Utile per ritornare il risultato del metodo
	private int win;
	
	//Campi per poter implementare l'algoritmo BFS
	private ArrayList<Integer> coda;
	private boolean[] scoperti;
	private int[] dist;
	
	//Costruttore della classe
	public Partita(DirectedGraph gioco, int[] confVincenti)
	{
		g = gioco;
		vinc = confVincenti;
	}
	//Inizializzazione delle strutture dati e delle variabili
	private void init()
	{
		coda = new ArrayList<Integer>();
		scoperti = new boolean [g.getOrder()];
		dist = new int [g.getOrder()];
		//win inizializzata a -1 in modo da poter restituire -1 in caso di nessuna configurazione vincente
		win =-1;
		for (int i = 0; i<g.getOrder(); i++)
		{
			scoperti[i]=false;
			dist[i]=-1;
		}
	}
	
	//L'algoritmo utilizzato è quello BFS poichè permette appunto la visita del grafo in ampiezza ed è ciò che ci serve per verificare le configurazioni vincenti dei vicini di un nodo
	//Inoltre si parla di configurazione vincente piu' vicina quindi c'è bisogno dei cammini minimi di un grafo non pesato e l'unico algoritmo è quello della BFS
	
	//L'algoritmo viene cambiato aggiungendo dei controlli sulla situazione delle configurazioni vincenti
	//In caso il nodo che si sta visitando(quindi il nodo v) abbia una configurazione vincente allora assegnamo il valore a win e ritorniamo visto che saremo sicuri di aver trovato il nodo con la configurazione vincente piu' vicina perchè l'abbiamo visitato per primo
	//In caso il nodo v non abbia una configurazione vincente allora si andrà piu' in profondità a verificare se i nodi vicini di v(ovvero i nodi u) presentano configurazioni vincenti
	private void bfs (int s)
	{
		scoperti[s]=true;
		dist[s]=0;
		coda.add(s);
		while(!coda.isEmpty())
		{
			int old =0;

			int v = coda.remove(0);
			scoperti[v]=true;
			//Nodo appena visitato ed estratto dalla coda. Se ha una configurazione vincente allora assegnamo il valore win e ritorniamo poichè siamo sicuri che non vi siano vicini con altre configurazioni. 
			//Ne siamo certi poichè abbiamo aggiunto un controllo anche sui nodi vicini di v.
			if(vinc[v]!=-1)
			{
				win= vinc[v];
				return; //La return serve per interrompere l'algoritmo ed evitare che i valori visitando tutto il grafo possano cambiare
			}
			for(int u: g.getNeighbors(v))
			{
					if(scoperti[u]==false)
					{
						
						//Grazie a questo controllo verifichiamo che tra tutti i vicini di v vi siano piu' configurazioni vincenti
						//Infatti la configurazione vincente 'vecchia' viene salvata nella variabile old e se la configurazione presente(vinc[u]) è diversa da quella vecchia(vinc[old]) significa che abbiamo piu' configurazioni vincenti tra i vicini di v e possiamo ritornare -1
						
						//Viene anche controllato che vinc[u] sia diversa da -1 e anche vinc[old] per verificare che entrambe siano configurazioni vincenti
						if(vinc[u]!=-1 && vinc[u]!=vinc[old] && vinc[old]!=-1)
						{
								win=-1; 
								return;
						}
						scoperti[u]=true;
						coda.add(u);
						//Se vinc[u] è una configurazione vincente la salviamo in old
						if(vinc[u]!=-1)
							old=u;
					}
				
			}
			
		}
		
	}
	//Metodo richiesto dalla consegna
	public int winner(int conf)
	{
		//Inizializzazione strutture dati e variabili utili
		init();
		//Lancio dell'algoritmo
		bfs(conf);
		//Ritorno la variabile win modificata dall'algoritmo(se si ha incotrato una configurazione vincente)
		return win;
	}
	
}
