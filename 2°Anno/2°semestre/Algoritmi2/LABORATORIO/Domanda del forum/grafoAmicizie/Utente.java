package  grafoAmicizie;
/**
 * @author      Andrea Ierardi 20018785@studenti.uniupo.it, Edoardo Favorido 20018971@studenti.uniupo.it
 * @version     1.0
 */
public class Utente {
	private final String nome;
	private String email;
	/**
	 * Inizializza un Utente
	 * @param nome Nome Utente
	 * @param email Email dell'Utente
	 * @throws FormatException Lancia un'eccezione se la email è nel formato sbagliato
	 */
	public Utente(String nome, String email) 
	{
		this.nome = nome;
		this.email = email;
	}
	
	/**
	 * Ritorna il nome dell'utente
	 * @return Ritorna il nome dell'utente
	 */
	public String getNome()
	{
		return this.nome;
	}
	/**
	 * Ritorna la email dell'utente
	 * @return Ritorna la email dell'utente
	 */
	public String getEmail()
	{
		return this.email;
	}
	
		

	
}
