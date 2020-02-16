package test;
import main.*;
import static org.junit.Assert.*;
import org.junit.Test;
public class Test_DB_utenti 
{



	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari
	
	@Test
	public void test_ricerca_account_1() 
	{
		//matricola errata - return null"
		assertEquals(null, DB_utenti.ricerca_dati_utente(9999));
	}

	@Test
	public void test_ricerca_account_2() 
	{
		//matricola esatta - return di studente con username corretto
		String user = "20021037";

		assertEquals(user, DB_utenti.ricerca_dati_utente(20021037).username);
	}

	@Test
	public void test_ricerca_account_3() 
	{
		//matricola esatta - return di studente con cognome corretto
		String user = "Famiani";

		assertEquals(user, DB_utenti.ricerca_dati_utente(20018222).cognome);
	}

		
}

