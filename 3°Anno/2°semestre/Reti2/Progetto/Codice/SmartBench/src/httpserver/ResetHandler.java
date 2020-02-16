package httpserver;

import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;

import controllo.PubToClient;
import controllo.SubControllo;
import main.Main;
import sensori.Bilanciere;
import sensori.Bracciale;
import sensori.Pesi;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;


public class ResetHandler implements HttpHandler {

	PubToClient pc;
	
	@Override
	public void handle(HttpExchange he) throws IOException{
		System.out.println("Reset signal received");
		String resp = "OK";
		he.sendResponseHeaders(200, resp.length());
		OutputStream os = he.getResponseBody();
		os.write(resp.toString().getBytes());
		os.close();
		
		try {
			SubControllo.disconnect();
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		try {
			Bracciale.disconnect();
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			Bilanciere.disconnect();
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			Pesi.disconnect();
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		for(Thread t : Main.lista_thread)
		{
			

			
			t.interrupt();
			System.out.println("NAME T: "+t.getName()+ " -- ID : "+t.getId());

		}
		
		
		Main.lista_thread = new ArrayList<Thread>();
		System.out.println("Stopped secondary threads");
		
		Main.main_task.interrupt();
		System.out.println("Stopped main task");
		
		System.out.println("SET Variabili main");
		Main.BROKER_URL= "193.206.55.23";
		Main.time_all=60;
		Main.time_pause=60;
		Main.time_bil=10;
		
		System.out.println("Variabili settate a default");
		System.out.println("valori settati{\n BROKER_URL: "+Main.BROKER_URL+"\ntime_all: "+Main.time_all+"\ntime_pause: "+Main.time_pause+"\ntime_bil: "+Main.time_bil+"\n");
		Main.main_task = new Thread(Main.main_runnable);
		
		try {
			SubControllo.connect();
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			Bracciale.connect();
		} catch (MqttSecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			Bilanciere.connect();
		} catch (MqttSecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			Pesi.connect();
		} catch (MqttException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Main.main_task.start();
		
		Main.reset= 1;
		System.out.println("System has been restarted successfully");
	}
	
}
