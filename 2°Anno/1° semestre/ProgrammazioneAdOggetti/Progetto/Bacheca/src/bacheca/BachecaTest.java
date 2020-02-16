package bacheca;

import static org.junit.Assert.*;

import java.io.IOException;
import java.util.Iterator;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

public class BachecaTest {
	@Rule
	public ExpectedException eccezione= ExpectedException.none();
	Bacheca b;
	@Before
	public void testcreazione() {
		b=new Bacheca();
		assertEquals(b.numEl(),0);
		Utenti.crea();
		assertEquals(Utenti.numEl(),0);
	}
	
	@Test
	public void testAggiungiAnnuncio() throws FormatException{
		Utente u=new Utente("Marco","Marco@Gmail.com");
		Utenti.aggiungiUtente(u);
		assertEquals(Utenti.numEl(),1);
		Annunci a=new Annunci('C',"Macchina",u,1,2000,1,"Elettronica","Auto");
		b.aggiungiAnnuncio(a);
		
		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Annuncio gia presente");
		b.aggiungiAnnuncio(a);
			
		Annunci a1=new Annunci('C',"Casa",u,1,2000,2,"legno");
		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Nessuna corrispondenza nelle parole chiave");
		b.aggiungiAnnuncio(a1);
		Annunci a2=new Annunci('C',"Casa",u,1,2000,3,"elettronica");
		b.aggiungiAnnuncio(a2);
		assertEquals(b.numEl(),2);
		Annunci a3=new Annunci('V',"Computer",u,1,2000,4,"elettronica");
		b.aggiungiAnnuncio(a3);
		Annunci a4=new Annunci('V',"Mercedes",u,1,2000,5,"auto");
		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Dimensione massima raggiunta");
		b.aggiungiAnnuncio(a4);
		
	}
	@Test
	public void testparoleChiaveString() {
		assertEquals(b.paroleChiaveString(),"Abbigliamento-Alimentari-Altro-Arredamento-Auto-Bellezza-Casa-Elettronica-Film-Giardinaggio-Giochi-Gioielli-Informatica-Libri-Moto-Musica-Telefonia-Sport-Videogiochi");
	}
	@Test 
	public void testlistaPropriAnnunci() throws FormatException
	{
		Utente u=new Utente("Marco","Marco@Gmail.com");
		Annunci a1=new Annunci('C',"Mouse",u,1,2000,3,"Elettronica");
		Utenti.aggiungiUtente(u);
		b.aggiungiAnnuncio(a1);
		Utente u2=new Utente("Andrea","andrea@Gmail.com");
		Utenti.aggiungiUtente(u2);
		Annunci a2=new Annunci('V',"Computer",u2,1,2000,4,"Elettronica");
		b.aggiungiAnnuncio(a2);
		Annunci a3=new Annunci('V',"Mercedes",u,1,2000,5,"Auto");
		b.aggiungiAnnuncio(a3);
		assertEquals(b.listaPropriAnnunci(u),"C,Mouse,Marco,Marco@Gmail.com,1,2000,3,Elettronica\nV,Mercedes,Marco,Marco@Gmail.com,1,2000,5,Auto");
		assertEquals(b.listaPropriAnnunci(u2),"V,Computer,Andrea,andrea@Gmail.com,1,2000,4,Elettronica");

	}
	@Test
	public void testTrovaAnnunci() throws FormatException {
		Utente u=new Utente("Marco","Marco@Gmail.com");
		Annunci a1=new Annunci('C',"Mouse",u,1,2000,3,"Elettronica");
		Utenti.aggiungiUtente(u);
		b.aggiungiAnnuncio(a1);
		Utente u2=new Utente("Andrea","Marco@Gmail.com");
		Utenti.aggiungiUtente(u2);
		Annunci a2=new Annunci('V',"Computer",u2,1,2000,4,"Elettronica");
		b.aggiungiAnnuncio(a2);
		Annunci a3=new Annunci('V',"Mercedes",u,1,2000,5,"Auto");
		b.aggiungiAnnuncio(a3);
		assertEquals(b.trovaAnnunci(u).toString(),"[C,Mouse,Marco,Marco@Gmail.com,1,2000,3,Elettronica, V,Mercedes,Marco,Marco@Gmail.com,1,2000,5,Auto]");
		assertEquals(b.trovaAnnunci(u2).toString(),"[V,Computer,Andrea,Marco@Gmail.com,1,2000,4,Elettronica]");
		Utente u3=new Utente("Gennaro","Marco@Gmail.com");
		Annunci a4=new Annunci('C',"Casa",u3,1,2000,3,"elettronica");
		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Utente non presente");
		b.aggiungiAnnuncio(a4);

	}
	@Test
	public void testRimuoviAnnuncio() throws FormatException {
		Utente u=new Utente("Marco","Marco@Gmail.com");
		Annunci a1=new Annunci('C',"Casa",u,1,2000,3,"Elettronica");
		Utenti.aggiungiUtente(u);
		b.aggiungiAnnuncio(a1);
		Utente u2=new Utente("Andrea","Marco@Gmail.com");
		Utenti.aggiungiUtente(u2);
		Annunci a2=new Annunci('V',"Computer",u2,1,2000,4,"Elettronica");
		b.aggiungiAnnuncio(a2);
		Annunci a3=new Annunci('V',"Mercedes",u,1,2000,5,"Auto");
		b.aggiungiAnnuncio(a3);
		assertEquals(b.numEl(),3);
		b.rimuoviAnnuncio(4, u2);
		assertEquals(b.numEl(),2);
		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Nessun annuncio trovato");
		b.rimuoviAnnuncio(4,u2);


	}
	@Test
	public void testVisualizzaAnnuncioTest() throws FormatException {
		Utente u=new Utente("Marco","Marco@Gmail.com");
		Annunci a1=new Annunci('C',"Tastiera",u,1,2000,3,"Elettronica");
		Utenti.aggiungiUtente(u);
		b.aggiungiAnnuncio(a1);
		Utente u2=new Utente("Andrea","Marco@Gmail.com");
		Utenti.aggiungiUtente(u2);
		Annunci a2=new Annunci('V',"Computer",u2,1,2000,4,"Elettronica");
		b.aggiungiAnnuncio(a2);
		Annunci a3=new Annunci('V',"Mercedes",u,1,2000,5,"Auto");
		b.aggiungiAnnuncio(a3);
		assertEquals(b.numEl(),3);
		assertEquals(b.visualizzaAnnuncio(5),"V,Mercedes,Marco,Marco@Gmail.com,1,2000,5,Auto");
	


	}
	@Test
	public void testElencoAnnunci() throws FormatException {
		Utente u=new Utente("Marco","Marco@Gmail.com");
		Annunci a1=new Annunci('C',"Mouse",u,1,2000,3,"Elettronica");
		Utenti.aggiungiUtente(u);
		b.aggiungiAnnuncio(a1);
		Utente u2=new Utente("Gennaro","Marco@Gmail.com");
		Utenti.aggiungiUtente(u2);
		Annunci a2=new Annunci('V',"Computer",u2,1,2000,4,"Elettronica");
		b.aggiungiAnnuncio(a2);
		Annunci a3=new Annunci('V',"Mercedes",u,1,2000,5,"Auto");
		b.aggiungiAnnuncio(a3);
		assertEquals(b.numEl(),3);
		assertEquals(b.elencoAnnunci(),"C,Mouse,Marco,Marco@Gmail.com,1,2000,3,Elettronica\nV,Computer,Gennaro,Marco@Gmail.com,"
				+ "1,2000,4,Elettronica\nV,Mercedes,Marco,Marco@Gmail.com,1,2000,5,Auto");
	


	}
	@Test
	public void testintersezione() throws FormatException {
		Utente u=new Utente("Marco","Marco@Gmail.com");
		Annunci a1=new Annunci('C',"Mouse",u,1,2000,3,"Elettronica");
		Utenti.aggiungiUtente(u);
		b.aggiungiAnnuncio(a1);
		Utente u2=new Utente("Gennaro","Marco@Gmail.com");
		Utenti.aggiungiUtente(u2);
		Annunci a2=new Annunci('V',"Computer",u2,1,2000,4,"Elettronica");
		b.aggiungiAnnuncio(a2);
		Annunci a3=new Annunci('V',"Mercedes",u,1,2000,5,"Auto");
		b.aggiungiAnnuncio(a3);
		assertEquals(b.numEl(),3);
		assertEquals(b.intersezione("Elettronica","Discreta").size(),2);
	


	}
	
