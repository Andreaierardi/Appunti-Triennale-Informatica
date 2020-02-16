package controllo;

import java.util.logging.Logger;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;

import main.Main;

public class SmartBench {

	PubToClient pC;
	Thread pubClient;
	Logger logger;

	public SmartBench(PubToClient pubto)
	{
		pC = pubto;
		logger = Main.logger;
	}

	public int settaPeso(int peso) throws InterruptedException, MqttSecurityException, MqttException {

		int n = (int)(Math.random()*100);

		/**DA CAMBIARE IN PUBTOCLIENT(n)**/
		pC = new PubToClient(n,"from/retilab/reti8/client/");
		pC.setValue("setpeso:"+peso);
		pubClient= new Thread(pC);
		Main.lista_thread.add(pubClient);

		pubClient.start();
		pubClient.join();

		return peso;
	}

	public int riduciPeso(int peso) throws InterruptedException, MqttSecurityException, MqttException {
		//System.println("Riduco peso...");
		peso=peso-5;
		int n = (int)(Math.random()*1000);

		pC = new PubToClient(n,"from/retilab/reti8/client/");
		pC.setValue("riducipeso:"+peso);
		pubClient= new Thread(pC);
		Main.lista_thread.add(pubClient);

		pubClient.start();
		pubClient.join();

		return peso;
	}

	//pubblica allarme if 10 secondi senza ripetizione
	public void allarmeAtleta() throws InterruptedException, MqttSecurityException, MqttException
	{
		//System.println("ALLARME ATLETA! PERICOLO!");
		int n = (int)(Math.random()*10);

		/**DA CAMBIARE IN PUBTOCLIENT(n)**/
		pC = new PubToClient(n,"from/retilab/reti8/client/");
		pC.setValue("allarme");
		pubClient= new Thread(pC);
		Main.lista_thread.add(pubClient);

		pubClient.start();
		pubClient.join();

	}



}
