package atletica;

import java.util.ArrayList;

public class Atletica {

	//Campi per applicare l'algoritmo del MSI
	private int[] A;
	//ArrayList che contiene le posizioni dei numeri della soluzione ottimale nell'array rend1 o rend2
	private ArrayList<Integer> S;
	
	//Campo utile per poter utilizzare il numero di discipline della gara
	private int num;

	
	//Costruttore della classe
	public Atletica(int numeroDiscipline)
	{
		num= numeroDiscipline;
	}
	
	//L'algoritmo utilizzato è quello del MSI
	//Si utilizza questo algoritmo poichè come chiedo in consegna bisogna considerare risultati di prove non consecutive.
	
	//L'unico cambiamento da applicare all'algoritmo è l'utilizzo della variabile somma che tiene conto della somma dei valori della soluzione ottimale per poterla confrontare con quella del secondo atleta
	private int msi(int rend[])
	{
		int somma = 0 ;
		A = new int[rend.length+1];
		A[0]=0;
		A[1]=rend[0];
		for(int i=2;i<=rend.length;i++)
			A[i]=Math.max(A[i-1], A[i-2]+rend[i-1]);
		
		S= new ArrayList<Integer> ();
		int i = A.length-1;
		while(i>0)
		{
			if(A[i]>A[i-1])
			{
				S.add(i-1);
				somma +=rend[i-1];
				i=i-2;
			}
			else
				i--;
		}
		
		///NB. Ho commentato questo poichè è un alternativa per poter ottenere la somma dei valori della soluzione ottimale 
		//Si può scorrere la lista delle posizioni con un ciclo for each e sommarle tra di loro
		/*for(int j : S)
			somma +=rend[j];*/
		
		//Ritorno il valore della somma
		return somma;
	}
	public int scelta(int[] rendAtleta1, int[] rendAtleta2) 	
	{
		//Controllo per verificare se per uno dei due atleti la lunghezza dell'array rendAtleta non corrisponde a numeroDiscipline		 (è maggiore o minore), 
		if(num!= rendAtleta1.length || num!=rendAtleta2.length)
			throw new IllegalArgumentException();
		
		//Richiamo due volte la funzione msi per ottenere la soluzione ottimale del primo atleta e la assegno alla variabile rend1
		int rend1 = msi(rendAtleta1);
		//Richiamo di nuovo per poter ottenere la soluzione ottimale del secondo atleta
		int rend2 = msi(rendAtleta2);
		
		//Una volta ottenute le soluzioni ottimali si possono confrontare:
		
		//Se sono uguali i due rendimenti ritorna 0
		if(rend1 ==rend2)
			return 0;
		//Se il rendimento del primo atleta è maggiore ritorna 1
		else if(rend1 > rend2)
			return 1;
		
		//Se il rendimento del secondo atleta è maggiore ritorna 2
		else
			return 2;

	}
}
