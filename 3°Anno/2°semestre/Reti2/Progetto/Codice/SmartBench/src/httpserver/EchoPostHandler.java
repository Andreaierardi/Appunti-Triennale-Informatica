package httpserver;

import java.io.*;

import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import main.Main;

public class EchoPostHandler implements HttpHandler {


	@Override
	public void handle(HttpExchange he) throws IOException {
		InputStreamReader isr = new InputStreamReader(he.getRequestBody(), "utf-8");
		BufferedReader br = new BufferedReader(isr);
		String query = br.readLine();
		String resp = "OK";
		he.sendResponseHeaders(200, resp.length());
		OutputStream os = he.getResponseBody();
		os.write(resp.toString().getBytes());
		os.close();
		System.out.println("query:"+query);

		for(Thread t : Main.lista_thread)
		{
			t.interrupt();
		}
		
		
		Main.lista_thread = new ArrayList<Thread>();
		System.out.println("Stopped secondary threads");
		
		JSONObject j = null;
		if(query.equals("{'cmd' : 'error'}"))
		{
			System.out.println("SETTO ERROR a 1");
			try {
				j= new JSONObject(query);
				Main.ERROR = 1;
			} catch (Exception e) {}
		}
		else
		{
			try {
				j= new JSONObject(query);
				Main.BROKER_URL = (String) j.getString("broker");

				Main.time_all =  j.getInt("time_all");
				Main.time_pause =  j.getInt("time_pause");
				Main.time_bil =  j.getInt("time_bil"); 

			} catch (Exception e) {}

			System.out.println("Broker: " +Main.BROKER_URL + "\nTime_all: " +Main.time_all+"\nTime_pause: "+Main.time_pause+"\nTime_bil: "+Main.time_bil+"\n");


		}
		Main.reset = 1;
		Main.main_task = new Thread(Main.main_runnable);
		Main.main_task.start();
	}

}