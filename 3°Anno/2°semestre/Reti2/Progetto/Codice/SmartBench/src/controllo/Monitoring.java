package controllo;

import java.util.concurrent.TimeUnit;
import java.util.logging.Level;
import java.util.logging.Logger;

import main.Main;

public class Monitoring implements Runnable{

	int tempo;
	boolean flagPull;
	private boolean pausa;
	private boolean exit=true;
	public int time_bil;
	private Logger logger;

	public Monitoring(int index)
	{
		
		tempo = index;
		time_bil = Main.time_bil;
		flagPull = true;
		logger = Main.logger;
	}

	@Override
	public void run() {

		try {
			monitora();
		} 
		catch (InterruptedException e) {}
	}


	private void monitora() throws InterruptedException {
		
		System.out.println("Inizio monitoring...\n "
				+ "Monitoro per "+ time_bil+"secondi");
		logger.log(Level.INFO, "Inizio il monitoring del bilanciere ogni "+time_bil+" secondi");

		while(exit && tempo<time_bil )
		{
			if(!exit)
				break;
			TimeUnit.SECONDS.sleep(1);
			System.out.println("\n\n\n -----MONITORING: "+tempo+"!!------\n\n");
			while(exit && pausa && !(Main.reset==1) ) 
			{
				if(!exit)
					break;
				System.out.println("PAUSA MONITORAGGIO");
				tempo= 0;
				TimeUnit.SECONDS.sleep(2);
				
			}
			tempo++;

		}
		tempo= 0;
		if(exit && Main.reset!=1)
		{
			logger.log(Level.WARNING, "Il monitoraggio ha rilevato una situazione critica");

			System.out.println("FlagPull settato a false. Fine monitoring");
			flagPull = false;
		}
	}

	public boolean getB()
	{
		return flagPull;
	}

	public void resetJ()
	{
		tempo = 0 ;
	}
	public void setPausa(boolean setting) {
		pausa = setting	;
	}
	public void setExit(boolean b) {
		exit = b;	
	}
}
