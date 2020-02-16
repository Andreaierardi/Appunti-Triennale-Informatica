package sensori;

import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilderFactory;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttPersistenceException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.eclipse.paho.client.mqttv3.MqttTopic;
import org.w3c.dom.NodeList;

import de.dcsquare.paho.client.util.Utils;
import main.Main;

import javax.xml.parsers.DocumentBuilder;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import java.io.File;

public class BraccialePub implements Runnable {


	public String topic;//= "to/retilab/reti8/gpio/OUT";
	
	public static String broker;//= "tcp://193.206.55.23:1883";

	public ArrayList<String> fr;
	public ArrayList<String> pr;
	
	public volatile boolean flag;
	private MqttClient client;
	
	public final String file = "src/XML/bracciale.xml";

	private int time;
	
	public BraccialePub() throws MqttSecurityException, MqttException {
		
		time = Main.Time_br;
		topic = Main.TOPIC_PUB_BRACCIALE;
		broker = Main.BROKER_BB;
		String clientId = Utils.getMacAddress()+"br-pub"+System.currentTimeMillis();
		fr=new ArrayList<String>();
		pr=new ArrayList<String>();
		

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

	public void pub(String nomeF) throws MqttSecurityException, MqttException {
			
			if(!leggi_file(nomeF))
				System.out.println("FILE NOT FOUND\n");
			
			try {
				while(flag && !fr.isEmpty() &&!pr.isEmpty()) {
				
					Thread.sleep(500);
					System.out.println("FLAG BR : "+flag);
					if(!flag)
						break;
					else 
					{
						int rand = (int)(Math.random()*fr.size());
						publishBracciale(fr.remove(rand),Main.TOPIC_PUB_BRACCIALE_1);
						Thread.sleep(500);
						int rand2=  (int)(Math.random()*pr.size());
						publishBracciale(pr.remove(rand2),Main.TOPIC_PUB_BRACCIALE_2);

					}				
					Thread.sleep(time);

			}
			} catch (MqttException e) {
				e.printStackTrace();
				System.exit(1);
			} catch (InterruptedException e) {
			}

		}
		private void publishBracciale(String string, String stato) throws MqttPersistenceException, MqttException {

			String tmpTopic = stato;
			final MqttTopic br = client.getTopic(tmpTopic);
			br.publish(new MqttMessage(string.getBytes()));
			System.out.println("BRACCIALE PUB:  Topic: "+br.getName()+ " MESSAGGIO: "+string);

		}

		@Override
		public void run() {
			
			flag = true;
			try {
				pub(file);
			} catch (MqttException e) {
				e.printStackTrace();
			}
			
		}
		
		public void stop()
		{
			flag = false;
		}
		
		public boolean leggi_file(String nomefile)
		{

			int l, i;
			Node nNode;
			Element eElement;
			File fXmlFile;
			String d = null;
			String d2 = null;

			
			try
			{
				fXmlFile = new File(nomefile);
				DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
				DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
				Document doc = dBuilder.parse(fXmlFile);
				NodeList nList = doc.getElementsByTagName("data");
				l=nList.getLength();

				fr=new ArrayList<String>();
				pr=new ArrayList<String>();
				i=0;
				do
				{	

					nNode = nList.item(i);	
					if (nNode.getNodeType() == Node.ELEMENT_NODE)
					{
						eElement = (Element) nNode;
					
						if(eElement.hasAttribute("frequenza"))
						{
							d = eElement.getAttribute("frequenza");
							fr.add("{cmd:"+d.trim()+"}");

						}
						
						if(eElement.hasAttribute("pressione"))
						{
							d2 = eElement.getAttribute("pressione");
							pr.add("{cmd:"+d2.trim()+"}");
						}
					}
					i++;	
				}while(i<l);
			}

			catch (Exception e) 
			{
				e.printStackTrace();
			}

			//CHIUDI FILE
			fXmlFile=null;

			return true;
		}
	

}
