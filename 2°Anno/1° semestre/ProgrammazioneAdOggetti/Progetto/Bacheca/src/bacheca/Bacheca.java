package bacheca;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * @author      Andrea Ierardi 20018785@studenti.uniupo.it, Edoardo Favorido 20018971@studenti.uniupo.it
 * @version     1.0
 */
public class Bacheca implements Iterable<Annunci> {
	private ArrayList<Annunci> annunci;
	final int MAX_DIM=3;

	protected static ArrayList<String> parole = new ArrayList<String>();
	static{
		parole.add("Abbigliamento");
		parole.add("Alimentari");
		parole.add("Altro");
		parole.add("Arredamento");
		parole.add("Auto");
		parole.add("Bellezza");
		parole.add("Casa");
		parole.add("Elettronica");
		parole.add("Film");
		parole.add("Giardinaggio");
		parole.add("Giochi");
		parole.add("Gioielli");
		parole.add("Informatica");
		parole.add("Libri");
		parole.add("Moto");
		parole.add("Musica");
		parole.add("Telefonia");
		parole.add("Sport");
		parole.add("Videogiochi");

	}
	
	public Iterator<Annunci> iterator()
	{
		return new IteratoreBacheca();
	}
	
	private class IteratoreBacheca implements Iterator<Annunci>
	{
		private int cursor;

		public IteratoreBacheca()
		{
			cursor = 0;
		}

		public boolean hasNext()
		{
			if (annunci.size()>MAX_DIM) return false;
			return (cursor<annunci.size());
		}
		public Annunci next()
		{
			if (!this.hasNext())
				return null;
			return annunci.get(cursor++);
		}

	}
	/**
	 * Inizializza la bacheca
	 */
	public Bacheca() 
	{
		this.annunci = new ArrayList<Annunci>();
	}
	
	/**
	 * Aggiunge un annuncio alla bacheca
	 * @param annuncio Annuncio da aggiungere in bacheca
	 * @throws FormatException Lancia un'eccezione se l'utente non è presente, se l'annuncio è già presente, se non trova nessuna corrispondenza nelle parole chiave e se raggiunge la dimensione massima
	 */
	public void aggiungiAnnuncio(Annunci annuncio)throws FormatException
	{

		ArrayList<String> match  = new ArrayList<String>();
		if(!(Utenti.contains(annuncio.getNomeUtente())))
			throw new FormatException("Utente non presente");
			
		
		for (Annunci tmp : this.annunci)
		{
			if (annuncio.getID() == tmp.getID())
				throw new FormatException("Annuncio gia presente");
		}
		for(String s: parole)
		{
			if(annuncio.getParoleChiave().contains(s))
			{
				match.add(s);
			}
		}

		if(match.size()==0)
		{
			throw new FormatException("Nessuna corrispondenza nelle parole chiave");

		}
		else
		{
			if (this.annunci.size()>=MAX_DIM) {
				throw new FormatException("Dimensione massima raggiunta");
			}
			annuncio.setParoleChiave(match);
			this.annunci.add(annuncio);

		}

	}
	/**
	 * Trasforma la lista delle parole chiave in stringa
	 * @return Ritorna la lista delle parole chiave in stringa separate da un '-'
	 */
	public String paroleChiaveString() 
	{
		String s = new String();
		for (String tmp : parole)
			s+=tmp+"-";
		return s.substring(0,s.length()-1);
	}

	/**
	 * Ritorna una lista di annunci di un utente
	 * @param u L'utente da cui prelevare gli annunci
	 * @return Ritorna una lista di annunci di un utente
	 */
	public ArrayList<Annunci> trovaAnnunci(Utente u) 
	{
		ArrayList<Annunci> risultato = new ArrayList<Annunci>();
		for (Annunci tmp : this.annunci)
			if (tmp.getNomeUtente().equals(u.getNome()))
				risultato.add(tmp);
		return risultato;

	}
	/**
	 * Trasforma una lista degli annunci di un determinato utente sotto forma di stringa
	 * @param u Utente a cui appartengono gli annunci
	 * @return Ritorna una lista degli annunci di un determinato utente sotto forma di stringa
	 */
	public String listaPropriAnnunci(Utente u)
	{
		ArrayList <Annunci> lista = trovaAnnunci(u);
		String s = new String();
		for (Annunci tmp : lista)
		{
			s+= tmp.toString()+("\n");
		}
		return s.substring(0, s.length()-1);
	}

