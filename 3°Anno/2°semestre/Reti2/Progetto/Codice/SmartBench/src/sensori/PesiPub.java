package sensori;

import java.util.ArrayList;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttPersistenceException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.eclipse.paho.client.mqttv3.MqttTopic;


import de.dcsquare.paho.client.util.Utils;
import main.Main;

public class PesiPub implements Runnable{

	public String topic; // = "to/retilab/reti8/gpio/OUT3";
	public String broker; 
		
	public volatile boolean flag;
	private MqttClient client;
	
	public ArrayList<String> p;
	
	private int w;
	
	public  PesiPub(int weight) throws MqttSecurityException, MqttException {
		
		w = weight;
		topic = Main.TOPIC_PUB_PESI;
		broker = Main.BROKER_BB;
		
		String clientId = Utils.getMacAddress()+"ps-pub"+System.currentTimeMillis();
		p=new ArrayList<String>();

		try {

			client = new MqttClient(broker, clientId);

		} catch (MqttException e) {
			e.printStackTrace();
			System.exit(1);
		}
		MqttConnectOptions options = new MqttConnectOptions();
		options.setCleanSession(false);
		options.setWill(client.getTopic("home/LWT"), "I'm gone :(".getBytes(), 0, false);
		client.connect(options);
		
	}

	public void pub() throws MqttSecurityException, MqttException {
		
			
			
			try {
				if(flag) {
				
					Thread.sleep(500);
					System.out.println("FLAG PESI : "+flag);
					publishPesi(w);

			}
				

			} catch (MqttException e) {
				e.printStackTrace();
				System.exit(1);
			} catch (InterruptedException e) {
			}

		}
		private void publishPesi(int we) throws MqttPersistenceException, MqttException {

			String string = "{cmd:"+we+"}";

			final MqttTopic ps = client.getTopic(topic);
			ps.publish(new MqttMessage(string.getBytes()));
			System.out.println("PESI PUB:  Topic: "+ps.getName()+ " MESSAGGIO: "+string);

		}

		@Override
		public void run() {
			
			flag = true;
			try {
				pub();
			} catch (MqttException e) {
				e.printStackTrace();
			}
			
		}
		


	
}
