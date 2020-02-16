package controllo;

import java.util.logging.Level;
//import java.util.logging.Level;
import java.util.logging.Logger;

import main.Main;

public class Controllo implements Runnable {

	PubControllo pc;
	SubControllo subscriber;
	static String BROKER_URL;//="tcp://reti8.edu-al.unipmn.it";
	String topic;
	String broker;
	SmartBench sm;
	public boolean exit = false;
	Logger logger;

	public Controllo() throws InterruptedException
	{
		topic = "from/retilab/reti8/#";
		broker = Main.BROKER_BB;
		logger = Main.logger;

		//System.println(">>>Setto sottoclassi di controllo...");
		subscriber = new SubControllo();
		
		logger.log(Level.INFO, "Setto i parametri del controllo");

	}


	@Override
	public void run() {


		//System.println(">>>Controllo: starto thread subscriber");
		Thread cl = new Thread(subscriber);
		Main.lista_thread.add(cl);
		cl.start();
		try
		{
			cl.join();
		}
		catch (InterruptedException e) {
			e.printStackTrace();
		}
		//System.println(">>>Controllo: starto thread subscriber");
		
		logger.log(Level.INFO, "Il controllo si mette in ascolto del client");

	}


	public void setExit()
	{
		exit = true;
	}


}
