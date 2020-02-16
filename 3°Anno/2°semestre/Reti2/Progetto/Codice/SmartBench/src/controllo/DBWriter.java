package controllo;

import java.util.logging.Level;
//import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttPersistenceException;
import org.eclipse.paho.client.mqttv3.MqttTopic;

import de.dcsquare.paho.client.util.Utils;
import main.Main;
import smartbench.Allenamento;

public class DBWriter implements Runnable {
	
	String topic ;
	String broker;
	private MqttClient client;
	
	public Allenamento allenamento;
	public Logger logger;
	
	public DBWriter()
	{

		logger = Main.logger;
		logger.log(Level.INFO, "Setto i parametri per la scrittura del resoconto sul DB in cloud");
		
		broker =  Main.BROKER_CLOUD;//"tcp://193.206.55.23:1883";
		topic= Main.TOPIC_PUB_CONTROLLO;//"from/retilab/reti8/db/wr";
		//System.println("DBWRITER fork on topic: "+topic);
		logger = Main.logger;
		String clientId = Utils.getMacAddress()+"rd-pub"+System.currentTimeMillis();

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
	
	public void pub(Allenamento all) {
		
		try {
			Thread.sleep(500);

			logger.log(Level.INFO, "Pubblico il resoconto dell'allenamento al client: "+all.toJson());
			publishWriter(all);

			Thread.sleep(500);

		} catch (MqttException e) {
			e.printStackTrace();
			System.exit(1);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

	}

	private void publishWriter(Allenamento a) throws MqttPersistenceException, MqttException {

		final MqttTopic c = client.getTopic(topic);
		c.publish(new MqttMessage(a.toString().getBytes()));
		//System.println("PUBBLICO writer. Topic: "+c.getName()+ " MESSAGGIO: "+a.toString());
	}

	public void generateAll(Allenamento a)
	{
		allenamento = a;
	}
	
	@Override
	public void run() 
	{
		
		if(!allenamento.equals(null))
				pub(allenamento);
		//else
			//System.println("\n\n======ERRORE COMUNICAZIONE COL DB========\n\n");
	}
}
