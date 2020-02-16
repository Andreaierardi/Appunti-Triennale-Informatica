package  bacheca;
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
	public Utente(String nome, String email) throws FormatException
	{
		checkNome(nome);
		this.nome = nome;
		checkEmail(email);
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
	/**
	 * Controlla che la email inserita sia valida
	 * @param s La stringa da controllare
	 * @throws FormatException Lancia un'eccezione se l'email inserita non è corretta
	 */
	private void checkEmail(String s) throws FormatException
	{
		if(!(s.matches("[a-z[A-Z]]+@[a-z[A-Z]]+\\.[a-z]+")))
			throw new FormatException("Email scorretta");
	}
	/**
	 *Controlla che il nome inserito sia valida
	 * @param str La stringa da controllare
	 * @throws FormatException Lancia un'eccezione se il nonme inserito non è corretto
	 */
	private void checkNome(String str) throws FormatException
	{
		if(!(str.matches("[a-z[A-Z][0-9]]+")))
			throw new FormatException("Formato del nome non corretto");
	}
		

	
}
