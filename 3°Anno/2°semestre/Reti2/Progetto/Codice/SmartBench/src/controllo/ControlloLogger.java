package controllo;

import java.io.IOException;
import java.util.logging.*;
public class ControlloLogger   {


	@SuppressWarnings("unused")
	private final static Logger logger = Logger.getLogger(ControlloLogger.class.getName());
	private static FileHandler fh = null;

	/* Type of loggin: OFF,SEVERE,WARNING,INFO, 
	 * CONFIG,FINE,FINER,FINEST,ALL */
	
	public static void init() {

		try {
			fh=new FileHandler("logfile.log", true);
		} catch (SecurityException | IOException e) {
			e.printStackTrace();
		}
		Logger l = Logger.getLogger("");
		fh.setFormatter(new SimpleFormatter());
		l.addHandler(fh);
		l.setLevel(Level.CONFIG);
	}


}
