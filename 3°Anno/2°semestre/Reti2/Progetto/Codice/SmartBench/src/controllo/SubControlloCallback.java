package controllo;

import java.util.ArrayList;
import java.util.logging.*;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.json.JSONException;
import org.json.JSONObject;

import main.Main;

import smartbench.Piano;

public class SubControlloCallback implements MqttCallback {


	Logger logger= Main.logger;

	int conta = 0; 
	int contaFC= 0 ; 
	int contaPS= 0; 
	ArrayList<Integer> valoriPS=new ArrayList<Integer>();
	ArrayList<Double> valoriFC=new ArrayList<Double>();

	public boolean idempotenza = true;
	public boolean idempotenza_stop = false;
	public boolean primo = true;
	boolean flagPull= true;
	private boolean posato= false;


	public Piano p;
	private String u;

	public int j= 0;

	public int peso;

	PubToClient pC;	
	PubControllo pc;
	Monitoring m = new Monitoring(j);

	Thread pubClient;
	Thread monitor;
	Thread publisher;




	@Override
	public void connectionLost(Throwable cause)
	{
		;
	}

	@Override
	public void deliveryComplete(IMqttDeliveryToken token) 
	{
		;
	}

	@Override
	public void messageArrived(String topic, MqttMessage message) throws Exception {

		//System.println("--- CONTROLLO --- Message arrived. Topic: " + topic + "  Message: " + message.toString());
		String arg [] = topic.split("/");


		if(arg[arg.length-1].equals("cmd"))
		{
			if(message.toString().equals("exit()"))
				{	
					logger.log(Level.INFO, "Comando di Exit() ricevuto, spegnimento di SmartBench");
					System.exit(1);
				}
		}

		if(arg[arg.length-1].equals("cmd"))
		{
			if(message.toString().equals("start()")&& idempotenza)
			{

				logger.log(Level.INFO, "Comando di start() ricevuto dal client, preparazione all'inizio dell'allemento");
				idempotenza_stop= true;
				idempotenza= false;

				//System.println("FORK: PubControllo");

				pc = new PubControllo(this,u,p);
				publisher = new Thread(pc);
				Main.lista_thread.add(publisher);

				publisher.start();

			}


			if(idempotenza_stop && message.toString().equals("stop()") )
			{

				logger.log(Level.INFO, "Comando di stop() ricevuto dal client, interruzione dell'allenamento.\n"+ "Mando segnale di stop ai sensori e stop del monitoring del bilanciere");
				
				//System.println("Controllo: STOP from Client");
				pc.pub("{cmd:0}");

				monitor.interrupt();
				m.setExit(false);
				pc.setFlag(false);
				publisher.interrupt();
				idempotenza = true;
				primo = true;
				idempotenza_stop= false;

				logger.log(Level.INFO, "Invio al client un messaggio di avvenuta riposizione in sede del bilanciere");
				PubToClient pC3 = new PubToClient(711,Main.TOPIC_PUB_TO_CLIENT_2);
				pC3.setValue("posato");
				Thread pubClient3= new Thread(pC3);
				Main.lista_thread.add(pubClient3);

				pubClient3.start();


			}
		}


		if(arg[arg.length-1].equals("OUT3"))
		{

			String array[] = message.toString().split(":");
			String msn = array[0];
			msn = msn.substring(1);

			if(msn.equals("event"))
			{

				String p = array[1];
				p = p.substring(0,p.length()-1);
				peso = Integer.parseInt(p);
				logger.log(Level.INFO, "Ricevo messaggio {event:"+p+"} dal sensore del peso (OUT3), aggiorno il peso della SmartBench");
				//System.println("<CONTROLLO>Messaggio da PESI" +peso);
			}

		}

		if(arg[arg.length-1].equals("OUT2"))
		{


			if(message.toString().equals("{event:2}"))
			{
				//System.println("SEGNALE DI BILANCIERE POSATO");
				posato = true;
			//	int n = (int)(Math.random()*100);

				logger.log(Level.INFO, "Ricevo messaggio {event:2} dal sensore del bilanciere (OUT2), l'atleta ha posato il bilanciere e la serie attuale terminata");
				pC = new PubToClient(30,Main.TOPIC_PUB_TO_CLIENT_2);
				pC.setValue("posato");
				logger.log(Level.INFO, "Invio al client un messaggio di avvenuta riposizione in sede del bilanciere");
				Thread pubClient= new Thread(pC);
				Main.lista_thread.add(pubClient);

				pubClient.start();
			}


			if(message.toString().equals("{event:1}"))
			{

				if(pc.getFlag() && !pc.getPausaFlag())
				{
					j=0;
					if(primo)
					{
						m = new Monitoring(j);
						logger.log(Level.INFO, "Ricevo messaggio {event:1} dal sensore del bilanciere (OUT2), inizio il monitoring della serie");
						monitor = new Thread(m);
						Main.lista_thread.add(monitor);

						monitor.start();
						primo = false;
					}

					m.resetJ();
					//System.println("<CONTROLLO> Messaggio da bilanciere: "+message);
					conta++;
					//int n = (int)(Math.random()*10);
					logger.log(Level.INFO, "Ricevo messaggio {event:1} dal sensore del bilanciere (OUT2), l'atleta ha eseguito una ripetizione");


					
					pC = new PubToClient(31,Main.TOPIC_PUB_TO_CLIENT);
					pC.setValue("pull");
					Thread pubClient= new Thread(pC);
					Main.lista_thread.add(pubClient);

					pubClient.start();
					logger.log(Level.INFO, "Invio al client un messaggio di una ripetizione eseguita correttamente");

					
					/** COSTRUTTORE PUBTOCLIENT**/
					PubToClient pC2 = new PubToClient(32,Main.TOPIC_PUB_TO_CLIENT_2);
					pC2.setValue("nonposato");
					Thread pubClient2= new Thread(pC2);
					Main.lista_thread.add(pubClient2);

					pubClient2.start();
					logger.log(Level.INFO, "Invio al client un messaggio di bilanciere in uso");




				}
			}

		}



		if(arg[arg.length-1].equals("OUT1"))
		{
			String array[] = message.toString().split(":");
			String msn = array[0];
			msn = msn.substring(1);

			if(msn.equals("event"))
			{
				//System.println("<CONTROLLO>Messaggio da Bracciale - pressione: "+message);

				String p = array[1];
				p = p.substring(0,p.length()-1);
				
				logger.log(Level.INFO, "Ricevo messaggio {event:"+p+"} dal sensore del bracciale relativo alla pressione cardiaca(OUT1), pressione rilevata");
				contaPS++;
				int PS = Integer.parseInt(p.replaceAll("[\\D]", ""));
				valoriPS.add(PS);
			}

		}
		if(arg[arg.length-1].equals("OUT0"))
		{

			String array[] = message.toString().split(":");
			String msn = array[0];
			msn = msn.substring(1);

			if(msn.equals("event"))
			{
				//System.println("<CONTROLLO>Messaggio da Bracciale - frequenza: "+message);

				String p = array[1];
				p = p.substring(0,p.length()-1);
				logger.log(Level.INFO, "Ricevo messaggio {event:"+p+"} dal sensore del bracciale relativo alla frequenza cardiaca(OUT2), pressione rilevata");
				double FC = Double.parseDouble(p.replaceAll("[\\D]-[\\.]", ""));
				contaFC++;

				valoriFC.add(FC);
			}


		}


		if(arg[arg.length-1].equals("logout"))
		{
			//System.println("Conntrollo: Logout- Reset credenziali");
			u = null;
			p= null;
			logger.log(Level.INFO, "Ricevo messaggio di logout dal client, resetto dati utente");

			idempotenza_stop = true;
		}


		if(arg[arg.length-1].equals("login") && arg[arg.length-2].equals("cmd"))
		{
			String m = message.toString();
			//System.println("login : "+ m);
			logger.log(Level.INFO, "Ricevo messaggio di login dal client, setto i dati utente");

			p = generateP(m);
			u = p.nomeUtente;

		}

	}


