package sensori;


import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import main.Main;

public class BraccialeCallback implements MqttCallback {

	BraccialePub bp;
	Thread b;

	@Override
	public void connectionLost(Throwable arg0) {
		;
	}

	@Override
	public void deliveryComplete(IMqttDeliveryToken arg0) {
		;	
	}


	/* START {cmd:1}, STOP {cmd:0} */
	@Override
	public void messageArrived(String topic, MqttMessage message) throws Exception {

		System.out.println("--BRACCIALE-- Message arrived. Topic: " + topic + "  Message: " + message.toString());
		if(message.toString().equals("{event:1}"))
		{

			/**	bp = new BraccialePub();**/
			bp = new BraccialePub();
			b =new Thread(bp);
			Main.lista_thread.add(b);

			b.start();
		}
		if(message.toString().equals("{event:0}"))
		{
			bp.stop(); 
			System.out.println("BRACCIALE STOP");

		}
	}


}