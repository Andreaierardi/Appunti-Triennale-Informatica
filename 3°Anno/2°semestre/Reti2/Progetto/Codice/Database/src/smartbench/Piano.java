package smartbench;

import java.util.ArrayList;

public class Piano {

	public String nomeUtente;
	public String validita;
	public int totRip;
	public int peso;
	public int serie;

	public Piano(String utente, String val, int rip, int p, int s) {
		nomeUtente = utente;
		validita= val;
		totRip = rip;
		peso = p;
		serie = s;
	}

	public Piano(String completo)
	{
		String [] split = completo.split(";");
		ArrayList<String> tmp = new ArrayList<String>();
		for(String s : split)
		{
			String [] sep = s.split(":");
			tmp.add(sep[1]);
		}

		nomeUtente = tmp.get(0);
		validita= tmp.get(1);

		totRip = Integer.parseInt(tmp.get(2).trim());
		peso = Integer.parseInt(tmp.get(3).trim());
		serie = Integer.parseInt(tmp.get(4).trim());

	}

	public Piano()
	{

	}

	public String toString() {

		return "Nome: "+nomeUtente+
				"; Validita': "+validita+
				"; Ripetizioni da fare: "+totRip+
				"; Peso consigliato: "+peso+ 
				"; Numero di serie totali: "+serie;
	}

	public String toJson()
	{
		return "{\"nome\":"+"\""+nomeUtente+"\""+
				", \"validita\":"+"\""+validita+"\""+
				", \"ripetizioni\":"+"\""+totRip+"\""+
				", \"peso\":"+"\""+peso+"\""+
				", \"serie\":"+"\""+serie+"\" }";
	}
}