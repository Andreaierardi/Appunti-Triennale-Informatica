package database;

import java.util.ArrayList;

import java.io.InputStream;
import java.security.KeyStore;
import java.security.SecureRandom;
import java.security.cert.Certificate;
import java.security.cert.CertificateFactory;

import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManagerFactory;

//8883 porta per crittografia. Certificati stanno in uno zip sul DIR
//Sequendo le istruzioni si fa


import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttPersistenceException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.eclipse.paho.client.mqttv3.MqttTopic;

import de.dcsquare.paho.client.util.Utils;
import smartbench.Allenamento;
import smartbench.Piano;

public class GestoreDBPub implements Runnable{

	ArrayList<Allenamento> allenamenti;
	Allenamento allenamento_singolo;
	String topic;
	String broker;
	private MqttClient client;
	String login;
	Object input;
	String utente;
	
	
	public GestoreDBPub() throws Exception
	{
		/**DA CONTROLLARE BENE IL TOPIC**/
		topic = MainDB.TOPIC_PUB_DB;
		
		broker = MainDB.BROKER_CLOUD;

		MqttConnectOptions options = new MqttConnectOptions();
			SSLSocketFactory socketFactory = getSocketFactory("ca.crt");
		options.setSocketFactory(socketFactory);

		String clientId = Utils.getMacAddress()+"wr-pub"+System.currentTimeMillis();

		try {

			client = new MqttClient(broker, clientId);

		} catch (MqttException e) {
			e.printStackTrace();
			System.exit(1);
		}
		options.setCleanSession(false);
		options.setWill(client.getTopic("home/LWT"), "I'm gone :(".getBytes(), 0, false);
		client.connect(options);	
	}
	
