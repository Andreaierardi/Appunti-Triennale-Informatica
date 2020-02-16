package bacheca;

import java.util.ArrayList;

/**
 * @author      Andrea Ierardi 20018785@studenti.uniupo.it, Edoardo Favorido 20018971@studenti.uniupo.it
 * @version     1.0
 */
public class Annunci {

	private String nomeOggetto;
	private Utente utente;
	private int quantita;
	private int prezzo;
	private ArrayList<String> paroleChiave;
	private int ID;
	private char type; 

	/**
	 * Inizializza un annuncio
	 * @param T Il tipo di annuncio
	 * @param nomeOggetto Il nome dell'oggetto dell'annuncio
	 * @param u L'utente che ha creato l'annuncio
	 * @param qnt Il numero di oggetti dell'annuncio
	 * @param prezzo Il prezzo dell'oggetto
	 * @param ID L'identificatore dell'annuncio
	 * @param paroleChiave Le parole chiave dell'annuncio
	 * @throws FormatException Lancia un'eccezione se il tipo dell'annuncio inserito non è esistente oppure se l'id inserito è minore di zero
	 */
	public Annunci(char T, String nomeOggetto, Utente u, int qnt, int prezzo, int ID, String... paroleChiave) throws FormatException {

		checkType(T);
		this.type = T;
		this.nomeOggetto = nomeOggetto;
		this.utente = u;
		this.quantita = qnt;
		this.prezzo = prezzo;
		checkID(ID);
		this.ID = ID;
		this.paroleChiave = new ArrayList<String>();
		for (String parola : paroleChiave)
			this.paroleChiave.add(parola);
	}
	/**
	 * Ritorna il tipo di annuncio
	 * @return Ritorna il tipo di annuncio
	 */
	public char getT() {
		return type;
	}
	
	/**
	 * Ritorna le parole chiave dell'annuncio
	 * @return Ritorna le parole chiave dell'annuncio
	 */
	public ArrayList<String> getParoleChiave() {
		return paroleChiave;
	}

	/**
	 * Ritorna l'ID dell'annuncio
	 * @return Ritorna l'ID dell'annuncio
	 */
	public int getID() {
		return this.ID;
	}
	
	/**
	 * Ritorna il nome dell'oggetto
	 * @return Ritorna il nome dell'oggetto
	 */
	public String getNome() {
		return this.nomeOggetto;
	}
	/**
	 * Ritorna il nome dell'utente
	 * @return Ritorna il nome dell'utente
	 */
	public String getNomeUtente() {
		return this.utente.getNome();
	}

	/**
	 * Fa il set della lista delle parole chiave
	 * @param match Fa il set della lista delle parole chiave
	 */
	public void setParoleChiave(ArrayList<String> match) {
		this.paroleChiave = match;
	}
	/**
	 * Trasforma la lista delle parole chiave in stringa separando ciascuna parola con un '-'
	 * @return Ritorna tutte le parole chiave dell'annuncio separate da un '-'
	 */
	public String listaParole() {
		String s = new String ();
		for(String tmp :this.paroleChiave)
			s+=tmp+"-";
		return s.substring(0, s.length()-1);
			
	}
	/**
	 *   Trasforma l'annuncio in stringa
	 */
	@Override
	public String toString() {
		return ( type+","+nomeOggetto+","+utente.getNome()+","+utente.getEmail()+","+quantita+","+prezzo+","+ID+","+this.listaParole());
	}
	/**
	 * Controlla che l'identificatore non sia minore di 0
	 * @param ID L'identificatore da controllare
	 * @throws FormatException Lancia un'eccezione se l'identificatore è minore di 0
	 */
	private void checkID(int ID) throws FormatException
	{
		if(ID<0)
			throw new FormatException("Errore inserimento ID");
	}
	/**
	 * Controlla che l'annuncio sia di tipo C (Compro) o V (Vendo)
	 * @param t Il tipo dell'annuncio da controllare
	 * @throws FormatException Lancia un'eccezione se il tipo dell'annuncio non è uguale al carattere C o al carattere V
	 */
	private void checkType(char t) throws FormatException
	{
		if(!((t=='C')||(t=='V')))
			throw new FormatException("Errore inserimento tipo di annuncio");
	}
}
