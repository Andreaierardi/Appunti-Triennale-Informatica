package bacheca;
/**
 * @author      Andrea Ierardi 20018785@studenti.uniupo.it, Edoardo Favorido 20018971@studenti.uniupo.it
 * @version     1.0
 */
import java.util.ArrayList;

public class Utenti {
	private static ArrayList<Utente> utenti=new ArrayList<Utente>();
	/**
	 * Inizializza l'ArrayList di utenti
	 */
	public static void crea() 
	{
		utenti=new ArrayList<Utente>();
	}
	/**
	 * Aggiunge un utente nell'ArrayList di utenti
	 * @param u Utente da aggiungere
	 * @throws FormatException Lancia un'eccezione se l'utente è già presente
	 */
	public static void aggiungiUtente(Utente u)  throws FormatException{
	
		for (Utente tmp : utenti)
			if (tmp.getNome().equals(u.getNome()))
					 throw new FormatException("Utente gia presente");
		Utente p=new Utente(u.getNome(),u.getEmail());
		utenti.add(p);
	}
/**
 * Rimuove un utente dall'ArrayList di utenti
 * @param nome Nome utente da rimuovere
 * @throws FormatException Lancia un'eccezione se l'utente non è presente nell'ArrayList di utenti
 */
	public static void RimuoviUtente(String nome) throws FormatException{

		for(int i=0;i<utenti.size();i++){
			Utente u= utenti.get(i);
			
			if(u.getNome().equals(nome))
			{
				utenti.remove(u);
				return;
				 
			}
		}
	
		throw new FormatException("Utente non presente, impossibile rimuovere");
	}
	/**
	 * Trasforma l'ArrayList di utenti in stringa
	 * @return Ritorna l'ArrayList di utenti sotto forma di stringa
	 */
	public static String elencoUtenti()
	{
		String elenco = new String();
		for (Utente tmp : utenti)
			elenco+= tmp.getNome() +"\n";
		return elenco;
			
	}
	/**
	 * Verifica che il nome passato in input sia presente nell'ArrayList di utenti
	 * @param nome Stringa nome da verificare
	 * @return Restituisce True se il nome è presente nell'ArrayList altrimenti restituisce True
	 */
	public static boolean contains(String nome)
	{
		for (Utente u : utenti)
			if(u.getNome().equals(nome))
				return true;
		return false;
	}
	/**
	 * Restituisce il numero di utenti presente nell'ArrayList di utenti
	 * @return Restituisce il numero di utenti presente nell'ArrayList di utenti
	 */
	public static int numEl() {
		return utenti.size();
	}
	/**
	 * Dato in input il nome di un'utente restituisce l'utente stesso
	 * @param nome Nome dell'utente da ricercare
	 * @return L'utente con il nome ricerca
	 * @throws FormatException Lancia un'eccezione se l'utente non è stato trovato
	 */
	public static Utente getUtente(String nome) throws FormatException
	{
		for (Utente u : utenti)
			if (u.getNome().equals(nome))
				return u;
		throw new FormatException("Utente non trovato");
	}

}

