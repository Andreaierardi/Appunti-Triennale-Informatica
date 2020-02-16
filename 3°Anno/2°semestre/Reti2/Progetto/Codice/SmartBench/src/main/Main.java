package main;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.InetSocketAddress;

import java.util.ArrayList;
import java.util.logging.Logger;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.json.JSONObject;

import org.json.JSONException;

import com.sun.net.httpserver.HttpServer;

//import controllo.Controllo;
import controllo.ControlloLogger;
import controllo.MainC;
import controllo.PubToClient;
//import database.GestoreDB;
import httpserver.EchoPostHandler;
import httpserver.ResetHandler;
import httpserver.RootHandler;
//import sensori.Bilanciere;
//import sensori.Bracciale;
import sensori.MainS;
//import sensori.Pesi;

public class Main {


	/* INDIRIZZI DEI BROKER*/
	public static String BROKER_CLOUD;
	public static String BROKER_BB;

	/* ================================*/

	final static String CONT_TOPIC_SUB = "smartbench/controllo/" ;
	final static String DB_TOPIC= "smartbench/db/";
	public static String BROKER_URL; //= "tcp://193.206.55.23:1883";


	public static Thread main_task;
	public static Runnable main_runnable;

	public static int time_all;
	public static int time_bil;
	public static int time_pause;
	public static int Time_bl=0;
	public static int Time_br=0;
	public static int defaultW = 0;
	public static int probabilita;

	
	public static ArrayList<Thread> lista_thread = new ArrayList<Thread>();
	public static ArrayList<Object> lista_reset = new ArrayList<Object>();

	public static int ERROR;
	public static int reset;
	public static PubToClient pc;
	public static String TOPIC_PUB_BRACCIALE;

	public static String TOPIC_PUB_BRACCIALE_1;
	public static String TOPIC_PUB_BRACCIALE_2;
	public static String TOPIC_PUB_BILANCIERE;
	public static String TOPIC_PUB_PESI;
	public static String TOPIC_SUB_BRACCIALE;
	public static String TOPIC_SUB_BILANCIERE;
	public static String TOPIC_SUB_PESI;
	public static String TOPIC_PUB_CONTROLLO;
	public static String TOPIC_PUB_CONTROLLO2;
	public static String TOPIC_PUB_TO_CLIENT;
	public static String TOPIC_PUB_TO_CLIENT_2;
	public static String TOPIC_SUB_CONTROLLO;
	public static String TOPIC_PUB_DB;
	public static String TOPIC_PUB_DB_2;
	public static String TOPIC_PUB_DB_3;
	public static String TOPIC_PUB_DB_4;
	public static String TOPIC_SUB_DB;
	public static String TOPIC_PUB_CLIENT;
	public static String TOPIC_SUB_CLIENT;
	

	public final static Logger logger = Logger.getLogger(ControlloLogger.class.getName());

