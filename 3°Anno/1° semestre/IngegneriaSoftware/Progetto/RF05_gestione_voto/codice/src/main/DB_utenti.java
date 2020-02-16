package main;

import javax.xml.parsers.DocumentBuilderFactory;

import javax.xml.parsers.DocumentBuilder;

import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import java.io.File;

public class DB_utenti
{

	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari

  public DB_utenti()
  {

  }

  public static utente ricerca_dati_utente(int matricola)
  {
   
    int l, i;
    Node nNode;
    Element eElement;
    File fXmlFile;
   
    utente u;
    utente Utente = null;
    String nascita;
    String[] parts;

    try
    {
      //APRI FILE accounts.xml
      fXmlFile = new File("src//XML//utenti.xml");
      DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
      DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
      Document doc = dBuilder.parse(fXmlFile);
      NodeList nList = doc.getElementsByTagName("utente");
      l=nList.getLength();
      i=0;
      
      do
      {	
        //CARICA UTENTE DA FILE
		nNode = nList.item(i);	
		if (nNode.getNodeType() == Node.ELEMENT_NODE)
		{
		  eElement = (Element) nNode;
		  u=new utente();
		  u.nome=eElement.getAttribute("nome");
		  u.cognome=eElement.getAttribute("cognome");
	
		  nascita=eElement.getAttribute("nascita");
	      parts = nascita.split("/");
						
		  u.nascita = new data();
		  u.nascita.giorno=Integer.parseInt(parts[0]);
		  u.nascita.mese=Integer.parseInt(parts[1]);
		  u.nascita.anno=Integer.parseInt(parts[2]);	
	
		  u.email=eElement.getAttribute("email");
		  u.telefono=eElement.getAttribute("telefono");
		  u.username=eElement.getAttribute("username");	
		  u.qualifica=eElement.getAttribute("qualifica");
		  if (u.qualifica.length() == 0)
		  {
		  	u.anno=Integer.parseInt(eElement.getAttribute("anno"));
			u.CdL=eElement.getAttribute("CdL");
		  }
		  else
		  {
		  	u.anno=0;
		  	u.CdL="";
		  }				
		  
		  if (Integer.toString(matricola).equals(u.username))
		  {
			// Ritorna l'oggetto utente
		    Utente = u; 						
		  }
		}
		i++;	
      }while(i<l); //FINCHE' CI SONO ALTRI UTENTI
    }

    catch (Exception e) 
    {
      e.printStackTrace();
    }

    //CHIUDI FILE
    fXmlFile=null;
    return Utente;
  }

}
