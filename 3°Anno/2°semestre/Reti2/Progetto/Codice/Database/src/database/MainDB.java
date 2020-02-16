package database;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.security.KeyManagementException;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.cert.CertificateException;
import java.util.ArrayList;

import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttSecurityException;
import org.json.JSONException;
import org.json.JSONObject;



public class MainDB {

	
	public static String BROKER_CLOUD;
	public static String BROKER_BB;
	public static String BROKER_URL;

	public static Thread main_task;
	public static Runnable main_runnable;
	public static String TOPIC_PUB_DB;
	public static String TOPIC_PUB_DB_2;
	public static String TOPIC_PUB_DB_3;
	public static String TOPIC_PUB_DB_4;
	static String TOPIC_SUB_DB;
	public static String TOPIC_PUB_CLIENT;
	public static String TOPIC_PUB_TO_CLIENT_2;
	public static String TOPIC_SUB_CLIENT;
	public static ArrayList<Thread> lista_thread = new ArrayList<Thread>();
	
	public static void main(String[] args) throws MqttSecurityException, InterruptedException, MqttException, IOException, JSONException  {
		/* INIT DB*/
		parseJSON("topic.json");

		
		//Main.main(args);
		

		GestoreDB gDB = null;
		MainDB.BROKER_CLOUD = "ssl://iotlabgw.edu-al.unipmn.it:8883";
		BROKER_URL = BROKER_CLOUD;
		System.out.println("MAIN: "+BROKER_URL);
		try {
			gDB = new GestoreDB();
		} catch (KeyManagementException | NoSuchAlgorithmException | KeyStoreException | CertificateException
				| IOException e2) {
			// TODO Auto-generated catch block
			e2.printStackTrace();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Thread db = new Thread(gDB);
		db.start();
		try {
			db.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	public static void parseJSON(String nomefile) throws JSONException
	{
		String result = "";
		try {
			BufferedReader br = new BufferedReader(new FileReader(nomefile));
			StringBuilder sb = new StringBuilder();
			String line = br.readLine();
			while (line != null) {
				sb.append(line);
				line = br.readLine();
			}
			br.close();
			result = sb.toString();
		} catch(Exception e) {
			e.printStackTrace();
		}

		JSONObject object = new JSONObject(result);
		BROKER_CLOUD = object.getString("BROKER_CLOUD");

		BROKER_BB = object.getString("BROKER_BB");
		
	


		/* TOPIC DEL DATABASE*/
		TOPIC_PUB_DB =object.getString("TOPIC_PUB_DB");
		TOPIC_PUB_DB_2 =object.getString("TOPIC_PUB_DB_2"); 
		//"from/retilab/reti8/login";
		TOPIC_PUB_DB_3 = object.getString("TOPIC_PUB_DB_3");
		//"from/retilab/reti8/logout";

		TOPIC_PUB_DB_4 = object.getString("TOPIC_PUB_DB_4");
		//"from/retilab/reti8/client/risposta"
		TOPIC_SUB_DB = object.getString("TOPIC_SUB_DB");
		//"from/retilab/reti8/db/#";

		/* TOPIC DEL CLIENT */
		TOPIC_PUB_CLIENT= object.getString("TOPIC_PUB_CLIENT");
		//"from/retilab/reti8/db";
		TOPIC_PUB_TO_CLIENT_2 = object.getString("TOPIC_PUB_TO_CLIENT_2");

		TOPIC_SUB_CLIENT = object.getString("TOPIC_SUB_CLIENT");
		//"from/retilab/reti8/client/#";
	}
	

}