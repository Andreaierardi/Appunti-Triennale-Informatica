package bacheca;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;

import jbook.util.Input;

public class Console {

	public static void main(String[] args) throws FormatException, IOException {
		Bacheca bach = new Bacheca();
		int risp=0;
		while(risp!=3)
		{
			
			try
			{
				while((risp!=1) && (risp !=2)&& (risp != 3))
				{
					risp = Input.readInt("=========================\nVuoi:\n1)Gestione Utenti\n2)Gestione Bacheca\n3)ESCI\n");

				if (risp==1)
					{
						modUtente();
						risp=0;
					}
				if (risp==2)
				{
					String nome = Input.readString("Inserisci il tuo nome utente: ");
					Utente utente = Utenti.getUtente(nome); 
					if (Utenti.contains(nome))
							modBacheca(bach,utente);
						
					else
						System.out.println("Inserisci un nome utente valido per poter loggare in bacheca!");
				
					risp=0;
					
				}
				if (risp==3) break;	
				}
			}
			catch (NumberFormatException e)
			{
				System.out.println("\nDevi inserisci un valore intero!!!\n---------------");
			}
			catch (FormatException e)
			{
				System.out.println("\n"+e.getMessage()+"!!!\n---------------");
				risp = 0;
			}
			
		}
			
	
		return;
	}
	private static void modBacheca(Bacheca bach, Utente u) throws NumberFormatException, FormatException, IOException
	{
		
		int modb=0;

		while((modb>0)||(modb<11))
		{
			try

			{
				System.out.println("==========================\nGestione Bacheca\n");
				System.out.println("1) Ottieni l'elenco delle parole chiave\n"
						+ "2) Ottieni tutti gli ID degli annunci in cui si vende un oggetto che ha intersezione non vuota con un sottoinsieme delle parole chiave\n"
						+ "3) Visualizza tutti i tuoi annunci\n" 
						+ "4) Visualizza il contenuto di un annuncio\n"
						+ "5) Inserisci un annuncio nella bacheca(fornendo le info necessarie)\n"
						+ "6) Rimuovi un' annuncio\n" 
						+ "7) Visualizza tutti gli annunci in bacheca\n"
						+ "8) Leggi la bacheca da file\n"
						+ "9) Stampa su file\n"
						+ "10) Logout\n");
				modb = Input.readInt();
				if(modb==1)
					System.out.println(bach.paroleChiaveString());
				if(modb==2)	
					{
						String tmp = Input.readString("Scrivi un sottoinsieme di parole chiave di cui vuoi ottenere gli ID: (Separare le parole chiave con un '-' e senza spazi):\n");
						String [] listakeys = tmp.split("-");
						ArrayList<Integer> listID = new ArrayList<Integer>();
						listID= bach.intersezione(listakeys);
						System.out.println("\nLista degli id:\n"+listID.toString());
						
					}
						
				if(modb==3)

					System.out.println("\nPropri annunci presenti in bacheca:\n"+bach.listaPropriAnnunci(u));
				if(modb==4)
				{
					int id = Input.readInt("Inserisci l'id dell'annuncio da visualizzare: ");
					System.out.println("Annuncio: "+bach.visualizzaAnnuncio(id));
				}
				if(modb==5)
				{
					int count = 0 ;
					String[] data = new String[6];
					data[count++]=Input.readString("Inserisci il tipo di annuncio(V/C): ");
					data[count++]=Input.readString("Inserisci il nome dell'oggetto: ");
					data[count++]=Input.readString("Inserisci la quantita': ");
					data[count++]=Input.readString("Inserisci il prezzo: ");
					data[count++]=Input.readString("Inserisci l'identificatore: ");
					data[count++]=Input.readString("Inserisci delle parole chiave separate da un '-' senza spazi in mezzo: ");

					bach.aggiungiAnnuncio(new Annunci(data[0].charAt(0),data[1],u,Integer.parseInt(data[2]),Integer.parseInt(data[3]),Integer.parseInt(data[4]),data[5].split("-")));
				}
				if (modb==6)
				{
					int id1= Input.readInt("Inserisci l'id dell'annuncio da eliminare: ");
					bach.rimuoviAnnuncio(id1, u);
					System.out.println(bach.elencoAnnunci());
				}
				if(modb==7)
					System.out.println("ELENCO ANNUNCI:\n"+bach.elencoAnnunci());

				if(modb==8)
				{
					String nomeFile= Input.readString("Inserisci il nome del file da cui importare la bacheca: ");
					bach.leggiBacheca(nomeFile);
					System.out.println("ELENCO ANNUNCI:\n"+bach.elencoAnnunci());
				}

				if(modb==9)
				{
					String nomeFile= Input.readString("Inserisci il nome del file su cui scrivere la bacheca: ");
					bach.scriviBacheca(nomeFile);
					System.out.println("Bacheca scritta con successo!\n");
				}
				if(modb==10 )return;


			}
			catch (FormatException e)
			{
				System.out.println("\n"+e.getMessage()+"!!!\n---------------");
			}
			catch (StringIndexOutOfBoundsException e)
			{
				System.out.println("\nNon sono presenti annunci!!!\n---------------");
			}
			catch (NumberFormatException e)
			{
				System.out.println("\nDevi inserisci un valore intero!!!\n---------------");
			}
			catch(FileNotFoundException e)
			{
				System.out.println("\nFile non trovato o formato file non adeguato!");
			}
		}

		
	}
	
	private static void modUtente ()
	{
		int modu=0;
		while((modu!=2)||(modu!=1))
		{
			try
			{
				System.out.println("Gestione utenti\n");
				System.out.println("1) Aggiungi utente");
				System.out.println("2) Rimuovi utente");
				System.out.println("3) TORNA INDIETRO");
				modu = Input.readInt();
				if(modu==1)
				{
							String nome = Input.readString("Inserisci il nome utente: ");
							String email = Input.readString("Inserisci l'email dell'utente: ");
							Utente u = new Utente(nome,email);
							Utenti.aggiungiUtente(u);					
				}	
				else if(modu==2)
				{
	
					if (Utenti.numEl()==0) System.out.println("Non ci sono utenti in bacheca da rimuovere! Aggiungine uno!\n");
					else
						{
							System.out.println("Lista degli Utenti:\n"+Utenti.elencoUtenti());
							String nome1= Input.readString("Inserisci il nome utente da rimuovere: ");
							Utenti.RimuoviUtente(nome1);
						}	
				}
				else if (modu==3)
					return;
							
			}
			catch (NumberFormatException e)
			{
				System.out.println("\nDevi inserisci un valore intero!!!\n---------------");
			}
			catch (FormatException e)
			{
				System.out.println("\n"+e.getMessage()+"!!!\n---------------");
			}
		}
	}
}