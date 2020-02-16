package main;

public class gestore_appelli {
	

	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari

  static DB_utenti db;
  static DB_appelli da;
  static DB_corsi dc;
	  
  // Costruttore per gestore appelli
  
  public gestore_appelli(DB_utenti d1, DB_appelli d2 , DB_corsi d3)
  {
	  db = d1;
	  da = d2;
	  dc = d3;
  }
	  
  // Verifica che il corso di laurea esista e corrisponda al corso di laurea e all'anno della matricola inserita.
  // Se esiste ritorna true altrimenti false
  public static boolean verifica_corso_laurea(int matricola, int codice_corso)
  {
	  utente s= DB_utenti.ricerca_dati_utente(matricola);
	  corso c= DB_corsi.ricerca_dati_corso(codice_corso);
	  
	  /*Test prototipo 
	   * if(s == null)
		  System.out.println("Utente non trovato");
	  if(c==null)
		  System.out.println("Codice corso non trovato");
		
		*/
	  if(s != null && c != null)
		  {
		  	//Se i dati passati in input coincidono con quelli nei due database
		    // si confrontano i campi CdL e anno dei due oggetti ritornati
		  	if(s.CdL.equals(c.cdl)  && s.anno == c.anno)
				  return true;

		  }
		return false;	
  }
	  
  //Verifica che il voto esiste per una determinata matricola e il codice appello
  //e ritorna l'oggetto voto
  public static voto verifica_esistenza_voto(int matricola, String  codice_appello)
  {
	  return DB_appelli.ricerca_voto(matricola,codice_appello);
  }
  
  // Aggiorna lo stato del voto, accettato o rifiutato quindi o true o false
  public void richiesta_update_voto(voto voto, String risposta)
  {
	  DB_appelli.aggiorna_voto(voto,risposta);
  }
  
}



