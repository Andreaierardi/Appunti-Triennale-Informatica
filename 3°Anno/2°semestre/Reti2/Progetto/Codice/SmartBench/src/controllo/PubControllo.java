package controllo;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
//import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttPersistenceException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.eclipse.paho.client.mqttv3.MqttTopic;

import de.dcsquare.paho.client.util.Utils;
import main.Main;
import smartbench.Allenamento;
import smartbench.Piano;

public class PubControllo implements Runnable {


	public String topic ;
	public String db_topic;

	public String broker;

	SubControlloCallback ccb;
	public DBWriter wr;

	private MqttClient client;

	/* DATI allenamento */

	String utente;
	Piano piano;
	SmartBench sm;

	/* VALORI OTTENUTI DA MESSAGGI IN CONTROLLOCALLBACK */
	int mediaPS;
	double mediaFC;
	int ripSerie=0 ;
	int ripetizioniAll;
	int pesoSerie=0;
	ArrayList<Integer> mediaRip = new ArrayList<Integer>();
	Logger logger;
	public boolean flag = true;
	int peso;
	PubToClient pC;

	public int tempo_pausa;
	public int tempo_all;

	private boolean posato = false;
	private boolean pausa;


	public PubControllo(SubControlloCallback controllCB, String nomeUtente, Piano p) {

		piano = p;
		utente = nomeUtente ;
		logger = Main.logger;

		sm = new SmartBench(pC);
		tempo_all= Main.time_all;
		tempo_pausa= Main.time_pause;
		ccb = controllCB;

		db_topic = Main.TOPIC_PUB_CONTROLLO; //"from/retilab/reti8/db/wr"
		topic = Main.TOPIC_PUB_CONTROLLO2; //"to/retilab/reti8/gpio/OUT4";
		broker = Main.BROKER_BB;
		String clientId = Utils.getMacAddress()+"con-pub"+System.currentTimeMillis();
		peso=piano.peso;


		try {

			client = new MqttClient(broker, clientId);
			MqttConnectOptions options = new MqttConnectOptions();
			options.setCleanSession(false);
			options.setWill(client.getTopic("home/LWT"), "I'm gone :(".getBytes(), 0, false);
			client.connect(options);

			logger.log(Level.INFO, "Connection by publisher "+this.getClass().getName());

		} catch (MqttException e) {
			e.printStackTrace();
			System.exit(1);
		}


	}


