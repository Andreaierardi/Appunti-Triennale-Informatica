package sensori;

import java.util.Random;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttPersistenceException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.eclipse.paho.client.mqttv3.MqttTopic;

import de.dcsquare.paho.client.util.Utils;
import main.Main;

public class BilancierePub implements Runnable {


	public String topic; //= "to/retilab/reti8/gpio/OUT2";
	public String broker;// = "tpc://reti8.edu-al.unipmn.it";

	private MqttClient client;

	public volatile boolean flag;
	public int pullNumber=0;
	private int time;

	public BilancierePub() throws MqttSecurityException, MqttException {

		topic =Main.TOPIC_PUB_BILANCIERE; 
		broker = Main.BROKER_BB;
		time= Main.Time_bl;

		String clientId = Utils.getMacAddress()+"bl-pub"+System.currentTimeMillis();

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

			while(flag) 
			{

				Thread.sleep(500);
				System.out.println("FLAG BL : "+flag);

				if(!flag)
					break;
				else
				{
					publishBilanciere("{cmd:"+1+"}");
					pullNumber+=1;
				}

				PDalgorithm();
				Thread.sleep(time);
			}


		} catch (MqttException e) {
			e.printStackTrace();
			System.exit(1);
		} catch (InterruptedException e) {
		}

	}


	private void PDalgorithm() throws MqttPersistenceException, MqttException {

		int allenamento = Main.time_all;
		int perc = allenamento /pullNumber * Main.probabilita; 
		System.out.println("RANDOM: "+allenamento+"/"+pullNumber+" * "+Main.probabilita+ "= "+perc);
		int r = new Random().nextInt(perc);
		System.out.println("Estraggo numero casuale: "+r);
		boolean val = r == 1;
		System.out.println("RANDOM: val -- "+val);
		if(val)
			publishBilanciere("{cmd:"+2+"}");


	}

	private void publishBilanciere(String string) throws MqttPersistenceException, MqttException {

		final MqttTopic bl = client.getTopic(topic);
		bl.publish(new MqttMessage(string.getBytes()));
		System.out.println("BILANCIERE PUB:  Topic: "+bl.getName()+ " MESSAGGIO: "+string);

	}

	@Override
	public void run() {
		flag = true;
		pullNumber=0;
		try {
			pub();
		} catch (MqttException e) {
			e.printStackTrace();
		}

	}

	public void stop()
	{
		flag = false;
	}

}
