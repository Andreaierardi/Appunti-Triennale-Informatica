package database;

import java.util.ArrayList;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import smartbench.*;

public class GestoreDBCallback implements MqttCallback {
	Allenamento a;
	GestoreDBPub gDBp ;
	Account act;
	Thread gestore2;

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


	@Override
	public void messageArrived(String topic, MqttMessage message) throws Exception {

		String arg [] = topic.split("/");

		System.out.println("Gestore : RICEVO MESSAGGIO "+message.toString()+"\nTopic: "+topic);

		if(arg[arg.length-1].equals("wr"))
		{

			ArrayList<String> tmp = new ArrayList<String>();

			String[] list = message.toString().split(" ");
			for(int i = 0 ; i<list.length; i++)
			{
				if(i%2!=0)
					tmp.add(list[i].substring(0, list[i].length()-1));
			}
			System.out.println("\n<GESTOREDB>-- Scrivo nel db"+"\n\n "+message.toString());

			a = new Allenamento(tmp.get(0), Integer.parseInt(tmp.get(1)), 
					Double.parseDouble(tmp.get(2)), Integer.parseInt(tmp.get(3)),
					Integer.parseInt(tmp.get(4)),Integer.parseInt(tmp.get(5)), 
					Integer.parseInt(tmp.get(6)), Integer.parseInt(tmp.get(7)), tmp.get(8));

			gDBp = new GestoreDBPub();
			gestore2 = new Thread(gDBp);
			MainDB.lista_thread.add(gestore2);

			if(DB_Allenamenti.pubblicaNuovoAllenamento(a))
			{
				System.out.println("Allenamento scritto con successo");
				gDBp.setAllenamento(a);
			}


			else
			{
				System.out.println("ERRORE Scrittura allenamento sul DB");
				gDBp.setAllenamento(null);
				System.out.println("ERRORE di scrittura inviato");

			}
			gestore2.start();
			gestore2.join();

		}


		if(arg[arg.length-2].equals("ricerca_all"))
		{
			String usr = arg[arg.length-1];
			ArrayList <Allenamento> amt= DB_Allenamenti.ricercaAllenamenti(usr);
			gDBp = new GestoreDBPub();
			Thread gestore = new Thread(gDBp);
			MainDB.lista_thread.add(gestore);

			gDBp.setAllenamenti(amt);
			gestore.start();
			gestore.join();

		}


		if(arg[arg.length-2].equals("ricerca_ultimo_all"))
		{
			String usr = arg[arg.length-1];
			Allenamento a= DB_Allenamenti.ricercaUltimoAllenamento(usr);
			gDBp = new GestoreDBPub();
			Thread gestore = new Thread(gDBp);
			MainDB.lista_thread.add(gestore);

			gDBp.setAllenamento(a);
			gestore.start();
			gestore.join();

		}


		if(arg[arg.length-2].equals("ricerca_ultimo_piano"))
		{
			String usr = arg[arg.length-1];
			Piano p= DB_Piani.ricercaUltimoPiano(usr);
			gDBp = new GestoreDBPub();
			Thread gestore = new Thread(gDBp);
			MainDB.lista_thread.add(gestore);

			gDBp.setPiano(p);
			gestore.start();
			gestore.join();

		}

		if(arg[arg.length-1].equals("login"))
		{

			String []s= message.toString().split(":");
			if(s[0].equals("check"))
			{
				String[] parametri= s[1].split(",");
				String p1 = parametri[0].trim();
				String p2 = parametri[1].trim();
				act = DB_utenti.login(p1,p2); 
			}

			gDBp = new GestoreDBPub();
			Thread gestore = new Thread(gDBp);
			MainDB.lista_thread.add(gestore);

			if(act==null)
			{
				gDBp.setLogin(null);
				gestore.start();
			}

			else
			{
				gDBp.setLogin(act);
				gestore.start();
			}
		}


		if(arg[arg.length-1].equals("nuovopiano"))
		{
			String[] p= message.toString().split(":");
			if(p[0].equals("nuovopiano"))
			{

				String[]param= p[1].split(",");
				String user=param[0].trim();
				String val= param[1].trim();
				Integer totRip= Integer.parseInt(param[2].trim());
				Integer peso=Integer.parseInt(param[3].trim());
				Integer serie=Integer.parseInt(param[4].trim());
				Piano p1= new Piano(user,val,totRip,peso, serie);
				boolean ack = DB_Piani.pubblicaNuovoPiano(p1, user);

				gDBp = new GestoreDBPub();
				gestore2 = new Thread(gDBp);
				MainDB.lista_thread.add(gestore2);

				if(ack)
				{
					gDBp.setACK("wrcheck");
					System.out.println("ACK Scrittura");
				}
				else
				{
					gDBp.setACK("ERRORE");
					System.out.println("ERRORE di scrittura inviato");

				}
				gestore2.start();
				gestore2.join();
			}
		}


		if(arg[arg.length-1].equals("visualizza_piani"))
		{
			String[]s= message.toString().split(":");
			String username= s[1].trim();
			ArrayList<Piano> piani= DB_Piani.ricercaPiani(username);
			gDBp = new GestoreDBPub();
			Thread gestore = new Thread(gDBp);
			MainDB.lista_thread.add(gestore);

			gDBp.setPiani(piani);
			gestore.start();
			gestore.join();
		}
	}

}
