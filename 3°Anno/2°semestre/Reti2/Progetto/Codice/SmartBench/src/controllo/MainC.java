package controllo;

import java.io.IOException;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.json.JSONException;

import main.Main;

//import main.Main;

public class MainC {
	public static void main(String[] args) throws MqttSecurityException, InterruptedException, MqttException, IOException, JSONException  {

		//Main.main(args);

		/*INIT CONTROLLO */
		Controllo c =null;
		try {
			c = new Controllo();
		} catch (InterruptedException e1) {
			e1.printStackTrace();
		}

		Thread cons = new Thread(c);
		Main.lista_thread.add(cons);
		cons.start();

	}
}