	@Test
	public void testIterator() throws FormatException
	{
		Iterator<Annunci> it1 = b.iterator();
		Utente u=new Utente("Marco","Marco@Gmail.com");
		Annunci a1=new Annunci('C',"Mouse",u,1,2000,3,"Elettronica");
		Utenti.aggiungiUtente(u);
		b.aggiungiAnnuncio(a1);
		Utente u2=new Utente("Gennaro","Marco@Gmail.com");
		Utenti.aggiungiUtente(u2);
		Annunci a2=new Annunci('V',"Computer",u2,1,2000,4,"Elettronica");
		b.aggiungiAnnuncio(a2);
		Annunci a3=new Annunci('V',"Mercedes",u,1,2000,5,"Auto");
		b.aggiungiAnnuncio(a3);
		assertEquals(b.numEl(),3);
		assertTrue(it1.hasNext());
		assertEquals(it1.next().getNome(),"Mouse");

		assertTrue(it1.hasNext());
		assertEquals(it1.next().getNome(),"Computer");
		assertTrue(it1.hasNext());

		assertEquals(it1.next().getNome(),"Mercedes");
		assertFalse(it1.hasNext());
		assertEquals(it1.next(),null);

	}
	@Test
	public void testRead() throws IOException, FormatException
	{
		b.leggiBacheca("bacheca");
		assertEquals(b.elencoAnnunci(),"C,Mouse,Marco,Marco@Gmail.com,1,2000,3,Elettronica\n" + 
				"V,Computer,Gennaro,Marco@Gmail.com,1,2000,4,Elettronica\n" + 
				"V,Mercedes,Marco,Marco@Gmail.com,1,2000,5,Auto");
	}
	
	
}