	private static SSLSocketFactory getSocketFactory(String certificateName) throws Exception {
	      // Load the certificate from src/main/resources and create a Certificate object
	  		InputStream certStream = GestoreDBPub.class.getClassLoader().getResourceAsStream(certificateName);
	  		CertificateFactory certFactory = CertificateFactory.getInstance("X509");
	      Certificate certificate =  certFactory.generateCertificate(certStream);
	      SSLContext sslContext = SSLContext.getInstance("TLSv1.2");
	      TrustManagerFactory trustManagerFactory = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm());
	  		KeyStore keyStore = KeyStore.getInstance(KeyStore.getDefaultType());
	  		keyStore.load(null);
	  		keyStore.setCertificateEntry("alias", certificate);
	  		trustManagerFactory.init(keyStore);
	  		sslContext.init(null, trustManagerFactory.getTrustManagers(), new SecureRandom());
	  		return sslContext.getSocketFactory();
	    }
	
	@Override
	public void run() {

		try {
			pub(input);
		} catch (MqttException e) {
			e.printStackTrace();
		}



	}

	@SuppressWarnings("unchecked")
	private void pub(Object all) throws MqttSecurityException, MqttException {
	

		try {
			
			if(all.getClass().toString().equals("class java.lang.String"))
			{
				if(all.toString().equals("wrcheck"))
					publishACK((String) all);
				if(all.toString().equals("ERRORE"))
					publishErrore((String) all); 
				if(!all.toString().equals("wrcheck"))
						publishLogin((String)all);
			}

			if(all.getClass().toString().equals("class smartbench.Allenamento"))
				publishAllenamento((Allenamento) all);
		
			if(all.getClass().toString().equals("class java.util.ArrayList"))
			{
				ArrayList<Object> tmp = (ArrayList<Object>) all;
				
				if(tmp.size()==0)
				{
					publishErrore("ERRORE");
					return;
				}
				
				if(tmp.get(0).getClass().toString().equals("class smartbench.Piano"))
							publishPiani((ArrayList<Piano>) all);
				
				else if(tmp.get(0).getClass().toString().equals("class smartbench.Allenamento"))
						publishAllenamenti((ArrayList<Allenamento>) all);
			}
			if(all.getClass().toString().equals("class smartbench.Piano"))
				publishPiano((Piano) all);

		}
		catch(java.lang.NullPointerException e)
		{
			//System.println("ERRORE, oggetto non trovato");
			publishErrore("ERRORE");
		}


	}
	private void publishACK(String check) throws MqttPersistenceException, MqttException {
		String tmpTopic =  MainDB.TOPIC_PUB_DB_4+"/";
		final MqttTopic br = client.getTopic(tmpTopic);
		br.publish(new MqttMessage(check.getBytes()));
		//System.println("ACK DB:  Topic: "+br.getName()+ " MESSAGGIO: "+check);
		
	}
	private void publishPiani(ArrayList<Piano> p) throws MqttPersistenceException, MqttException {

		String tmpTopic =  MainDB.TOPIC_PUB_DB_4+"/visualizza_piani";
		String m = new String();
		for (Piano s : p)
		{
			m += s.toString()+"\n"+"-";
			//System.println(s.toString());
		}
		final MqttTopic br = client.getTopic(tmpTopic);
		
		if(m.length()>1)
		{
			br.publish(new MqttMessage(m.substring(0, m.length()-1).getBytes()));
			//System.println("Piani ricercati PUB:  Topic: "+br.getName()+ " MESSAGGIO: "+m);

		}
		else
		{
			br.publish(new MqttMessage((new String("ERRORE, allenamenti non trovati").getBytes())));
			//System.println("Piani ricercati ERRORE!");

		}

		//System.println("Ricerca piani PUB:  Topic: "+br.getName()+ " MESSAGGIO: "+m);

	}
	private void publishPiano(Piano piano) throws MqttPersistenceException, MqttException {

		String tmpTopic = MainDB.TOPIC_PUB_DB_4+"/ricerca_ultimo_piano";
		String m = piano.toString();
		final MqttTopic br = client.getTopic(tmpTopic);
		br.publish(new MqttMessage(m.getBytes()));
		//System.println("Ultimo piano PUB:  Topic: "+br.getName()+ " MESSAGGIO: "+m);

	}
	private void publishAllenamento(Allenamento alle) throws MqttPersistenceException, MqttException {

		String tmpTopic = MainDB.TOPIC_PUB_DB_4+"/ricerca_ultimo_all";
		String m = alle.toString();
		final MqttTopic br = client.getTopic(tmpTopic);
		br.publish(new MqttMessage(m.getBytes()));
		//System.println("Ultimo allenamento PUB:  Topic: "+br.getName()+ " MESSAGGIO: "+m);

	}
	private void publishAllenamenti(ArrayList<Allenamento> a) throws MqttPersistenceException, MqttException {

		String tmpTopic =  MainDB.TOPIC_PUB_DB_4+"/ricerca_all";
		String m = new String();
		for (Allenamento s : a)
		{
			m += s.toString()+"\n"+"-";
			//System.println(s.toString());
		}


		final MqttTopic br = client.getTopic(tmpTopic);
		if(m.length()>1)
		{
			br.publish(new MqttMessage(m.substring(0, m.length()-1).getBytes()));
			//System.println("Allenamenti ricercati PUB:  Topic: "+br.getName()+ " MESSAGGIO: "+m);

		}
		else
		{
			br.publish(new MqttMessage((new String("ERRORE, allenamenti non trovati").getBytes())));
			//System.println("Allenamenti ricercati ERRORE!");

		}


	}
	
	
	private void publishErrore(String all) throws MqttPersistenceException, MqttException {

		String tmpTopic = MainDB.TOPIC_PUB_DB_4+"/errore";
		String m = all;
		final MqttTopic br = client.getTopic(tmpTopic);
		br.publish(new MqttMessage(m.getBytes()));
		//System.println("PUB ERRORE AL CLIENT==>  Topic: "+br.getName()+ " MESSAGGIO: "+m);

	}
	
	
	private void publishLogin(String all) throws MqttPersistenceException, MqttException {

		String tmpTopic = topic+"/response";
		String m = all;
		final MqttTopic br = client.getTopic(tmpTopic);
		br.publish(new MqttMessage(m.getBytes()));
		//System.println("Login PUB:  Topic: "+br.getName()+ " MESSAGGIO: "+m);
		
		String tmpTopic2 = MainDB.TOPIC_PUB_DB_4+"/utente";
		String m2 = utente;
		final MqttTopic br2 = client.getTopic(tmpTopic2);
		br2.publish(new MqttMessage(m2.getBytes()));
		//System.println("Login PUB:  Topic: "+br2.getName()+ " MESSAGGIO: "+m2);
		
		Piano p = DB_Piani.ricercaUltimoPiano(utente);
		String tmpTopic3 = MainDB.TOPIC_PUB_DB_2;
		String m3 = p.toJson();
		final MqttTopic br3 = client.getTopic(tmpTopic3);
		br3.publish(new MqttMessage(m3.getBytes()));
		//System.println("Login PUB:  Topic: "+br3.getName()+ " MESSAGGIO: "+m3);
	
		

	}
	
	
	public void setAllenamento(Allenamento alle) {

		input = alle;

		allenamento_singolo= alle;
	}
	public void setAllenamenti(ArrayList<Allenamento> amt) {

		input = amt;
		allenamenti = amt;

	}

	public void setLogin(Account act) {
		//System.println("CCC" +act==null);
		if(act==null)
		{	//System.println("IMPOSTO INPUT A NO");
		input = "NO";
		}
		else
		{
			input = "OK, "+act.tipo;
			utente = act.username;
			//System.println("IMPOSTO INPUT A OK E AGGIUNGO TIPO: "+act.tipo);
		}

	}
	
	public void setPiani(ArrayList<Piano> piani) {

		input=piani;
	}
	public void setPiano(Piano p) {

		input = p;
	}
	public void setACK(String string) {
		input = string;
		
	}

}