	public static Piano generateP(String m)  {

		JSONObject json=null;
		try {
			json = new JSONObject(m.toString());
		} catch (JSONException e) {
			e.printStackTrace();
		}
		

		Piano tmp=null;
		try {
			tmp = new Piano(json.getString("nome"), json.getString("validita"),json.getInt("ripetizioni"), json.getInt("peso"), json.getInt("serie"));
		} catch (JSONException e) {
			e.printStackTrace();
		}
		//if(tmp!=null)
			//System.println("JSON Piano: "+tmp.toString());
		return tmp;
	}


	public void setPausa(boolean setting)
	{
		m.setPausa(setting);
	}


	public boolean getFlagPull()
	{
		return m.getB();
	}


	public int getContaFC() {
		return contaFC;
	}

	public int getContaPS() {
		return contaPS;
	}

	public ArrayList<Integer> getValoriPS() {
		return valoriPS;
	}

	public ArrayList<Double> getValoriFC() {
		return valoriFC;
	}

	public int getConta()
	{
		return conta;
	}
	public void resetConta()
	{
		conta=0;
	}
	

	public void monitorExit(boolean b) {
		m.setExit(b);

	}

	public boolean getPosato()
	{
		return posato;
	}
	public void setPosato(boolean pos)
	{
		posato = pos;
	}
	public int getPeso() {
		return peso;
	}
}


