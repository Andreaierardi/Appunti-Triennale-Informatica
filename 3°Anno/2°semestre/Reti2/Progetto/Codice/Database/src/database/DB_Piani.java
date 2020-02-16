package database;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import smartbench.Piano;

public class DB_Piani {


	public static ArrayList<Piano> ricercaPiani(String utente)
	{
		int l, i;
		Node nNode;
		Element eElement;
		File fXmlFile;
		Piano p = null;
		ArrayList<Piano> ris = new ArrayList<Piano>();

		try
		{
			fXmlFile = new File("src//XML//piani.xml");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			NodeList nList = doc.getElementsByTagName("piano");
			l=nList.getLength();


			i=0;
			do
			{	
				nNode = nList.item(i);	
				if (nNode.getNodeType() == Node.ELEMENT_NODE)
				{
					eElement = (Element) nNode;
					p=new Piano();	  
					p.nomeUtente= eElement.getAttribute("nomeUtente"); 
					p.validita=eElement.getAttribute("validita");
					p.totRip= Integer.parseInt(eElement.getAttribute("totRip"));
					p.peso= Integer.parseInt(eElement.getAttribute("peso"));
					p.serie= Integer.parseInt(eElement.getAttribute("serie"));
				
					if (utente.equals(p.nomeUtente))
						ris.add(p);

				}
				i++;	
			}while(i<l); 
		}

		catch (Exception e) 
		{
			e.printStackTrace();
		}
		Collections.reverse(ris);
		//CHIUDI FILE
		fXmlFile=null;
		return ris;
	}

	
	public static Piano ricercaUltimoPiano(String utente)
	{
		int l, i;
		Node nNode;
		Element eElement;
		File fXmlFile;
		Piano p = null;
		Piano tmp=null;
		try
		{
			fXmlFile = new File("src//XML//piani.xml");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			NodeList nList = doc.getElementsByTagName("piano");
			l=nList.getLength();

			i=0;
			do
			{	
				nNode = nList.item(i);	
				if (nNode.getNodeType() == Node.ELEMENT_NODE)
				{
					
						eElement = (Element) nNode;
						p=new Piano();
						p.nomeUtente= eElement.getAttribute("nomeUtente"); 
						p.validita=eElement.getAttribute("validita");

						p.totRip= Integer.parseInt(eElement.getAttribute("totRip"));
						p.peso= Integer.parseInt(eElement.getAttribute("peso"));
						p.serie= Integer.parseInt(eElement.getAttribute("serie"));
						if(utente.equals(p.nomeUtente)&&(p.validita.equals("valid")))
						{
							fXmlFile=null;
							return p;
						}
				}
				i++;	
			}while(i<l); 
		}
		catch (Exception e) 
		{
			e.printStackTrace();
		}

		//CHIUDI FILE
		fXmlFile=null;
		System.out.println("ERRORE nessun piano valido trovato per l'utente: "+utente);
		return tmp;
	}



	public static boolean pubblicaNuovoPiano(Piano p,String nomeUt) throws ParserConfigurationException, SAXException, IOException, TransformerException
	{
		if(p.nomeUtente.equals(nomeUt))
		{
			modificaPiano(nomeUt);
			Document doc= caricaStrutturaDati("src//XML//piani.xml", "piano");
			Element nuovoEl=(Element) doc.createElement("piano");
			nuovoEl.setAttribute("nomeUtente", p.nomeUtente);
			nuovoEl.setAttribute("validita", p.validita);
			nuovoEl.setAttribute("totRip", Integer.toString(p.totRip));
			nuovoEl.setAttribute("peso", Integer.toString(p.peso));
			nuovoEl.setAttribute("serie", Integer.toString(p.serie));
			doc.getDocumentElement().appendChild(nuovoEl);
			salvaNuovoFile("src//XML//piani.xml", doc);
			
			System.out.println("Piano scritto correttamente");
			return true;
		}
		System.out.println("ERRORE: PIANO NON SCRITTO");
		return false;

	}
	protected static Document caricaStrutturaDati(String pathname, String tag) throws ParserConfigurationException, SAXException, IOException {
		File xmlFile = new File(pathname);
		DocumentBuilderFactory dBuilderFactory = DocumentBuilderFactory.newInstance();
		DocumentBuilder dBuilder = dBuilderFactory.newDocumentBuilder();
		Document doc = dBuilder.parse(xmlFile);
	
		xmlFile=null;

		return doc;
	}


	protected static void salvaNuovoFile(String pathname, Document doc) throws TransformerException {
		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer = transformerFactory.newTransformer();
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		StreamResult result = new StreamResult(pathname);
		DOMSource source = new DOMSource(doc);
		transformer.transform(source, result);
	}



	 public static void modificaPiano(String utente)
	  {
	    int l, i;
	    Node nNode;
	    Element eElement;
	    File fXmlFile;
	    Piano v;
	    try
	    {
	      fXmlFile = new File("src//XML//piani.xml");
	      DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
	      DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
	      Document doc = dBuilder.parse(fXmlFile);
	      NodeList nList = doc.getElementsByTagName("piano");
	      l=nList.getLength();

	      i=0;
	      do
	      {
			nNode = nList.item(i);	
			if (nNode.getNodeType() == Node.ELEMENT_NODE)
			{
			  eElement = (Element) nNode;
			  v=new Piano();
		
			  v.nomeUtente=eElement.getAttribute("nomeUtente");
			  v.peso= Integer.parseInt(eElement.getAttribute("peso"));
			  v.serie= Integer.parseInt(eElement.getAttribute("serie"));
			  v.totRip=Integer.parseInt(eElement.getAttribute("totRip"));
			  v.validita=eElement.getAttribute("validita");
			  if (v.nomeUtente.equals(utente))
			  {	
				v.validita="invalid";
				  
				 				  
				  eElement.setAttribute("validita",v.validita);
				 
				  // Scrive il contenuto nel file XML
		          TransformerFactory transformerFactory = TransformerFactory.newInstance();
		          Transformer transformer = transformerFactory.newTransformer();
		      	  transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		          StreamResult result = new StreamResult(new File("src//XML//piani.xml"));

		          DOMSource source = new DOMSource(doc);
		          transformer.transform(source, result);
		          
			  }
			}      

			i++;	
	      }while(i<l); 
	    }

	    catch (Exception e) 
	    {
	      e.printStackTrace();
	    }

	    //CHIUDI FILE
	    fXmlFile=null;
	  }
	    
	    
}