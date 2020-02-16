package sensori;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;

import de.dcsquare.paho.client.util.Utils;
import main.Main;

public class Pesi implements Runnable {



	public String topic;// = "from/retilab/reti8/gpio/OUT4";
	public String broker;//="tcp://reti8.edu-al.unipmn.it";

	private static MqttClient mqttClient;
	PesiCallback bcc;

	/**	public Pesi() **/
	public Pesi()
	{


		topic = Main.TOPIC_SUB_PESI;
		broker = Main.BROKER_BB;

		String clientId = Utils.getMacAddress()+"ps-sub"+System.currentTimeMillis();
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
			bcc = new PesiCallback();
			mqttClient.setCallback(bcc);
			mqttClient.connect();

			mqttClient.subscribe(topic);

			System.out.println("PESI is now listening to "+topic);

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
