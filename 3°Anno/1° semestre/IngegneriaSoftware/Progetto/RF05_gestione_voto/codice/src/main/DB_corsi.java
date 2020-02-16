package main;

import java.io.File;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

public class DB_corsi
{

	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari
	
  public DB_corsi()
  {

  }
	  
  public static corso ricerca_dati_corso(int codice_corso) {
	   
    int l, i;
    Node nNode;
    Element eElement;
    File fXmlFile;
    corso c;
    corso Corso = null;
 
    try
    {
      //APRI FILE corsi.xml
      fXmlFile = new File("src//XML//corsi.xml");
      DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
      DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
      Document doc = dBuilder.parse(fXmlFile);
      NodeList nList = doc.getElementsByTagName("corso");
      l=nList.getLength();

      i=0;
      do
      {	

        //CARICA CORSI DA FILE
		nNode = nList.item(i);	
		if (nNode.getNodeType() == Node.ELEMENT_NODE)
		{
		  eElement = (Element) nNode;
		  c =new corso();
		  c.nome=eElement.getAttribute("nome");
		  c.codice=Integer.parseInt(eElement.getAttribute("codice"));
		  c.anno = Integer.parseInt(eElement.getAttribute("anno"));
		  c.studenti = Integer.parseInt(eElement.getAttribute("studenti"));
		  c.cdl=eElement.getAttribute("CdL");
		  c.cognome_docente=eElement.getAttribute("cognome_docente");

		  if (codice_corso == c.codice)
		  {
			// Ritorna l'oggetto corso
		    Corso = c; 						
		  }
		}
		i++;	
      }while(i<l); //FINCHE' CI SONO ALTRI CORSI
    }

    catch (Exception e) 
    {
      e.printStackTrace();
    }

    //CHIUDI FILE
    fXmlFile=null;
    return Corso;
  }

}
