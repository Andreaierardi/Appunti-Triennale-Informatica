package sensori;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;

import de.dcsquare.paho.client.util.Utils;
import main.Main;

public class Bracciale implements Runnable {
	
	
	
	public String topic;  // "from/retilab/reti8/gpio/OUT4";
	public String broker; //"tcp://reti8.edu-al.unipmn.it";
	
	private static MqttClient mqttClient;

	BraccialeCallback bcc;
	
	/** public Bracciale() **/
	public Bracciale()
	{
		
		topic = Main.TOPIC_SUB_BRACCIALE;
		broker = Main.BROKER_BB;
		String clientId = Utils.getMacAddress()+"br-sub"+System.currentTimeMillis();
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

	public void sub() throws InterruptedException {
		try
		{
			bcc = new BraccialeCallback();
			mqttClient.setCallback(bcc);
			mqttClient.connect();

			//Subscribe to all subtopics of home
			mqttClient.subscribe(topic);

			System.out.println("BRACCIALE is now listening to "+topic);

		}
		catch (MqttException e) 
		{
			e.printStackTrace();
			System.exit(1);
		}
	
	}

	@Override
	public void run() {
		try {
			sub();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
	}

	public static void disconnect() throws MqttException {
		mqttClient.disconnect();
		
	}

	public static void connect() throws MqttSecurityException, MqttException {
		mqttClient.connect();
		
	}


}
