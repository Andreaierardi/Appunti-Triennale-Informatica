package sensori;

import java.io.IOException;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.json.JSONException;

import main.Main;

public class MainS {

	public static void main(String[] args) throws MqttSecurityException, InterruptedException, MqttException, IOException, JSONException {
		/* INIT SENSORI */

		//	Main.main(args);

		Bracciale ba=new Bracciale();
		Thread br = new Thread(ba);
		
		Bilanciere bl = new Bilanciere();
		Thread bil = new Thread(bl);

		Pesi p = new Pesi();
		Thread ps = new Thread(p);


		Main.lista_thread.add(br);
		Main.lista_thread.add(bil);
		Main.lista_thread.add(ps);


		ps.start();
		br.start();
		bil.start();
		System.out.println("SUB COMPLETE BY CONTROLLO");

		try {
			br.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		try {
			bil.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		try {
			ps.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	

	}

}