	/**
	 * Elimina un annuncio dalla bacheca
	 * @param identificatore L'identificatore dell'annuncio da eliminare
	 * @param u L'utente serve per verificare che l'utente sia il proprietario dell'annuncio
	 * @throws FormatException Lancia un'eccezione se non viene trovato nessun annuncio con quell'identificatore
	 */
	public void rimuoviAnnuncio(int identificatore, Utente u) throws FormatException 
	{
		for(int i=0;i<annunci.size();i++){
			Annunci c=annunci.get(i);
			if(c.getID()==identificatore && u.getNome()==c.getNomeUtente()){
				annunci.remove(c);
				return;
			}
		}
		throw new FormatException("Nessun annuncio trovato");
	}
	/**
	 * Trasforma un annuncio ricercato in stringa
	 * @param id_cercato L'identificatore dell'annuncio da cercare
	 * @return Ritorna l'annuncio ricercato sotto forma di stringa
	 */ 
	public String visualizzaAnnuncio(int id_cercato)
	{
		for (Annunci c : this.annunci) {
			if (c.getID() == id_cercato) {
				return c.toString();
			}
		}
		return "";

	}

	/**
	 * Trasforma tutti gli annunci della bacheca in stringa
	 * @return Ritorna la lista di annunci della bacheca sottoforma di stringa
	 */
	public String elencoAnnunci()
	{//testo iteratore qua
		String s = new String();
		for(Annunci tmp : annunci)
			s += tmp.toString()+"\n";
		return s.substring(0, s.length()-1);
	}
	
	/**
	 * Genera tutti gli ID degli annunci in cui si vende un oggetto che ha intersezione non vuota con un sottoinsieme delle parole chiave
	 * @param s Il sottoinsieme di parole chiave
	 * @return Ritorna una lista di ID degli annunci in cui si vende un oggetto che ha intersezione non vuota con un sottoinsieme delle parole chiave
	 */
	public ArrayList<Integer> intersezione(String ... s)
	{
		ArrayList<Integer> array = new ArrayList<Integer>();
		for(Annunci p:this.annunci){
			for(String c: p.getParoleChiave()){
				for(String z:s){
					if(!array.contains(p.getID())){
						if (c.equals(z))
							array.add(p.getID());
					}
				}
			}
		}

		return array;
	}
	/**
	 * Per importare gli annunci da un file di testo
	 * @param nomeFile Il nome del file da cui importare gli annunci
	 * @throws IOException Lancia un'eccezione se il file non viene trovato o c'è un errore nella lettura del file
	 * @throws FormatException Lancia un'eccezione se l'aggiunta di un annuncio non avviene con successo
	 */
	public	void leggiBacheca(String nomeFile) throws FormatException, IOException
	{
		
			BufferedReader in = new BufferedReader(new FileReader(nomeFile));
			String linea = in.readLine();
			String[] dati = linea.split(",");
			
			while (linea != null) {
				dati = linea.split(",");
				if (dati.length >= 7) {

					char T = dati[0].charAt(0);
					String nomeOgg = dati[1].trim();
					String nomeU= dati[2].trim();
					String emailU= dati[3].trim();
					int  qnt = Integer.parseInt(dati[4]);
					int  prezzo= Integer.parseInt(dati[5]);
					int  ID = Integer.parseInt(dati[6]);
					String [] parCh = dati[7].split("-");
					Utente u = new Utente(nomeU,emailU);
					if (!(Utenti.contains(u.getNome())))
						Utenti.aggiungiUtente(u);
					this.aggiungiAnnuncio(new Annunci(T,nomeOgg,u, qnt, prezzo,ID, parCh));
					
				}
				linea = in.readLine();
			}
			in.close();
		
	}
	/**
	 * Salva sul file dato in input gli annunci salvati in bacheca convertiti in stringa
	 * @param nomeFile Il nome del file su cui scrivere gli annunci
	 * @throws FileNotFoundException Lancia un'eccezione se il nome del file è in un formato non corretto
	 */
	public void scriviBacheca(String nomeFile) throws FileNotFoundException  {

			PrintWriter out = new PrintWriter(new File(nomeFile));
			out.printf(this.elencoAnnunci());
			out.close();
		
	}
	/**
	 * Ritorna il numero di annunci in bacheca
	 * @return Ritorna il numero di annunci in bacheca
	 */
	public int numEl(){
		return this.annunci.size();
	}

}

