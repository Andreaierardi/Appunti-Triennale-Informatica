package sensori;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import main.Main;

public class PesiCallback implements MqttCallback{

	PesiPub pp;
	Thread p;
	private int CurrentW=Main.defaultW;

	@Override
	public void connectionLost(Throwable arg0)
	{
		;
	}

	@Override
	public void deliveryComplete(IMqttDeliveryToken arg0) 
	{
		;	
	}


	/* AGGIORNO PESO {cmd:number}, INVIO PESO {cmd:2} */
	@Override
	public void messageArrived(String topic, MqttMessage message) throws Exception {

		System.out.println("--PESI-- Message arrived, Topic: " + topic + "  Message: " + message.toString());

		String[] event = message.toString().substring(1).split(":");
		String tmp = event[1].substring(0,event[1].length()-1);
		int check = Integer.parseInt(tmp);

		if(event[0].equals("event") && check>=5)
		{
			System.out.println("SETTO Peso ricevuto"+ tmp);
			CurrentW=Integer.parseInt(tmp);
		}
		if(message.toString().equals("{event:2}"))
		{
			System.out.println("MANDO PESO A CONTROLLO: "+CurrentW);
			/**	pp = new PesiPub(CurrentW); **/
			pp = new PesiPub(CurrentW);
			p =new Thread(pp);
			Main.lista_thread.add(p);

			p.start();
		}

	}

	public void setW(int w) {

		CurrentW = w;
	}

}