package main;

public class prototipo
{

	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari
  	public static void main(String[] args) 
	{
		DB_utenti db_u= new DB_utenti();
		DB_appelli db_a= new DB_appelli();
		DB_corsi db_c = new DB_corsi();
		gestore_appelli g_a=new gestore_appelli(db_u,db_a,db_c);
		
		//<appello data_appello="04/02/2019" ora_appello="11:00" inizio_prenotazioni="04/01/2019" 
		//fine_prenotazioni="26/01/2019" numero_aula="104" tipo="orale" codice_appello="A07" 
		//codice_corso="reti2" cognome_docente="Giordana" 
		//verbalizzato="false" nome_corso="Reti 2" username_docente="attilio.giordana"/>
		
		appello a= new appello();
		a.data_appello = new data();
		a.data_appello.giorno = 4;
		a.data_appello.mese= 2;
		a.data_appello.anno =2019;
		a.ora_appello = new orario();
		a.ora_appello.minuti= "00";
		a.ora_appello.ora = 11;
					
		a.inizio_prenotazioni= new data();
		a.inizio_prenotazioni.giorno =04;
		a.inizio_prenotazioni.mese = 01;
		a.inizio_prenotazioni.anno = 2019;
		
		a.fine_prenotazioni= new data();
		a.fine_prenotazioni.giorno = 26;
		a.fine_prenotazioni.mese = 01;
		a.fine_prenotazioni.anno = 2019;	
		
		a.numero_aula=104;
		a.tipo ="orale";
		a.codice_appello ="A06";
		a.codice_corso = 126;
		a.cognome_docente ="Giordana";
		a.verbalizzato= false;
		a.nome_corso = "Reti 2";
		a.username_docente = "attilio.giordana";	
	
		//Matricola = 20021037

		int m = 20021037;
		UI_appello ui_a= new UI_appello(g_a,m,a);	
  	}
}