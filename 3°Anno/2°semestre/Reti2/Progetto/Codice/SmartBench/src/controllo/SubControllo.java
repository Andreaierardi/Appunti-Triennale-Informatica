package controllo;

import java.util.logging.Level;
//import java.util.logging.Level;
import java.util.logging.Logger;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;

import de.dcsquare.paho.client.util.Utils;
import main.Main;

public class SubControllo implements Runnable {

	private static MqttClient mqttClient;
	public String topic;
	public String broker;
	Logger logger;

	
	public SubControllo() {


		logger  = Main.logger;
		topic =Main.TOPIC_SUB_CONTROLLO;
		broker = Main.BROKER_BB;

		String clientId = Utils.getMacAddress()+System.currentTimeMillis();
		try
		{
			mqttClient = new MqttClient(broker, clientId);
		}
		catch (MqttException e)
		{
			e.printStackTrace();
			System.exit(1);
		}	

	}

	public void sub() {
		try
		{
			mqttClient.setCallback(new SubControlloCallback() );
			Main.lista_reset.add(this);
			mqttClient.connect();
			mqttClient.subscribe(topic);
			logger.log(Level.INFO, "Sub al topic '"+topic+ "' by publisher "+this.getClass().getName());

			//System.println("SUB Controllo is now listening to "+topic);

		}
		catch (MqttException e) 
		{
			e.printStackTrace();
			System.exit(1);
		}

	}

	public static void disconnect() throws MqttException
	{
		mqttClient.disconnect();
	}
	@Override
	public void run() 
	{
		sub();		

	}

	public static void connect() throws MqttSecurityException, MqttException {
		mqttClient.connect();
		
	}

}
