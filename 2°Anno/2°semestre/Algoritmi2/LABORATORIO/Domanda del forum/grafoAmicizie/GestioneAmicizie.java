package grafoAmicizie;

import java.util.ArrayList;
import java.util.HashMap;

import it.uniupo.algo2.grafi.*;
public class GestioneAmicizie{
	
	private static HashMap<String, Integer> listaUtenti =new HashMap<String, Integer>();
	private static ArrayList<String> nomiUtenti = new ArrayList<String>();
	private static UndirectedGraph grafo= new UndirectedGraph(5);
//Metodo per la creazione di una rubrica	
	public static int crea(String nome, int nodo)
	{
		if (listaUtenti.containsKey(nome)) return -1;
		grafo = new UndirectedGraph(nodo);
		listaUtenti.put(nome,nodo);
		nomiUtenti.add(nome);
		return 1;
	}

	public static void addFriendship(String utente1, String utente2) {
		
		
		if (listaUtenti.containsKey(utente1)&& listaUtenti.containsKey(utente2))
		{
			int nodo1 = listaUtenti.get(utente1);
			int nodo2 = listaUtenti.get(utente2);
			grafo.addEdge(nodo1,nodo2);
		}
	}
	
	public static ArrayList<String> getFriends(String utente3) //che si deve basare su getNeighbors
	{
		ArrayList<String> neightbors = new ArrayList<String>();

		if (listaUtenti.containsKey(utente3))
				{
					int nodo = listaUtenti.get(utente3);
					ArrayList<Integer> nearestNodes = (ArrayList<Integer>) grafo.getNeighbors(nodo);	
					for (int tmp : nearestNodes)
						for (String nomi : nomiUtenti)
							if (listaUtenti.get(nomi).equals(tmp))
								neightbors.add(nomi);
						
							
				}	
		return neightbors;
		
		
	}
//Metodo per l'aggiunta di un contatto in una rubrica
	


//Metodo per la ricerca di contatti in rubrica
/*public static ArrayList<String> cerca(String nome, String contatto)
	{
		if( listaUtenti.get(nome).cerca(contatto).isEmpty())
		{
			return null;
		}
		
		else
		{
			return  listaUtenti.get(nome).cerca(contatto);
		}
			
	}*/
	
//Metodo per trasformare una rubrica in stringa
	public static String instringa()
	{
		return listaUtenti.toString();
	}
	
	public static boolean hasEdge(int u , int v)
	{
		return grafo.hasEdge(u, v);
	}
//Metodo per risettare la rubrica
	public static void reset()
	{
		listaUtenti =new HashMap<String, Integer>();
	}

	
		

}
