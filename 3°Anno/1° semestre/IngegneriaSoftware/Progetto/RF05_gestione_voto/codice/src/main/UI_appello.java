package main;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class UI_appello {

	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari
	
	String risposta;
	boolean esito;
	voto v;
	int matricola;
	int codice_corso;
	String codice_appello;
	
	public UI_appello(gestore_appelli g_a, int m, appello a)
	{	
	  	matricola = m;
	  	codice_corso = a.codice_corso;
	  	codice_appello = a.codice_appello;
		
	   System.out.println("-------------------------\n|      UI_APPELLO       |\n---------------------------------------");		
	   boolean esito = g_a.verifica_corso_laurea(matricola, codice_corso);
	   if (!esito)
		  this.mostra_errore(1);
	   else
	   {
		   voto v = g_a.verifica_esistenza_voto(matricola,codice_appello);
		   if( v == null)
			   	mostra_errore(2);
		   else
		   {	
			   this.visualizza_stato_del_voto(v);
			   if(v.accettato)
				   this.mostra_conferma("1");
			   else
			   {
				   if(v.valore >= 18 && !v.accettato)
				   {
					   this.mostra_elenco_azioni();
					   g_a.richiesta_update_voto(v, risposta);
					   this.mostra_conferma(risposta);

				   } 

			   }
				 
			 
		   }
	   }
	   System.out.println("\n---------------------------------------");
	}

	
	private void mostra_conferma(String risposta)
	{
		  System.out.println("\n==============================\n=Visualizza conferma del voto=\n==============================");
		  Integer r = Integer.parseInt(risposta);
		 
		  if(r==1)
			  System.out.println("Voto accettato");
			  
		  else
			  System.out.println("Voto rifiutato");
		  
		  
		  System.out.println("\n==============================\n");
	
	}


	private void mostra_elenco_azioni()
	{
	
		System.out.println("_____________________\n|MOSTRA ELENCO AZIONI|\n|____________________|\n");
	
		try
		{
		  BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
		  System.out.println("0: Rifiuta voto\n1: Accetta voto");
		  System.out.println("_______________________");
		  System.out.println("Inserire Risposta");
		 
		  this.risposta= bufferRead.readLine();	
		}
		
		catch(IOException e)
		{
		  System.out.println("ERRORE I/0");
		}
	}



	private void visualizza_stato_del_voto(voto v) 
	{
		System.out.println("\n===========================\n=Visualizza stato del voto=\n===========================\n");
		if(v.data_accettazione == null)
			System.out.println("Voto in sospeso");
		else if(v.accettato)
			System.out.println("Voto accettato");
		else 
			System.out.println("Voto rifiutato");
		
		System.out.println("\n===========================\n");
		
	}

	public void mostra_errore(int tipo_errore)
	{
	
	    try
	    {
	      BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
	
	      if (tipo_errore==1)
	    	  System.out.println("\nERRORE: appello non trovato");
	      if (tipo_errore==2)
	    	  System.out.println("\nERRORE: voto non trovato");
	      System.out.println("premi INVIO per confermare");
	      String conferma = bufferRead.readLine();	
	    }
	
	    catch(IOException e)
	    {
	      System.out.println("ERRORE I/0");
	    }
	}
	
}