	public void pub(String controllo) 
	{
		try 
		{

			logger.log(Level.INFO, "Pub '"+controllo+ "' by publisher "+this.getClass().getName());
			Thread.sleep(500);

			publishControllo(controllo);
			Thread.sleep(500);

		} catch (MqttException e) {
			e.printStackTrace();
			System.exit(1);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}


	private void publishControllo(String controllo) throws MqttPersistenceException, MqttException {

		final MqttTopic c = client.getTopic(topic);
		c.publish(new MqttMessage(controllo.getBytes()));
		//System.println("PUBBLICO controllo. Topic: "+c.getName()+ " MESSAGGIO: "+controllo);
	}
	
	private void publishControlloCl(String controllo) throws MqttPersistenceException, MqttException {

		final MqttTopic c = client.getTopic(Main.TOPIC_PUB_BILANCIERE);
		c.publish(new MqttMessage(controllo.getBytes()));
		//System.println("PUBBLICO controllo per simulare l'avvenuto riposizionamento del bilanciere a fine di time_all. Topic: "+c.getName()+ " MESSAGGIO: "+controllo);
	}

	public boolean pub_allenamento(Allenamento a)
	{

		logger.log(Level.INFO, "Richiesta pubblicazione di un resoconto di allenamento in cloud");
		wr = new DBWriter();
		wr.generateAll(a);
		Thread writer = new Thread(wr);
		Main.lista_thread.add(writer);

		writer.start();

		return true;
	}


	@Override
	public void run() {

		//System.println("STARTO Allenamento");
		//System.println("...con piano attuale: "+piano.toString());
		try {
			startAllenamento();
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}


	private void startAllenamento() throws MqttSecurityException, MqttException 
	{
		logger.log(Level.INFO, "Start dell'allenamento");

		int cserie = 1;
		posato = false;
		//System.println("PIANO PESO:(init all) "+piano.peso);

		try {
			pub("{cmd:"+piano.peso+"}");
			logger.log(Level.INFO, "Comando: "+"{cmd:"+piano.peso+"} per notificare al sensore di peso il peso nel piano dell'utente");

			sm.settaPeso(piano.peso);
		} 
		catch (InterruptedException e1) {}

		pesoSerie += piano.peso;
		flag = true;

		while (cserie<=piano.serie && flag)
		{
			//System.println("Esecuzione allenamento di "+tempo_all+"s ...");

			posato = false;
			pausa = false;

			ccb.setPosato(false);
			
			logger.log(Level.INFO, "Invio comando: {cmd:2} per richiedere il peso rilevato dal sensore");
			pub("{cmd:2}");
			
			if(!flag)
				break;
			else
				{
					pub("{cmd:1}");
					logger.log(Level.INFO, "Invio comando:  {cmd:1} per far startare i sensori");

				}

			try {
				int count = 0 ;

				while(count<tempo_all && flag && !posato)
				{
					count++;
					posato = ccb.getPosato();
					if(posato)
					{	
						//System.println("Bilanciere posato dopo "+ count+"s di allenamento...");
						logger.log(Level.INFO, "Il bilanciere riposto in sede dopo "+count+ " secondi di allenamento");

						break;
					}
					if(!ccb.m.flagPull && !posato)
					{
						logger.log(Level.INFO, "Rilevata criticit�, Invio comando: {cmd:0} per fermare i sensori e mando allarme");
						pub("{cmd:0}");
						sm.allarmeAtleta();
						ccb.m.flagPull=true;
						flag=false;

					}
					TimeUnit.SECONDS.sleep(1);	
					if(posato)
					{	
						//System.println("Bilanciere posato dopo "+ count+"s di allenamento...");
						logger.log(Level.INFO, "Il bilanciere riposto in sede dopo "+count+ " secondi di allenamento");

						break;
					}
				}
				//System.println("Serie terminata...");
				logger.log(Level.INFO, "Serie "+cserie+" terminata");


			} catch (InterruptedException e) {}

			if(!posato)
				try {
					publishControlloCl("{cmd:2}");
				} catch (MqttPersistenceException e2) {
					// TODO Auto-generated catch block
					e2.printStackTrace();
				} catch (MqttException e2) {
					// TODO Auto-generated catch block
					e2.printStackTrace();
				}
			pausa = true;
			if(ccb.getPeso()==peso)
				{
					//System.println("PESO Coerente");
					logger.log(Level.INFO, "Check del peso: il peso tra controllo e sensori � coerente");

				}
			else
				{
					//System.println("PESO DIFFERENTE: (ccb, peso): "+ccb.getPeso()+","+peso);
					logger.log(Level.INFO, "Check del peso: il peso tra controllo e sensori � incongruente");

				}
			ccb.setPausa(true);
		
			if(!flag)
				break;

			else 
				pub("{cmd:0}");


			//System.println("=======================\nBREAK\n==================");

			try {
				ripSerie = rilevaRipetizioni(cserie);
			} catch (InterruptedException e1) {	}	

			mediaRip.add(ripSerie);
			ripetizioniAll+=ripSerie;
			//System.println("Ripetizioni di questa serie: "+ ripSerie);
			//System.println("Ripetizioni totali: "+ ripetizioniAll);

			if(!flag)
				break;

			if(cserie != piano.serie)
			{

				try { 

					logger.log(Level.INFO, "Invio {cmd:0} ai sensori per fermare il monitoring e inizio della pausa di "+tempo_pausa+" secondi");

					int count = 0 ;
					//System.println("Pausa di "+tempo_pausa+"s iniziata...");
					while(count<tempo_pausa && flag) 
					{
						count++;
						TimeUnit.SECONDS.sleep(1);	
					}
				}catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			pausa = false;

			ccb.setPausa(false);


			//System.println("--------------\nFINE BREAK\n----------------");


			logger.log(Level.INFO, "Fine della pausa");

			cserie++;
		}

		if(cserie > piano.serie && flag)
		{
			logger.log(Level.INFO, "Fine dell'allenamento, calcolo dei parametri da scrivere sul DB");

			ccb.setPausa(false);
			ccb.monitorExit(false);
			mediaFC=calcola_mediaFC();
			mediaPS=calcola_mediaPS();
			int valutazione = valutaAllenamento();
			String timeStamp = new SimpleDateFormat("yyyy/MM/dd,HH:mm").format(new java.util.Date());
			int mR = 0;
			for (int i : mediaRip)
				mR+= i;
			mR /= mediaRip.size();
			int mediaPeso = pesoSerie/piano.serie;

			Allenamento a = new Allenamento(utente, valutazione, mediaFC, mediaPS,mR, mediaPeso, ripetizioniAll, piano.peso, timeStamp);

			//System.println("Allenamento concluso. Allenamento: "+a.toString());
			mediaRip = new ArrayList<Integer>();

			if(!pub_allenamento(a))
				{
					//System.println("Allenamento non scritto");
					logger.log(Level.WARNING, "Errore nella richiesta di scrittura dell'allenamento");

				}
			//System.println("--> TERMINO START ALLENAMENTO");


		}

		if(!flag)
		{
			logger.log(Level.WARNING, "Allenamento interrotto, stop del monitoring e invio comando {cmd:0} ai sensori");

			//System.println("allenamento interrotto...");
			try 
			{
				publishControllo("{cmd:0}");
			} catch (MqttException e) 
			{e.printStackTrace();}
			
			ccb.monitorExit(false);
			ccb.m.setPausa(false);
			ccb.monitor.interrupt();
			posato = true;
			pausa = true;

		}


	}



	private int valutaAllenamento()
	{
		double val=  10*ripetizioniAll/(piano.totRip*piano.serie);
		if(val >=10)
			val = 10;

		return (int) Math.floor(val);
	}

	private int calcola_mediaPS() {
		int sommaPS = 0 ;
		int res=0;
		for(int val:ccb.getValoriPS())
		{
			sommaPS+=val;
		}

		if(ccb.getContaPS()!=0)
			res=sommaPS/ccb.getContaPS();		
		return res;
	}


	private double calcola_mediaFC() {
		double sommaFC = 0;
		double result=0;
		for(double val:ccb.getValoriFC())
		{
			sommaFC += val;
		}
		result=sommaFC/ccb.getContaFC();		
		return result;
	}

	public int rilevaRipetizioni(int cserie) throws InterruptedException, MqttSecurityException, MqttException
	{

		Integer ripetizioni = ccb.getConta();
		ccb.resetConta();
		if(cserie != piano.serie)
		{
			if(ripetizioni < piano.totRip && ripetizioni>=0 && peso >=10)
			{
				peso=sm.riduciPeso(peso);
				pesoSerie+= peso;
				pub("{cmd:"+peso+"}");
				logger.log(Level.INFO, "Invio comando {cmd:"+peso+"}, il peso � stato ridotto");

				//System.println("Riduzione del peso.."+peso);

			}
			else 
				pesoSerie+=piano.peso;
			
		}

		return ripetizioni;
	}
	
	public void setFlag(boolean f)
	{
		//System.println("=====SETTO FLAG di interruzione=====");
		flag = false;
	}


	public boolean getFlag() {

		return flag;
	}


	public boolean getPausaFlag() {
		return pausa;
	}
}
