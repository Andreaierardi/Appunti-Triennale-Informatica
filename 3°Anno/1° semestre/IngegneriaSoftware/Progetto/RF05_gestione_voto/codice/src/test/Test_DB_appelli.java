package test;
import main.*;
import static org.junit.Assert.*;
import org.junit.Test;
public class Test_DB_appelli
{

	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari
	//Campo 1 e 2 giusti
	@Test 
	public void test_ricerca_voto_1()
	{
		
		assertNotNull("DB deve ritornare qualcosa", DB_appelli.ricerca_voto(20021037,"A07")); 
	}

	//Campo 1 corretto e due errato
	@Test 
	public void test_ricerca_voto_2()
	{
		
    		assertEquals(null,DB_appelli.ricerca_voto(20018222,"A99")); 
	}
	
	//Campo 2 errato 
	@Test 
	public void test_ricerca_voto_3()
	{
			assertEquals(null,DB_appelli.ricerca_voto(20021037,"99999")); 

	}
	
	//Campo 1 e 2 errato 
	@Test 
	public void test_ricerca_voto_4()
	{
			assertEquals(null,DB_appelli.ricerca_voto(99999,"99999")); 

	}
	//Verifica che il voto ritornato sia giusto
	@Test 
	public void test_ricerca_voto_5()
	{
			assertEquals(27,DB_appelli.ricerca_voto(20020572,"A06").valore); 

	}
	
	//Verifica che la data di accettazione dell'appello sia null
	@Test 
	public void test_ricerca_voto_6()
	{
			assertEquals(null,DB_appelli.ricerca_voto(20020572,"A09").data_accettazione); 

	}
	
	//Verifica che la data di accettazione del voto sia corretta 
	@Test 
	public void test_ricerca_voto_7()
	{
		data d = new data();
		d.giorno = 15;
		d.mese = 3;
		d.anno = 2019;
		
		assertEquals(d.giorno,DB_appelli.ricerca_voto(20019238,"A07").data_accettazione.giorno); 
		assertEquals(d.mese,DB_appelli.ricerca_voto(20019238,"A07").data_accettazione.mese); 
		assertEquals(d.anno,DB_appelli.ricerca_voto(20019238,"A07").data_accettazione.anno); 

	}
}