	public static void main(String[] args) throws InterruptedException, MqttSecurityException, MqttException, IOException, JSONException{

	
		/* Setting variabili globali*/
		parseJSON("src/main/topic.json");
		
		/** DA CANCELLARE DENTRO LA RETE DELL'UNI **/
		//Main.BROKER_BB = "tcp://193.206.55.23:1883";
		/* Setting HTTPServer*/
		HttpServer server = HttpServer.create(new InetSocketAddress(11000), 0);
		System.out.println("Server pronto sulla porta " + 11000);

		server.createContext("/",new RootHandler());
		server.createContext("/load",new EchoPostHandler());
		server.createContext("/reset", new ResetHandler());
		server.setExecutor(null);
		server.start();

		
		Main.main_runnable = () -> {

			if(BROKER_URL!=null && ERROR!=1)
				BROKER_URL= "tcp://"+BROKER_URL+":1883";
			if(ERROR==1)
			{
				if(BROKER_URL!=null)
				{
					System.out.println(Main.BROKER_URL);
					
					try {
						pc = new PubToClient(999, "from/retilab/reti8/client/risposta/");
					} catch (MqttException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
					pc.setValue("logout");
					Thread client = new Thread(pc);
					lista_thread.add(client);

					client.start();
					try {
						client.join();
					} catch (InterruptedException e) {
						e.printStackTrace();
					}
					reset =0 ;
				}
				System.out.println("Spegnimento di EMERGENZA");
				System.exit(1);
			}

			if(reset==1)
			{
				if(BROKER_URL!=null)
				{
					System.out.println(Main.BROKER_URL);
					
					try {
						pc = new PubToClient(999, "from/retilab/reti8/client/risposta/");
					} catch (MqttException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					pc.setValue("logout");
					Thread client = new Thread(pc);
					lista_thread.add(client);

					client.start();
					reset =0 ;
				}

			}


		//   Main.BROKER_CLOUD = "ssl://iotlabgw.edu-al.unipmn.it:8883";
			System.out.println("LE BIBBI: " +Main.BROKER_BB);
			//Main.BROKER_BB = "tcp://193.206.55.23:1883";
			Main.BROKER_URL = Main.BROKER_CLOUD;
			/* INIT LOGGER*/
			ControlloLogger.init();

			try {
				Time_br = leggiJSON("src/main/confbracciale.json");
			} catch (JSONException e1) {
				System.out.println("FILE di configurazione bracciale non trovato");
			}
			try {
				Time_bl = leggiJSON("src/main/confbilanciere.json");
			} catch (JSONException e1) {
				System.out.println("FILE di configurazione bilanciere non trovato");
			}

			try {
				defaultW = leggiJSON("src/main/confpesi.json");
			} catch (JSONException e1) {
				System.out.println("FILE di configurazione pesi non trovato");
			}
			
			
		
			try {
				MainS.main(args);
			} catch (InterruptedException | MqttException | IOException | JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			try {
				MainC.main(args);
			} catch (InterruptedException | MqttException | IOException | JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}


		

		};
	}

	public static void parseJSON(String nomefile) throws JSONException
	{
		String result = "";
		try {
			BufferedReader br = new BufferedReader(new FileReader(nomefile));
			StringBuilder sb = new StringBuilder();
			String line = br.readLine();
			while (line != null) {
				sb.append(line);
				line = br.readLine();
			}
			br.close();
			result = sb.toString();
		} catch(Exception e) {
			e.printStackTrace();
		}

		JSONObject object = new JSONObject(result);
		BROKER_CLOUD = object.getString("BROKER_CLOUD");

		BROKER_BB = object.getString("BROKER_BB");
		
		/* TOPIC DEI SENSORI */
		TOPIC_PUB_BRACCIALE_1 = object.getString("TOPIC_PUB_BRACCIALE_1");

		TOPIC_PUB_BRACCIALE_1 = object.getString("TOPIC_PUB_BRACCIALE_1");
		//"to/retilab/reti8/gpio/OUT0";	
		TOPIC_PUB_BRACCIALE_2= object.getString("TOPIC_PUB_BRACCIALE_2");
		//"to/retilab/reti8/gpio/OUT1";
		TOPIC_PUB_BILANCIERE = object.getString("TOPIC_PUB_BILANCIERE");
		//"to/retilab/reti8/gpio/OUT2";
		TOPIC_PUB_PESI =  object.getString("TOPIC_PUB_PESI");
		//"to/retilab/reti8/gpio/OUT3";

		TOPIC_SUB_BRACCIALE = object.getString("TOPIC_SUB_BRACCIALE");
		//"from/retilab/reti8/gpio/OUT4";
		TOPIC_SUB_BILANCIERE = object.getString("TOPIC_SUB_BILANCIERE"); 
		//"from/retilab/reti8/gpio/OUT4";

		TOPIC_SUB_PESI =object.getString("TOPIC_SUB_PESI");
		//"from/retilab/reti8/gpio/OUT4";

		/* TOPIC DEL CONTROLLO */

		TOPIC_PUB_CONTROLLO =object.getString("TOPIC_PUB_CONTROLLO");
		//"from/retilab/reti8/db/wr";
		TOPIC_PUB_CONTROLLO2 = object.getString("TOPIC_PUB_CONTROLLO2");
		//"to/retilab/reti8/gpio/OUT4";

		TOPIC_PUB_TO_CLIENT = object.getString("TOPIC_PUB_TO_CLIENT");
		//"from/retilab/reti8/client";
		TOPIC_SUB_CONTROLLO = object.getString("TOPIC_SUB_CONTROLLO");
		//"from/retilab/reti8/#";

		/* TOPIC DEL DATABASE*/
		TOPIC_PUB_DB =object.getString("TOPIC_PUB_DB");
		TOPIC_PUB_DB_2 =object.getString("TOPIC_PUB_DB_2"); 
		//"from/retilab/reti8/login";
		TOPIC_PUB_DB_3 = object.getString("TOPIC_PUB_DB_3");
		//"from/retilab/reti8/logout";

		TOPIC_PUB_DB_4 = object.getString("TOPIC_PUB_DB_4");
		//"from/retilab/reti8/client/risposta"
		TOPIC_SUB_DB = object.getString("TOPIC_SUB_DB");
		//"from/retilab/reti8/db/#";

		/* TOPIC DEL CLIENT */
		TOPIC_PUB_CLIENT= object.getString("TOPIC_PUB_CLIENT");
		//"from/retilab/reti8/db";
		TOPIC_PUB_TO_CLIENT_2 = object.getString("TOPIC_PUB_TO_CLIENT_2");

		TOPIC_SUB_CLIENT = object.getString("TOPIC_SUB_CLIENT");
		//"from/retilab/reti8/client/#";
	}
	
	public static int leggiJSON(String nomefile) throws JSONException
	{
		String result = "";
		try {
			BufferedReader br = new BufferedReader(new FileReader(nomefile));
			StringBuilder sb = new StringBuilder();
			String line = br.readLine();
			while (line != null) {
				sb.append(line);
				line = br.readLine();
			}
			br.close();
			result = sb.toString();
		} catch(Exception e) {
			e.printStackTrace();
		}

		JSONObject object = new JSONObject(result);
		int value= 0;
		if(nomefile.equals("src/main/confbilanciere.json"))
			{
				Main.probabilita=object.getInt("probabilita");
				System.out.println("Probabilita' da file "+nomefile+": "+Main.probabilita);

			}
		if(nomefile.equals("src/main/confpesi.json"))
			 {
				value = object.getInt("weight");
				System.out.println("Weight da file "+nomefile+": "+value);
			 }
		else
			 value =  object.getInt("time");
		System.out.println("Time da file '"+nomefile+"': " + value);

		return value;
	}
}


