package test;

import static org.junit.Assert.*;

import org.junit.Test;

import main.*;

public class Test_gestore_appelli {


	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari
	
	// Test che verifica che inserendo come input una matricola e il codice di un
	// corso ritorni qualcosa, in questo caso deve ritornare un oggetto corso
	@Test
	public void test_gA_CdL() {
		
		assertNotNull(gestore_appelli.verifica_corso_laurea(20018222,133));
	}
	
	//Test vero perchè ritorna correttamente un oggetto corso
	@Test
	public void test_gA_CdL_2() {
		
		assertTrue(gestore_appelli.verifica_corso_laurea(20018222,133));
	}
	
	//Test falso perchè matricola inesistente  ma il codice corso corretto
	@Test
	public void test_gA_CdL_3() {
		
		assertFalse(gestore_appelli.verifica_corso_laurea(20018212,133));
	}
	
	//Test falso perchè matricola corretta ma il codice corso non esiste
	@Test
	public void test_gA_CdL_4() {
		
		assertFalse(gestore_appelli.verifica_corso_laurea(20018222,999));
	}
	
	//Test fallisce perchè il codice del corso e la matricola non esistono
	@Test
	public void test_gA_CdL_5() {
		
		assertFalse(gestore_appelli.verifica_corso_laurea(999,999));
	}
	
	//Dato in input una matricola e il codice di un appello ritorna l'oggetto voto
	//Verifichiamo che ritorni qualcosa
	@Test
	public void test_gA_voto() {
		
		assertNotNull(gestore_appelli.verifica_esistenza_voto(20018222,"A07"));
	}
	
	//Test fallisce perchè il codice del corso non esiste
	@Test
	public void test_gA_voto2() {
		assertEquals(null,gestore_appelli.verifica_esistenza_voto(20018222,"999"));

	}
	
	//Test fallisce perchè la matricola non esiste
	@Test
	public void test_gA_voto3() {
		assertEquals(null,gestore_appelli.verifica_esistenza_voto(1234,"A07"));

	}
	
	//Test fallisce perchè la matricola e il codice del corso non esistono
	@Test
	public void test_gA_voto4() {
		assertEquals(null,gestore_appelli.verifica_esistenza_voto(1234,"FGHI"));

	}
	
	//Test che verifica che l'oggetto voto che viene ritornato contenga il valore corretto
	@Test
	public void test_gA_voto5() {
		assertEquals(26,gestore_appelli.verifica_esistenza_voto(20018222,"A07").valore);
	}

}
