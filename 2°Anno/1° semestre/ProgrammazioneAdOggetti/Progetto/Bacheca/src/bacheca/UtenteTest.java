package bacheca;

import static org.junit.Assert.*;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;



	public class  UtenteTest{
		@Rule
		public ExpectedException eccezione= ExpectedException.none();
		Utente u;
			@Test
			public void testCostruttore() throws FormatException {
				u=new Utente("Gianni2","gianni@hotmail.it");
				assertEquals(u.getNome(),"Gianni2");
				assertEquals(u.getEmail(),"gianni@hotmail.it");
				eccezione.expect(FormatException.class);
				eccezione.expectMessage("Email scorretta");
				u=new Utente("Gianni","gia@nni@hotmail.it");
				
				eccezione.expect(FormatException.class);
				eccezione.expectMessage("Formato del nome non corretto");
				u=new Utente("@@","gia@nni@hotmail.it");
				u = new Utente("93131","eqew@hotmail.it");
				u = new Utente("andre_eqq","andrea@ciao.it");
			}
			
	}
