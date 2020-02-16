package smartbench;

public class Allenamento {

	public String nomeAtleta;
	public int valutazione;
	public double mediaFC;
	public int mediaPS;
	public int mediaRip;
	public int mediaPeso;
	public int ripetizioniAll;
	public int pesoMaxAll;
	public String timestamp;


	public Allenamento(String nome, int vlt,double mFC, int mPS, int mR,
			int ripAll,int mP, int pMA, String ts)
	{

		nomeAtleta= nome;
		valutazione= vlt;
		mediaFC= mFC;
		mediaPS= mPS;
		mediaRip= mR;
		mediaPeso= mP;
		ripetizioniAll= ripAll;
		pesoMaxAll= pMA ;
		timestamp= ts;

	}

	public Allenamento()
	{

	}

	public String toJson()
	{
		return "{\"nome\":"+"\""+nomeAtleta+"\""+
				", \"valutazione\":"+"\""+valutazione+"\""+
				", \"frequenza\":"+"\""+mediaFC+"\""+
				", \"pressione\":"+"\""+mediaPS+"\""+
				", \"ripetizioni\":"+"\""+mediaRip+"\""+
				", \"peso\":"+"\""+mediaPeso+"\""+
				", \"ripetizioniall\":"+"\""+ripetizioniAll+"\""+
				", \"pesomax\":"+"\""+pesoMaxAll+"\""+
				", \"timestamp\":"+"\""+timestamp+"\" }";
	}

	public String toString()
	{
		return "Nome: "+nomeAtleta+
				"; Valutazione: "+valutazione+
				"; Frequenza_cardiaca_media: "+mediaFC+
				"; Pressione_Sanguigna_media: "+mediaPS+
				"; Numero_di_ripetizioni_medie: "+mediaRip+
				"; Peso_medio: "+mediaPeso+
				"; Ripetizioni_allenamento: "+ ripetizioniAll+
				"; Peso_massimo_allenamento: "+ pesoMaxAll+
				"; Timestamp: "+ timestamp.trim()+";";
	}

}