package database;

import java.io.File;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;



public class DB_utenti {



	public static Account login(String username, String password) {
		int l, i;
		Node nNode;
		Element eElement;
		File fXmlFile;
		Account a=new Account();

		try
		{
			fXmlFile = new File("src//XML//utenti.xml");
			DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
			DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
			Document doc = dBuilder.parse(fXmlFile);
			NodeList nList = doc.getElementsByTagName("account");
			l=nList.getLength();
			i=0;
			do
			{	
				nNode = nList.item(i);	
				if (nNode.getNodeType() == Node.ELEMENT_NODE)
				{
					eElement = (Element) nNode;

					a.username = new String(eElement.getAttribute("username").getBytes("UTF-8"));
					a.password=eElement.getAttribute("password");
					a.tipo=eElement.getAttribute("tipo");

					String usr = convert(a.username);
					String usr2 = convert(username);
					String pwd = convert(a.password);
					String pwd2 = convert(password);


					if (pwd.equals(pwd2)&& usr.equals(usr2))
						return a;


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

		return null;


	}

	private static String convert(String username) {

		String p = new String("");

		for(int k = 0; k<username.length();k++)
			p+=username.charAt(k);
		

		return p;
	}
}
