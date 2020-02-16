package test;

import static org.junit.Assert.*;


import org.junit.Test;

import main.DB_corsi;

public class Test_DB_corsi {


	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari
	
	//Inserendo il codice del corso come input, deve ritornare qualcosa, in questo caso
	//l'oggetto corso
	@Test
	public void test_corso1() {
		assertNotNull("DB deve ritornare qualcosa", DB_corsi.ricerca_dati_corso(125)); 
	}
	
	
	@Test
	public void test_corso2() {
		assertNotNull("DB deve ritornare qualcosa", DB_corsi.ricerca_dati_corso(133)); 
	}
	
	//Verifica che ritorni il corretto oggetto corso contenente il corretto nome
	@Test
	public void test_corso3() {
		String nome = "20018222";
		assertEquals(DB_corsi.ricerca_dati_corso(133).nome,nome); 
	}
	
	//Verifica che ritorni il corretto oggetto corso contenente il corretto anno
	@Test
	public void test_corso4() {
		int anno = 3;
		assertEquals(DB_corsi.ricerca_dati_corso(129).anno,anno); 
	}
	
	//Verifica che ritorni il corretto oggetto corso contenente il giusto corso di laurea
	@Test
	public void test_corso5() {
		String CdL = "Informatica";
		assertEquals(DB_corsi.ricerca_dati_corso(126).cdl,CdL); 
	}
	
	//Verifica che ritorni il corretto oggetto corso contenente il corretto cognome del docente
	@Test
	public void test_corso6() {
		String cognome_docente = "portinale";
		assertEquals(DB_corsi.ricerca_dati_corso(128).cognome_docente,cognome_docente); 
	}
	
	//Verifica che se venga cercato un codice corso inesistente, ritorni null
	@Test
	public void test_corso7() {
		assertEquals(DB_corsi.ricerca_dati_corso(145),null); 
	}

}
