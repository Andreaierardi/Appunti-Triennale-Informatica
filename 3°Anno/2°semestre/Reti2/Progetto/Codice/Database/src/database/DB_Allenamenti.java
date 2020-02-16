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

import smartbench.Allenamento;

public class DB_Allenamenti {


	//private static NodeList nList;

	public static ArrayList<Allenamento> ricercaAllenamenti(String utente) 
	{

		int l, i;
		Node nNode;
		Element eElement;
		File fXmlFile;
		Allenamento a = null;
		ArrayList<Allenamento> ris = new ArrayList<Allenamento>();

		try
		{
			fXmlFile = new File("src//XML//allenamenti.xml");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			NodeList nList = doc.getElementsByTagName("allenamento");
			l=nList.getLength();


			i=0;
			do
			{	
				nNode = nList.item(i);	
				if (nNode.getNodeType() == Node.ELEMENT_NODE)
				{
					eElement = (Element) nNode;
					a=new Allenamento();	  

					a.nomeAtleta = eElement.getAttribute("nomeAtleta"); 
					a.timestamp=eElement.getAttribute("timestamp"); 
					a.valutazione= Integer.parseInt(eElement.getAttribute("valutazione"));
					a.mediaFC=Double.parseDouble(eElement.getAttribute("mediaFC"));
					a.mediaPS=Integer.parseInt(eElement.getAttribute("mediaPS"));
					a.mediaRip=Integer.parseInt(eElement.getAttribute("mediaRip"));
					a.mediaPeso= Integer.parseInt(eElement.getAttribute("mediaPeso"));
					a.ripetizioniAll= Integer.parseInt(eElement.getAttribute("ripetizioniAll")); 
					a.pesoMaxAll= Integer.parseInt(eElement.getAttribute("pesoMaxAll"));

					if (utente.equals(a.nomeAtleta))
					{
						ris.add(a);
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
		Collections.reverse(ris);
		return ris;
	}


	public static Allenamento ricercaUltimoAllenamento(String utente)
	{

		ArrayList<Allenamento> all=ricercaAllenamenti(utente);
		if(all.size()>0)
		{
			String s= all.get(all.size()-1).toString();
			System.out.println("Cerco nel DB ultimo allenamento: "+s);
			return all.get(0);
		}

		return null;

	}


	public static boolean pubblicaNuovoAllenamento(Allenamento all) throws TransformerException, ParserConfigurationException, SAXException, IOException
	{
		if(!all.nomeAtleta.isEmpty())
		{
			Document doc= caricaStrutturaDati("src//XML//allenamenti.xml", "allenamento");
			Element nuovoEl=(Element) doc.createElement("allenamento");
			nuovoEl.setAttribute("nomeAtleta", all.nomeAtleta);
			nuovoEl.setAttribute("valutazione",Integer.toString(all.valutazione));
			nuovoEl.setAttribute("mediaFC",Double.toString(all.mediaFC) );
			nuovoEl.setAttribute("mediaPS",Integer.toString(all.mediaPS) );
			nuovoEl.setAttribute("mediaRip", Integer.toString(all.mediaRip));
			nuovoEl.setAttribute("mediaPeso",Integer.toString(all.mediaPeso));
			nuovoEl.setAttribute("ripetizioniAll", Integer.toString(all.ripetizioniAll));
			nuovoEl.setAttribute("pesoMaxAll", Integer.toString(all.pesoMaxAll));
			nuovoEl.setAttribute("timestamp", all.timestamp);
			doc.getDocumentElement().appendChild(nuovoEl);
			salvaNuovoFile("src//XML//allenamenti.xml", doc);

			return true;
		}
		return false;

	}

	protected static Document caricaStrutturaDati(String pathname, String tag) throws ParserConfigurationException, SAXException, IOException 
	{
		File xmlFile = new File(pathname);
		DocumentBuilderFactory dBuilderFactory = DocumentBuilderFactory.newInstance();
		DocumentBuilder dBuilder = dBuilderFactory.newDocumentBuilder();
		Document doc = dBuilder.parse(xmlFile);
	//	nList = doc.getElementsByTagName(tag);
	//	int l = nList.getLength();

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


}
