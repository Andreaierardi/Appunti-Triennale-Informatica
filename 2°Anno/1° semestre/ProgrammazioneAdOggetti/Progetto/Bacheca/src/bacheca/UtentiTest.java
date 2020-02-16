package bacheca;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

public class UtentiTest {
	@Before
	public void creazione() {
		Utenti.crea();
	}
	
	@Rule
	public ExpectedException eccezione= ExpectedException.none();
	@Test
	public void testAggiungi() throws FormatException {
		Utente u1=new Utente("Gianni","gianni@hotmail.it");
		Utenti.aggiungiUtente(u1);
		Utente u2=new Utente("Gianni","gianni@hotmail.it");
		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Utente gia presente");
		Utenti.aggiungiUtente(u2);
		assertEquals(Utenti.numEl(),1);
	}
	@Test
	public void rimuoviUtentetest() throws FormatException {
		assertEquals(Utenti.numEl(),0);
		Utente u1=new Utente("Gianni","gianni@hotmail.it");
		Utenti.aggiungiUtente(u1);
		assertEquals(Utenti.numEl(),1);
		Utenti.RimuoviUtente("Gianni");
		assertEquals(Utenti.numEl(),0);
		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Utente non presente, impossibile rimuovere");
		Utenti.RimuoviUtente("Marco");
		
	}
	@Test
	public void verificaUtentetest() throws FormatException {
		Utente u1=new Utente("Gianni","gianni@hotmail.it");
		Utente u2=new Utente("Lorenzo","lorenzo@gmnail.com");
		Utenti.aggiungiUtente(u1);
		Utenti.aggiungiUtente(u2);
		Utente u3=new Utente("Marco","marco@gmnail.com");
		assertTrue(Utenti.contains(u2.getNome()));
		assertFalse(Utenti.contains(u3.getNome()));
		
	}
	@Test
	public void ElencoUtentiTest() throws FormatException {
		Utente u1=new Utente("Gianni","gianni@hotmail.it");
		Utente u2=new Utente("Marco","marco@gmnail.com");
		Utenti.aggiungiUtente(u1);
		Utenti.aggiungiUtente(u2);
		assertEquals(Utenti.elencoUtenti(),"Gianni\n"+ "Marco\n");
		
	}
	@Test
	public void GetUtenteTest() throws FormatException
	{
		Utente u1=new Utente("Gianni","gianni@hotmail.it");
		Utente u2=new Utente("Marco","marco@gmnail.com");
		Utenti.aggiungiUtente(u1);
		Utenti.aggiungiUtente(u2);
		assertEquals(Utenti.getUtente("Gianni").getNome(),u1.getNome());
		assertEquals(Utenti.getUtente("Gianni").getEmail(),u1.getEmail());

		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Utente non trovato");
		assertEquals(Utenti.getUtente("Maria").getNome(),u1.getNome());

	}


}
