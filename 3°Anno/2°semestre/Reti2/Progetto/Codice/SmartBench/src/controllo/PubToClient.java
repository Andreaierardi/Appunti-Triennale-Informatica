package controllo;

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

public class PubToClient implements Runnable{

	String topic;
	String broker;
	Logger logger;
	MqttClient client;
	String valore;

	public PubToClient(int n, String t) throws MqttSecurityException, MqttException {
		topic = t;
		broker = Main.BROKER_CLOUD;
		String clientId = Utils.getMacAddress()+"client-pub"+System.currentTimeMillis();
		logger = Main.logger;
		try {

			client = new MqttClient(broker, clientId);	
		
			logger.log(Level.INFO, "Connection by publisher "+this.getClass().getName());

		} catch (MqttException e) {
			//e.printStackTrace();
			//System.exit(1);
		}
		
		MqttConnectOptions options = new MqttConnectOptions();
		options.setCleanSession(false);
		options.setWill(client.getTopic("home/LWT"), "I'm gone :(".getBytes(), 0, false);
		client.connect(options);
	}


	@Override
	public void run() {
		pub(valore);

	}
	
	public void pub(String response) 
	{
		try {

			Thread.sleep(1000);
			logger.log(Level.INFO, "Invio messaggio dal Controllo al Client: "+response); 

			publishResp(response);
			Thread.sleep(1000);

		} catch (MqttException e) {
			//e.printStackTrace();
			//System.exit(1);
		} catch (InterruptedException e) {
			//e.printStackTrace();
		}

	}

	private void publishResp(String response) throws MqttPersistenceException, MqttException {

		final MqttTopic c = client.getTopic(topic);
		c.publish(new MqttMessage(response.getBytes()));
		//System.println("PUBLISH... Source: PubToClient. Topic: "+c.getName()+ " MESSAGGIO: "+response);
	}
	
	public void setValue(String v)
	{
		valore = v;
	}


}
