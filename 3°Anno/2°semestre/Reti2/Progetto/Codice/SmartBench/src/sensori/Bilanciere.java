package sensori;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;

import de.dcsquare.paho.client.util.Utils;
import main.Main;

public class Bilanciere implements Runnable {

	public String topic;// = "from/retilab/reti8/gpio/OUT4";
	public String broker;//= "tcp://193.206.55.23:1883";//"tcp://reti8.edu-al.unipmn.it";

	private static MqttClient mqttClient;

	int time;
	BilanciereCallback bcc;

	//	public Bilanciere(String CONT_TOPIC_SUB, String BROKER_URL/*String CONT_TOPIC_PUB, String BROKER_URL*/, int time_bl)
	public Bilanciere()
	{


		topic = Main.TOPIC_SUB_BILANCIERE;
		broker = Main.BROKER_BB;
		time = Main.Time_bl;

		String clientId = Utils.getMacAddress()+"bl-sub"+System.currentTimeMillis();
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

	public void sub() throws InterruptedException, MqttException {
		try
		{
			bcc = new BilanciereCallback();
			mqttClient.setCallback(bcc);
			mqttClient.connect();

			mqttClient.subscribe(topic);

			System.out.println("BILANCIERE is now listening to "+topic);

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
		} catch (InterruptedException | MqttException e) {
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
