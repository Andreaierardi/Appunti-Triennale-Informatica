package main;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.w3c.dom.Node;
import org.w3c.dom.Element;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import java.io.File;
import java.util.Calendar;

public class DB_appelli
{

	//RF05: gestione voto
	//Autore: Andrea Ierardi, Andrea Ferrari	

  public DB_appelli()
  {

  }


  
  public static voto ricerca_voto(int matricola,String codice_appello)
  {

    int l, i;
    Node nNode;
    Element eElement;
    File fXmlFile;
    voto v = null;
    
    String data_verbale;
    String data_accettazione;
    
    String[] parts;

    try
    {
      //APRI FILE voti.xml
      fXmlFile = new File("src//XML//voti.xml");
      DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
      DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
      Document doc = dBuilder.parse(fXmlFile);
      NodeList nList = doc.getElementsByTagName("voto");
      l=nList.getLength();
      
      
      i=0;
      do
      {	

        //CARICA VOTO DA FILE
		nNode = nList.item(i);	
		if (nNode.getNodeType() == Node.ELEMENT_NODE)
		{
		  eElement = (Element) nNode;
		  v=new voto();	  		  
		  v.valore=Integer.parseInt(eElement.getAttribute("valore"));
		  
		  
		  v.accettato=Boolean.parseBoolean(eElement.getAttribute("accettato"));
		  
		  data_verbale=eElement.getAttribute("data_verbale");
    	  parts = data_verbale.split("/");
		  v.data_verbale = new data();
		  v.data_verbale.giorno=Integer.parseInt(parts[0]);
		  v.data_verbale.mese=Integer.parseInt(parts[1]);
		  v.data_verbale.anno=Integer.parseInt(parts[2]);
		  
		  data_accettazione=eElement.getAttribute("data_accettazione");
		  v.data_accettazione = new data();
		  if(data_accettazione.isEmpty()) {
			 v.data_accettazione = null;
		  }
		  else {
			  parts = data_accettazione.split("/");
			  v.data_accettazione.giorno=Integer.parseInt(parts[0]);
			  v.data_accettazione.mese=Integer.parseInt(parts[1]);
			  v.data_accettazione.anno=Integer.parseInt(parts[2]);
			  
		  }
	      v.matricola=Integer.parseInt(eElement.getAttribute("matricola"));
	      
		  v.codice_appello=eElement.getAttribute("codice_appello");
		  
		  v.codice_corso=Integer.parseInt(eElement.getAttribute("codice_corso"));

		  if ((v.matricola == matricola) && (v.codice_appello.equals(codice_appello)))
			  {
			  	return v; 
			  }
		  
		}
		i++;	
      }while(i<l); //FINCHE' CI SONO ALTRI VOTI
    }

    catch (Exception e) 
    {
      e.printStackTrace();
    }

    //CHIUDI FILE
    fXmlFile=null;
    return null;
  }
  
  public static void aggiorna_voto(voto voto, String risposta)
  {
    int l, i;
    Node nNode;
    Element eElement;
    File fXmlFile;
    voto v;
    boolean ris;
    if (Integer.parseInt(risposta)==1)
    	ris = true;
    else
    	ris = false;

    try
    {
      //APRI FILE accounts.xml
      fXmlFile = new File("src//XML//voti.xml");
      DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
      DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
      Document doc = dBuilder.parse(fXmlFile);
      NodeList nList = doc.getElementsByTagName("voto");
      l=nList.getLength();

      i=0;
      do
      {
		nNode = nList.item(i);	
		if (nNode.getNodeType() == Node.ELEMENT_NODE)
		{
		  eElement = (Element) nNode;
		  v=new voto();
	
	
		  v=new voto();	  		  
		  v.valore=Integer.parseInt(eElement.getAttribute("valore"));
		  
		  v.accettato=Boolean.parseBoolean(eElement.getAttribute("accettato"));
		  v.codice_appello=eElement.getAttribute("codice_appello");

		  String data_verbale = eElement.getAttribute("data_verbale");
    	  String[] parts = data_verbale.split("/");
		  v.data_verbale = new data();
		  v.data_verbale.giorno=Integer.parseInt(parts[0]);
		  v.data_verbale.mese=Integer.parseInt(parts[1]);
		  v.data_verbale.anno=Integer.parseInt(parts[2]);
		  
		  String data_accettazione = eElement.getAttribute("data_accettazione");
		  if(data_accettazione.isEmpty())
		  {
			  v.data_accettazione = null;
		  }
		  else
		  {
			  parts = data_accettazione.split("/");
			  v.data_accettazione = new data();
			  v.data_accettazione.giorno=Integer.parseInt(parts[0]);
			  v.data_accettazione.mese=Integer.parseInt(parts[1]);
			  v.data_accettazione.anno=Integer.parseInt(parts[2]);
		  }
    	 
		  
	      v.matricola=Integer.parseInt(eElement.getAttribute("matricola"));
	      
		  
		  v.codice_corso=Integer.parseInt(eElement.getAttribute("codice_corso"));
		  
		  if ((v.matricola == voto.matricola) && v.codice_corso == voto.codice_corso)
		  {	
			  v.accettato = ris;
			  
			  Calendar cal = Calendar.getInstance();

			  int giorno =  cal.get(Calendar.DATE);
			  int mese = cal.get(Calendar.MONTH) +1;
			  int anno = cal.get(Calendar.YEAR);
			  
			  v.data_accettazione = new data();
			  v.data_accettazione.giorno = giorno;
			  v.data_accettazione.mese = mese;
			  v.data_accettazione.anno = anno;
			  
			  String date = giorno + "/" + mese + "/" + anno; 
			  
			  eElement.setAttribute("data_accettazione", date);
			  eElement.setAttribute("accettato", Boolean.toString(v.accettato));
			
			  // Scrive il contenuto nel file XML
	          TransformerFactory transformerFactory = TransformerFactory.newInstance();
	          Transformer transformer = transformerFactory.newTransformer();
	      	  transformer.setOutputProperty(OutputKeys.INDENT, "yes");
	          StreamResult result = new StreamResult(new File("src//XML//voti.xml"));

	          DOMSource source = new DOMSource(doc);
	          transformer.transform(source, result);
	          
		  }
		}      

		i++;	
      }while(i<l); //FINCHE' CI SONO ALTRI VOTI
    }

    catch (Exception e) 
    {
      e.printStackTrace();
    }

    //CHIUDI FILE
    fXmlFile=null;
  }
}
