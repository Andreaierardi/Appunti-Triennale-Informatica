package bacheca;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

public class AnnunciTest {

	Annunci ann, ann1, ann2, ann3;
	@Rule
	public ExpectedException eccezione= ExpectedException.none();
	
	@Before
	public void testCostruttore() throws FormatException
	{
		ann = new Annunci('C',"Moto",new Utente("AndreaIerardi", "andreaierardi@gmail.com"),1,3000,2,"Motori","Moto");
		assertEquals(ann.getID(),2);
		assertEquals(ann.getNomeUtente(),"AndreaIerardi");
		assertEquals(ann.getT(),'C');
		assertEquals(ann.getParoleChiave().size(),2);
		assertEquals(ann.getNome(),"Moto");
		
		ann1 = new Annunci('V',"Sedia",new Utente("EdoardoFavorido", "edoardofavorido@gmail.com"),3,20,3,"Arredamento");
		assertEquals(ann1.getID(),3);
		assertEquals(ann1.getNomeUtente(),"EdoardoFavorido");
		assertEquals(ann1.getT(),'V');
		assertEquals(ann1.getParoleChiave().size(),1);
		assertEquals(ann1.getNome(),"Sedia");
		
		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Errore inserimento tipo di annuncio");
		ann2 = new Annunci('L',"IphoneX",new Utente("GiovanniManni", "giovannimanni@gmail.com"),1,1500,4,"Telefonia","Tecnologia","Informatica");
		
		eccezione.expect(FormatException.class);
		eccezione.expectMessage("Errore inserimento ID");
		ann2 = new Annunci('V',"Mouse",new Utente("DanieleMani", "danielemani@gmail.com"),4,20,5,"Tecnologia","Informatica");
		
		
	}
	
	
	@Test
	public void testlistaParole() 
	{
		assertEquals(ann.listaParole(),"Motori-Moto");
		assertEquals(ann1.listaParole(),"Arredamento");
	}
	@Test
	public void testtoString() 
	{
		assertEquals(ann.toString(),"C,Moto,AndreaIerardi,andreaierardi@gmail.com,1,3000,2,Motori-Moto");
		assertEquals(ann1.toString(),"V,Sedia,EdoardoFavorido,edoardofavorido@gmail.com,3,20,3,Arredamento");
	}
		


}
