package hs;

import java.io.IOException;
import java.io.UnsupportedEncodingException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.*;
import java.text.SimpleDateFormat;

import javax.mail.*;
import javax.mail.internet.*;
import java.util.*;
/**
 * Servlet implementation class Controller
 */

@WebServlet("/Controller")
public class Controller extends HttpServlet {
	private static final long serialVersionUID = 1L;
	public Connection db;
	/**
	 * @throws SQLException 
	 * @throws ClassNotFoundException 
	 * @see HttpServlet#HttpServlet()
	 */
	public Controller() throws SQLException, ClassNotFoundException {

		Class.forName("com.mysql.jdbc.Driver");
		String connectionURL = "jdbc:mysql://localhost/hobbyshop";
		db = DriverManager.getConnection(connectionURL, "root","");

		Statement st = db.createStatement();
		/*ResultSet myR = st.executeQuery("SELECT * from ");

    	while(myR.next())
    	{
    		System.out.println(myR.getString("email"));
    	}
        // TODO Auto-generated constructor stub*/


	}


	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		response.getWriter().append("Served at: ").append(request.getContextPath());
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

	public String visualizzaUtenti() throws SQLException
	{
		Statement st = db.createStatement();
		ResultSet rs = 	st.executeQuery("SELECT id, email, nome, cognome, data_nascita, telefono FROM utente");

		String html = "<table class=\"table\"><tr>"
				+ "<th>id</th>"
				+ "<th>email</th>"
				+ "<th>nome</th>"
				+ "<th>cognome</th>"
				+ "<th>data_nascita</th>"
				+ "<th>telefono</th>"
		  			+ "</tr>";
		for (rs.beforeFirst(); rs.next();) {

			
			html += "<tr>"
					+ "<td>"+rs.getString("id")+"</td>"
					+ "<td>"+rs.getString("email")+"</td>"
					+ "<td>"+rs.getString("nome")+"</td>"
					+ "<td>"+rs.getString("cognome")+"</td>"
					+ "<td>"+rs.getString("data_nascita")+"</td>"
					+ "<td>"+rs.getString("telefono")+"</td>";

		}
		html += "</table>";

		return html;	
	}
	public int nUtenti() throws SQLException
	{
		String q = "SELECT COUNT(id) FROM utente";
		Statement st = db.createStatement();
		ResultSet rs = st.executeQuery(q);
		if(rs.last())
			return rs.getInt(1);
		return 0;
	}

	public int nOrdini() throws SQLException
	{
		String q = "SELECT COUNT(id) FROM cont_ordine";
		Statement st = db.createStatement();
		ResultSet rs = st.executeQuery(q);
		if(rs.last())
			return rs.getInt(1);
		return 0;
	}

	public int nPrdotti() throws SQLException
	{
		String q = "SELECT COUNT(id) FROM prodotto";
		Statement st = db.createStatement();
		ResultSet rs = st.executeQuery(q);
		if(rs.last())
			return rs.getInt(1);
		return 0;
	}


	public int nCategorie() throws SQLException
	{
		String q = "SELECT COUNT(id) FROM categoria";
		Statement st = db.createStatement();
		ResultSet rs = st.executeQuery(q);
		if(rs.last())
			return rs.getInt(1);
		return 0;
	}

	/*Aggiunta film*/
	public String addProdottoFilm(String nome, String  categoria,String  immagine,  String  descrizione,  String prezzo,  String prezzo_spedizione, 
			String  giacenza, String titolo, String  genere, String anno, String nomer, String cognomer, String datar,String luogor, String []ruoli,String [] nomea,String [] cognomea,String [] sessoa,String []dataa,String [] luogoa ) throws SQLException
	{
		System.out.println("INSERISCO film");


		String prodotto = addProdotto(nome+" - DVD",categoria,immagine, descrizione, prezzo, prezzo_spedizione, giacenza);
		String reg = addRegista(nomer, cognomer, datar, luogor);
		String dvd = addSupportoV(anno, prodotto);
		String film = addFilm(titolo,reg,genere,dvd);

		addAttori_Ruoli(nomea,cognomea,sessoa,dataa,luogoa,ruoli,film);
		return prodotto;
	}

	private void addAttori_Ruoli(String[] nomea, String[] cognomea, String[] sessoa, String[] dataa, String[] luogoa,
			String[] ruoli, String film) throws SQLException {
		for(int i =0 ; i<nomea.length; i++)
		{
			Statement st = db.createStatement();
			st.executeUpdate("INSERT INTO attore (id,nome,cognome,sesso, data_nascita, luogo_nascita) VALUES(DEFAULT,'"+nomea[i]+"','"+cognomea[i]+"','"+sessoa[i]+"','"+dataa[i]+"','"+luogoa[i]+"')");

			Statement st2 = db.createStatement();
			ResultSet rs = st2.executeQuery("SELECT id from attore WHERE nome='"+nomea[i]+"' AND cognome='"+cognomea[i]+"' AND data_nascita='"+dataa[i]+"'");
			String id = null;
			if(rs.last())
				id =  rs.getString(1);

			Statement st3 = db.createStatement();
			st3.executeUpdate("INSERT INTO ruoli (attore,film,ruolo) VALUES('"+id+"','"+film+"','"+ruoli[i]+"')");


		}

	}


	private String addFilm(String titolo, String reg, String genere, String dvd) throws SQLException {
		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO film (id,titolo,regista,genere,dvd) VALUES(DEFAULT,'"+titolo+"','"+reg+"','"+genere+"','"+dvd+"')");
		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from film WHERE titolo='"+titolo+"' AND dvd='"+dvd+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}


	private String addRegista(String nomer, String cognomer, String datar, String luogor) throws SQLException 
	{
		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO regista (id,nome,cognome,data_nascita,luogo_nascita) VALUES(DEFAULT,'"+nomer+"','"+cognomer+"','"+datar+"','"+luogor+"')");
		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from regista WHERE nome='"+nomer+"' AND cognome='"+cognomer+"' AND data_nascita='"+datar+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}


	/*Aggiunta album*/
	public String addProdottoMusica(String nome, String categoria, String tipo, String immagine,  String descrizione, String prezzo, String prezzo_spedizione, String giacenza,
			String titolo, String genere,	String anno, 
			String artista, String data,String luogo, 
			String[] canzone, String[] durata) throws SQLException 
	{
		/* INSERT in : prodotto, supporto_audio, album, artista, canzone, */

		System.out.println("INSERISCO");


		String prodotto = addProdotto(nome+" - "+tipo,categoria,immagine, descrizione, prezzo, prezzo_spedizione, giacenza);
		String id_artista = addArtista(artista,data,luogo);
		String album = addAlbum(titolo,id_artista);

		String supporto = addSupportoM(titolo,tipo, album, id_artista, prodotto, genere, anno);

		addCanzoni(canzone, durata, album);

		return prodotto;


	}

	private void addCanzoni(String[] canzone, String[] durata, String album) throws SQLException {
		for(int i =0 ; i<canzone.length; i++)
		{
			String sql = "SELECT * from canzone where titolo = '"+canzone[i]+"' AND album='"+album+"'";
			Statement error = db.createStatement();
			ResultSet err = error.executeQuery(sql);

			if(!err.last())
			{
				Statement st = db.createStatement();
				st.executeUpdate("INSERT INTO canzone (id,titolo,album,durata) VALUES(DEFAULT,'"+canzone[i]+"','"+album+"','"+durata[i]+"')");
			}
			else {
				throw new SQLException();
			}
		}

	}


	private String addSupportoM(String titolo, String tipo, String album, String id_artista, String prodotto, String genere,
			String anno) throws SQLException {
		Statement st = db.createStatement();
		String query = "INSERT INTO supporto_audio (id,titolo,tipo, album,artista, prodotto, genere, anno_uscita) VALUES (DEFAULT, '"+titolo+"','"+tipo+"','"+album+"','"+id_artista+"','"+prodotto+"','"+genere+"','"+anno+"')";
		System.out.println(query);
		st.executeUpdate(query);
		Statement st2 = db.createStatement();

		String checkid = "SELECT id from supporto_audio WHERE titolo='"+titolo+"' AND tipo = '"+tipo+"' AND prodotto='"+prodotto+"'";
		System.out.println("checkid: "+checkid);
		ResultSet rs = st2.executeQuery(checkid);
		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}


	private String addAlbum(String titolo, String id_artista) throws SQLException {
		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO album (id,titolo,artista) VALUES (DEFAULT, '"+titolo+"','"+id_artista+"')");

		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from album WHERE titolo='"+titolo+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}


	public String addProdotto(String nome,String categoria,String immagine,String descrizione,String prezzo, String prezzo_spedizione, String giacenza) throws SQLException
	{
		Statement st = db.createStatement();

		String insert = "INSERT INTO prodotto (id,nome,categoria,foto,descrizione,costo, costo_spedizione, giacenza, timestamp) VALUES (DEFAULT, '"+nome+"','"+categoria+"','"+immagine+"', \""+descrizione+"\", '"+prezzo+"', '"+prezzo_spedizione+"', '"+giacenza+"',DEFAULT)";
		System.out.println(insert);
		st.executeUpdate(insert);

		Statement st2 = db.createStatement();
		String query = "SELECT id from prodotto WHERE nome='"+nome+"'";
		System.out.println(query);
		ResultSet rs = st2.executeQuery(query);

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}

	public String addArtista(String artista, String data, String luogo) throws SQLException
	{
		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO artista (id,nome,data_nascita,luogo_nascita) VALUES(DEFAULT,'"+artista+"','"+data+"','"+luogo+"')");
		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from artista WHERE nome='"+artista+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}

	/*Aggiunta videogioco */
	public String addProdottoVideogioco(String nome,  String categoria, String immagine,  String descrizione,  String prezzo,  String prezzo_spedizione,  String giacenza,String titolo, String genere, String sviluppatore, String sede, String anno) throws SQLException
	{
		System.out.println("INSERISCO videogioco");


		String prodotto = addProdotto(nome+" - DVD",categoria,immagine, descrizione, prezzo, prezzo_spedizione, giacenza);
		String svil = addSviluppatore(sviluppatore, sede);
		String dvd = addSupportoV(anno, prodotto);

		String video = addVideogioco(titolo,dvd,svil,genere);

		return prodotto;

	}



	private String addVideogioco(String titolo, String dvd, String svil, String genere) throws SQLException {
		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO videogioco (id,titolo,dvd,sviluppatore,genere) VALUES (DEFAULT, '"+titolo+"','"+dvd+"','"+svil+"','"+genere+"')");

		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from videogioco WHERE titolo='"+titolo+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}


	private String addSupportoV(String anno, String prodotto) throws SQLException {
		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO supporto_video (id,prodotto,anno_uscita) VALUES (DEFAULT, '"+prodotto+"','"+anno+"')");

		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from supporto_video WHERE prodotto='"+prodotto+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;

	}


	private String addSviluppatore(String sviluppatore, String sede) throws SQLException {
		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO sviluppatore (id,nome,sede) VALUES (DEFAULT, '"+sviluppatore+"','"+sede+"')");

		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from sviluppatore WHERE nome='"+sviluppatore+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}


	/*Aggiunta libro */
	public String addProdottoLibro(String nome, String categoria, String immagine,  String descrizione,  String prezzo,  String prezzo_spedizione,  
			String giacenza,String titolo, String tipo,String genere, String nomeautore, String cognomeautore, String sessoautore, String dataautore,
			String luogoautore, String editore, String ISBN, String pagine, String anno) throws SQLException
	{
		System.out.println("INSERISCO libro");


		String prodotto = addProdotto(nome,categoria,immagine, descrizione, prezzo, prezzo_spedizione, giacenza);
		String autore = addAutore(nomeautore,cognomeautore,sessoautore,dataautore,luogoautore);
		String id_editore = addEditore(editore);
		String supp = addSupportoC(titolo,tipo,genere,autore,id_editore,ISBN,pagine,anno,prodotto);


		return prodotto;
		/*String svil = addSviluppatore(sviluppatore, sede);
		String dvd = addSupportoV(anno, prodotto);

		String video = addVideogioco(titolo,dvd,svil,genere);*/
	}
	private String addAutore(String nomeautore, String cognomeautore, String sessoautore, String dataautore,
			String luogoautore) throws SQLException {
		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO autore (id,nome,cognome, sesso, data_nascita, luogo_nascita) VALUES (DEFAULT, '"+nomeautore+"','"+cognomeautore+"','"+sessoautore+"','"+dataautore+"','"+luogoautore+"')");

		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from autore WHERE nome='"+nomeautore+"' AND cognome='"+cognomeautore+"' AND data_nascita='"+dataautore+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}

	public String addSupportoC(String titolo, String tipo, String genere, String autore, String editore_id, String ISBN, String pagine, String anno, String prodotto) throws SQLException
	{

		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO supporto_cartaceo (id,tipo,titolo, genere, autore, editore, ISBN, pagine, anno_uscita, prodotto) "
				+ "VALUES (DEFAULT, '"+tipo+"','"+titolo+"','"+genere+"','"+autore+"','"+editore_id+"','"+ISBN+"','"+pagine+"','"+anno+"','"+prodotto+"')");

		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from support_cartaceo WHERE titolo='"+titolo+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}
	public String addEditore(String editore) throws SQLException
	{
		Statement st = db.createStatement();
		st.executeUpdate("INSERT INTO editore (id,nome) VALUES (DEFAULT, '"+editore+"')");

		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery("SELECT id from editore WHERE nome='"+editore+"'");

		String id = null;
		if(rs.last())
			id =  rs.getString(1);
		return id;
	}
	/*Metodi di visualizzazione*/

	public String visualizzaProdotti() throws SQLException
	{
		Statement st = db.createStatement();
		ResultSet rs = 	st.executeQuery("SELECT * FROM prodotto ");

		String html = "<table class=\"table\"><tr>"
				+ "<th>id</th>"
				+ "<th>nome</th>"
				+ "<th>categoria</th>"
				+ "<th>descrizione</th>"
				+ "<th>prezzo</th>"
				+ "<th>prezzo di spedizione</th>"
				+ "<th>giacenza</th>"
				+ "<th>timestamp</th>"

		  			+ "</tr>";
		for (rs.beforeFirst(); rs.next();) {

			String categoria = new String();
			if(rs.getString("categoria").equals("1"))
				categoria="film";
			if(rs.getString("categoria").equals("2"))
				categoria="musica";
			if(rs.getString("categoria").equals("3"))
				categoria="videogiochi";
			if(rs.getString("categoria").equals("4"))
				categoria="libri";

			html += "<tr>"
					+ "<td>"+rs.getString("id")+"</td>"
					+ "<td>"+rs.getString("nome")+"</td>"
					+ "<td>"+categoria+"</td>"
					+ "<td>"+rs.getString("descrizione")+"</td>"
					+ "<td>"+rs.getString("costo")+"</td>"
					+ "<td>"+rs.getString("costo_spedizione")+"</td>"+ "<td>"+rs.getString("giacenza")+"</td>"+ "<td>"+rs.getString("timestamp")+"</td>";


		}
		html += "</table>";

		return html;	

	}	

	/* Prenotazioni */
	public void gestisciPrenotazioni(String prodotto, String giacenza, String nome) throws SQLException, UnsupportedEncodingException, MessagingException
	{
		Statement st = db.createStatement();
		ResultSet rs = st.executeQuery("SELECT * from prenotazione WHERE prodotto='"+prodotto+"' ORDER BY timestamp");

		int count = 0;
		for (rs.beforeFirst(); rs.next();) {

			String utente = rs.getString("utente");
			String email = getEmailByPren(utente);
			System.out.println("GET EMAIL: "+email);
			if(email!=null)
			{

				String mitt ="hobbyshop@noreply";
				String dest = email;
				String oggetto = "Prenotazione del tuo prodotto";
				String testoEmail = "<p>Gentile cliente,<br>il prodotto '"+nome+"' da lei ordinato è ora disponibile sul nostro sito<br><br>Servizio email HobbyShop, non rispondere a questa email</p>";
				this.sendMail(dest, mitt, oggetto, testoEmail);
				
				Statement st2 = db.createStatement();
				st2.executeUpdate("DELETE FROM prenotazione WHERE prodotto="+prodotto+" AND utente="+utente);
				
					
			}
			/*** MANDA EMAIL
			String mitt ="hobbyshop@noreplyS";
			String dest = "andreierardi@gmail.com";


			String oggetto = "Prenotazione del tuo prodotto";
			String testoEmail = "<p>Gentile cliente,<br>il prodotto da lei ordinato è ora disponibile sul nostro sito<br><br>Servizio email HobbyShop, non rispondere a questa email</p>";

		  	db.sendMail(dest, mitt, oggetto, testoEmail);
			 */

		}

	}

	public void sendMail (String dest, String mitt, String oggetto, String testoEmail)
			throws MessagingException, UnsupportedEncodingException
	{
		// Creazione di una mail session
		Properties props = new Properties();

		props.setProperty("mail.transport.protocol", "smtp");     
		props.setProperty("mail.host", "smtp.gmail.com");  
		props.put("mail.smtp.auth", "true");  
		props.put("mail.smtp.port", "465");  
		props.put("mail.debug", "true");  
		props.put("mail.smtp.socketFactory.port", "465");  
		props.put("mail.smtp.socketFactory.class","javax.net.ssl.SSLSocketFactory");  
		props.put("mail.smtp.socketFactory.fallback", "false");  
		Session session = Session.getDefaultInstance(props,  
				new javax.mail.Authenticator() {
			protected PasswordAuthentication getPasswordAuthentication() {  
				return new PasswordAuthentication("hobbyshop.prenotazioni@gmail.com","hobbymarket");  
			}  
		});  
		props.put("mail.smtp.user", "hobbyshop");

		Transport transport = session.getTransport();  

		// Aggiunta degli indirizzi del mittente e del destinatario
		InternetAddress fromAddress = new InternetAddress(mitt, "HobbyShop@gmail.com");
		InternetAddress toAddress = new InternetAddress(dest);

		MimeMessage message = new MimeMessage(session);

		message.setFrom(fromAddress);
		message.setRecipient(Message.RecipientType.TO, toAddress);

		message.setSubject(oggetto);  
		message.setContent(testoEmail, "text/html; charset=utf-8");  

		transport.connect();  
		Transport.send(message, message.getAllRecipients());  
		transport.close();
	}  

	private String getEmailByPren(String utente ) throws SQLException {

		Statement st = db.createStatement();


		ResultSet rs = st.executeQuery("SELECT email FROM utente WHERE id="+utente);

		if(rs.last())
			return rs.getString(1);
		return null;
	}


	/*Metodi rimozione*/
	public void removeProdotto(int id) throws SQLException
	{
		Statement st = db.createStatement();
		st.executeUpdate("DELETE FROM prodotto WHERE id = '"+id+"'");
	}

	public void removeUtente(int id) throws SQLException
	{
		Statement st = db.createStatement();
		st.executeUpdate("DELETE FROM utente WHERE id = '"+id+"'");
	}

	public void removeOrdine(int id) throws SQLException
	{
		Statement st = db.createStatement();
		st.executeUpdate("DELETE FROM ordine WHERE id = '"+id+"'");
	}

	public ArrayList<String> listCategorie() throws SQLException
	{
		Statement st = db.createStatement();
		ResultSet rs = st.executeQuery("SELECT nome FROM categoria");
		ArrayList<String> list = new ArrayList<String> ();
		for(rs.beforeFirst(); rs.next();)
		{
			list.add(rs.getString("nome"));
		}
		return list;
	}


	/*
	public String printData(ArrayList<String> data, ArrayList<String> nameData)
	{
		String group = "<div class=\"card-group\" style=\"display:inline-block\">";

		String cardt= "<div class=\"card\"><div class=\"card-body\">  <h5 class=\"card-title\">";
		String cardm= "</h5>  <p class=\"card-text\" id=\"";
		String cardf = "</p> </div></div>";

		String endid= "\">";
		String buth ="<button type=\"button\" class=\"btn btn-outline-info\" onclick=\"showLabel(\'";
		String butf = "\')\">Modifica</button> "; //TOLGO </p>
		String html = group;
		boolean find = false;
		String descrName = nameData.get(3);
		String descrizione = data.get(3);
		if(descrName.equals("descrizione"))
		{
			descrName= nameData.remove(3);
			descrizione = data.remove(3);
			find = true;
		}

		for(int i = 0 ; i<nameData.size(); i++)
		{
			html += cardt;
			html += nameData.get(i);
			html += cardm;
			html += nameData.get(i);
			html+= endid;
			html +=data.get(i);
			html+= buth;
			html+=nameData.get(i)+"\',\'"+data.get(i);
			html+=butf;
			html += cardf;
		}

		if(find)
		{
			html += cardt;
			html += descrName;
			html += cardm;
			html += descrizione;
			html += cardf;
		}
		html+="</div>";

		return html;
	}

	public String[] getTabella(String campo) throws SQLException
	{

		if(campo.equals("sviluppatore"))	
			return new String[]{"sviluppatore","nome"};


		if(campo.equals("categoria"))
			return new String[] {"categoria","nome"};

		String query= "SELECT TABLE_NAME"
				+ " FROM INFORMATION_SCHEMA.COLUMNS "
				+ "WHERE TABLE_SCHEMA = 'hobbyshop' "
				+ "AND COLUMN_NAME = '"+campo+"'";
		Statement st = db.createStatement();
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
			return new String[] {rs.getString(1),campo};
		return null;
	}

	public void modificaTabella(String tabella, String field, String value) throws SQLException, UnsupportedEncodingException, MessagingException
	{
		Statement st = db.createStatement();

		String[] table = getTabella(field);

		String tabella = table[0];
		String campo = table[1];
		String giac = "SELECT giacenza from prodotto WHERE id="+prodotto;
		Statement st2 = db.createStatement();
		ResultSet rs = st2.executeQuery(giac);
		if(rs.last())
		{
			System.out.println("OK GIACENZA: "+rs.getString("giacenza"));
			if(rs.getString("giacenza").equals("0") && campo.equals("giacenza"))
			{
				System.out.println("Entro primo if");
				if(Integer.parseInt(value)>0)
				{
					System.out.println("Entro secondo if");

					Statement st3 = db.createStatement();
					ResultSet rs2 = st3.executeQuery("SELECT nome FROM prodotto WHERE id="+prodotto);
					if(rs2.last())
					{

						String nome = rs2.getString("nome");
						System.out.println("Gestisco prenotazioni con: "+prodotto+" ,"+campo+" ,"+nome);

						gestisciPrenotazioni(prodotto,campo,nome);

					}
				}
			}
		}


		String query = "UPDATE "+tabella+ " SET "+campo+" ='"+value+"' WHERE id ="+prodotto;
		System.out.println(query);
		st.executeUpdate(query);

	}*/

	/*
	 * 
	 * 
  </div>
  <div class="card">
    <img class="card-img-top" src="..." alt="Card image cap">
    <div class="card-body">
      <h5 class="card-title">Card title</h5>
      <p class="card-text">This card has supporting text below as a natural lead-in to additional content.</p>
      <p class="card-text"><small class="text-muted">Last updated 3 mins ago</small></p>
    </div>
  </div>
  <div class="card">
    <img class="card-img-top" src="..." alt="Card image cap">
    <div class="card-body">
      <h5 class="card-title">Card title</h5>
      <p class="card-text">This is a wider card with supporting text below as a natural lead-in to additional content. This card has even longer content than the first to show that equal height action.</p>
      <p class="card-text"><small class="text-muted">Last updated 3 mins ago</small></p>
    </div>
  </div>
</div>
	 */

	public String getCategoria(String id ) throws SQLException
	{

		ArrayList<String> tmp= new ArrayList<String>();
		Statement st2 = db.createStatement();
		String query2  ="SELECT id FROM prodotto";
		ResultSet rs2 = st2.executeQuery(query2);
		while(rs2.next())
		{
			tmp.add(rs2.getString("id"));
		}
		if(!tmp.contains(id))
		{
			return null;
		}
		
		Statement st = db.createStatement();
		String query  ="SELECT categoria FROM prodotto WHERE id = "+id;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("categoria");
		}
		return null;
	}

	public String printMusica(String id) throws SQLException
	{

		String categoria = "musica";


		String qProdotto = "SELECT nome, foto,descrizione,costo,costo_spedizione,giacenza,timestamp FROM prodotto where id ="+id;
		String qSupporto ="SELECT titolo, tipo,genere,anno_uscita from supporto_audio where prodotto="+id;
		String supporto = getSupportoA(id);
		String album = getAlbum(id);
		String qAlbum="SELECT titolo FROM album where id="+album;
		String artista = getArtista(album);
		String qArtista="SELECT nome, data_nascita, luogo_nascita FROM artista where id="+artista;



		ArrayList<String> pArray = getData(qProdotto);
		ArrayList<String>  sArray = getData(qSupporto);
		ArrayList<String> fArray = getData(qAlbum);
		ArrayList<String> rArray = getData(qArtista);

		String html = "<h1> Categoria: "+categoria+"</h1> <br>";
		html += "<h3>Scegli il valore da modificare</h3>";
		html+="<h5> Dati sul prodotto </h5>";
		html+= buildCard(pArray,"prodotto",id)+"<br>";
		html+="<h5> Dati sul supporto audio </h5>";
		html+=buildCard(sArray,"supporto_audio",supporto)+"<br>";
		html+="<h5> Dati sul'album </h5>";

		html+=buildCard(fArray,"album",album)+"<br>";
		html+="<h5> Dati sull'artista </h5>";

		html+=buildCard(rArray,"artista",artista)+"<br>";

		System.out.println("QUESTO E' "+html);
		//	String qAttori="";

		//	String film= 
		//String qRuoli="SELECT ruolo FROM ruoli";


		return html+"<br>";
		//String qCanzoni="";
	}

	private String getSupportoA(String id) throws SQLException {
		Statement st = db.createStatement();
		String query  ="SELECT id FROM supporto_audio WHERE prodotto= "+id;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("id");
		}
		return null;
	}


	private String getArtista(String album) throws SQLException {
		Statement st = db.createStatement();
		String query  ="SELECT artista FROM album WHERE id="+album;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("artista");
		}
		return null;
	}


	private String getAlbum(String id) throws SQLException {

		Statement st = db.createStatement();
		String query  ="SELECT album FROM supporto_audio WHERE prodotto= "+id;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("album");
		}
		return null;	
	}


	public String printVideogiochi(String id) throws SQLException
	{


		String qProdotto = "SELECT nome, foto,descrizione,costo,costo_spedizione,giacenza,timestamp FROM prodotto where id ="+id;
		
		String supporto = getSupportoV(id);
		String qSupporto ="SELECT anno_uscita from supporto_video where prodotto="+id;
		
		String videogioco = getVideogioco(supporto);
		String qVideo= "SELECT titolo,genere FROM videogioco WHERE id="+videogioco;

		String sviluppatore= getSviluppatore(videogioco);
		String qSvil="SELECT nome,sede from sviluppatore where id="+sviluppatore;


		String categoria = "videogiochi";





		ArrayList<String> pArray = getData(qProdotto);
		ArrayList<String>  sArray = getData(qSupporto);
		ArrayList<String> fArray = getData(qVideo);
		ArrayList<String> rArray = getData(qSvil);

		String html = "<h1> Categoria: "+categoria+"</h1> <br>";
		html += "<h3>Scegli il valore da modificare</h3>";
		html+="<h5> Dati sul prodotto </h5>";
		html+= buildCard(pArray,"prodotto",id)+"<br>";
		
		html+="<h5> Dati sul supporto video </h5>";
		html+=buildCard(sArray,"supporto_video",supporto)+"<br>";
		
		html+="<h5> Dati sul videogioco </h5>";
		html+=buildCard(fArray,"videogioco",videogioco)+"<br>";
		
		html+="<h5> Dati sullo sviluppatore </h5>";
		html+=buildCard(rArray,"sviluppatore",sviluppatore)+"<br>";

		System.out.println("QUESTO E' "+html);
		//	String qAttori="";

		//	String film= 
		//String qRuoli="SELECT ruolo FROM ruoli";


		return html+"<br>";
		//String qCanzoni="";




	}

	private String getSviluppatore(String videogioco) throws SQLException {
		Statement st = db.createStatement();
		String query= "SELECT sviluppatore FROM videogioco WHERE id="+videogioco;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("sviluppatore");
		}
		return null;
	}


	private String getVideogioco(String supporto) throws SQLException {
		Statement st = db.createStatement();
		String query= "SELECT id FROM videogioco WHERE dvd="+supporto;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("id");
		}
		return null;
	}


	public String printLibri(String id) throws SQLException
	{

		String qProdotto = "SELECT nome, foto,descrizione,costo,costo_spedizione,giacenza,timestamp FROM prodotto where id ="+id;
		String supporto = getSupportoC(id);
		String qSupporto ="SELECT tipo,titolo,genere,ISBN, pagine, anno_uscita from supporto_cartaceo where prodotto="+id;
		String editore = getEditore(supporto);
		String qEditore="SELECT nome from editore where id="+editore;
		String autore = getAutore(editore);
		String qAutore="SELECT nome,cognome,sesso,data_nascita, luogo_nascita from autore where id="+autore;
		

		String categoria = "libri";
		
		ArrayList<String> pArray = getData(qProdotto);
		ArrayList<String>  sArray = getData(qSupporto);
		ArrayList<String> fArray = getData(qEditore);
		ArrayList<String> rArray = getData(qAutore);

		String html = "<h1> Categoria: "+categoria+"</h1> <br>";
		html += "<h3>Scegli il valore da modificare</h3>";
		html+="<h5> Dati sul prodotto </h5>";
		html+= buildCard(pArray,"prodotto",id)+"<br>";
		
		html+="<h5> Dati sul libro </h5>";
		html+=buildCard(sArray,"supporto_carteceo",supporto)+"<br>";
		
		html+="<h5> Dati sull'editore </h5>";
		html+=buildCard(fArray,"editore",editore)+"<br>";
		
		html+="<h5> Dati sull'autore </h5>";
		html+=buildCard(rArray,"autore",autore)+"<br>";

		System.out.println("QUESTO E' "+html);
		//	String qAttori="";

		//	String film= 
		//String qRuoli="SELECT ruolo FROM ruoli";


		return html+"<br>";
		
	}

	private String getAutore(String autore) throws SQLException {
		Statement st = db.createStatement();
		String query= "SELECT autore FROM supporto_cartaceo WHERE autore="+autore;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("autore");
		}
		return null;
	}


	private String getEditore(String supporto) throws SQLException {
		Statement st = db.createStatement();
		String query= "SELECT editore FROM supporto_cartaceo WHERE id="+supporto;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("editore");
		}
		return null;
	}


	private String getSupportoC(String id) throws SQLException {
		Statement st = db.createStatement();
		String query= "SELECT id FROM supporto_cartaceo WHERE prodotto="+id;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("id");
		}
		return null;
	}


	public String printFilm(String id) throws SQLException
	{



		String categoria = "film";
		String qProdotto = "SELECT nome, foto,descrizione,costo,costo_spedizione,giacenza,timestamp FROM prodotto WHERE id ="+id;
		String qSupporto ="SELECT anno_uscita FROM supporto_video WHERE prodotto="+id;

		String supporto = getSupportoV(id);
		String qFilm= "SELECT titolo, genere FROM film WHERE dvd="+supporto;
		String film = getFilm(supporto);
		String regista = getRegista(supporto);
		String qRegisti="SELECT nome as nome_regista, cognome, data_nascita, luogo_nascita FROM regista WHERE id="+regista;


		ArrayList<String> pArray = getData(qProdotto);
		ArrayList<String>  sArray = getData(qSupporto);
		ArrayList<String> fArray = getData(qFilm);
		ArrayList<String> rArray = getData(qRegisti);

		String html = "<h1> Categoria: "+categoria+"</h1> <br>";
		html += "<h3>Scegli il valore da modificare</h3>";
		html+="<h5> Dati sul prodotto </h5>";
		html+= buildCard(pArray,"prodotto",id)+"<br>";
		html+="<h5> Dati sul DVD </h5>";
		html+=buildCard(sArray,"supporto_video",supporto)+"<br>";
		html+="<h5> Dati sul film </h5>";

		html+=buildCard(fArray,"film",film)+"<br>";
		html+="<h5> Dati sul regista </h5>";

		html+=buildCard(rArray,"regista",regista)+"<br>";

		System.out.println("QUESTO E' "+html);
		//	String qAttori="";

		//	String film= 
		//String qRuoli="SELECT ruolo FROM ruoli";


		return html+"<br>";
	}


	private String getFilm(String supporto) throws SQLException {


		Statement st = db.createStatement();
		String query= "SELECT id FROM film WHERE dvd="+supporto;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("id");
		}
		return null;
	}


	public ArrayList<String> getData(String query) throws SQLException 
	{
		ArrayList<String> tmp = new ArrayList<String>();

		Statement st = db.createStatement();
		ResultSet rs = st.executeQuery(query);

		ResultSetMetaData rsmd = rs.getMetaData();
		int colCount = rsmd.getColumnCount();

		while (	rs.next())
		{
			for (int col=1; col <= colCount; col++) 
			{
				System.out.println("GETDATA :"+rs.getString(col));
				tmp.add(rsmd.getColumnName(col));
				tmp.add(rs.getString(col));
			}
			rs.next();

		}




		return tmp;

	}

	public String buildCard(ArrayList<String> array, String tabella, String id)
	{


		String html = "";

		String base = "<div class=\"card-group\">";
		html += base;

		ArrayList<String> nomi = new ArrayList<String>();
		ArrayList<String> valori = new ArrayList<String>();

		for (int i = 0; i < array.size(); i++) {

			System.out.println("array: "+array.get(i));
			if (i % 2 == 0)
				nomi.add(array.get(i));
			else
				valori.add(array.get(i));

		}

		for(int i = 0; i < nomi.size(); i++)
		{

			String cardinit= "<div class=\"card\"><div class=\"card-body\"> <h5 class=\"card-title\">";

			String titolo= nomi.get(i);

			String cardbody= "</h5><p class=\"card-text\" id=\""+nomi.get(i)+"_"+tabella+"\">";

			String value = valori.get(i);

			String buth ="<br><br><br><button type=\"button\" class=\"btn btn-outline-info\" onclick=\"showLabel(\'";

			String func= nomi.get(i)+"\',\'"+valori.get(i)+"\',\'"+tabella+"\',\'"+id;

			String butf = "\')\">Modifica</button> </p> "; //TOLGO </p>

			String endcard = " </div></div>" ;

			html+=(cardinit+titolo+cardbody+value+buth+func+butf+endcard);


		}

		html+= "</div>";

		return html;

	}


	private String getRegista(String supporto) throws SQLException {
		Statement st = db.createStatement();
		String query  ="SELECT regista FROM film WHERE dvd= "+supporto;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("regista");
		}
		return null;	
	}


	private String getSupportoV(String id) throws SQLException {
		Statement st = db.createStatement();
		String query  ="SELECT id FROM supporto_video WHERE prodotto= "+id;
		ResultSet rs = st.executeQuery(query);
		if(rs.last())
		{
			return rs.getString("id");
		}
		return null;
	}




	public void modificaTabella(String prodotto, String tabella, String campo, String value, String identificatore) throws SQLException, UnsupportedEncodingException, MessagingException
	{
		Statement st = db.createStatement();

		if(tabella.equals("prodotto") && campo.equals("giacenza"))
		{
			String giac = "SELECT giacenza from prodotto WHERE id="+prodotto;
			Statement st2 = db.createStatement();
			ResultSet rs = st2.executeQuery(giac);
			if(rs.last())
			{
				System.out.println("OK GIACENZA: "+rs.getString("giacenza"));
				if(rs.getString("giacenza").equals("0") && campo.equals("giacenza"))
				{
					System.out.println("Entro primo if");
					if(Integer.parseInt(value)>0)
					{
						System.out.println("Entro secondo if");

						Statement st3 = db.createStatement();
						ResultSet rs2 = st3.executeQuery("SELECT nome FROM prodotto WHERE id="+prodotto);
						if(rs2.last())
						{

							String nome = rs2.getString("nome");
							System.out.println("Gestisco prenotazioni con: "+prodotto+" ,"+campo+" ,"+nome);

							gestisciPrenotazioni(prodotto,campo,nome);

						}
					}
				}
			}

		}


		String query = "UPDATE "+tabella+ " SET "+campo+" ='"+value+"' WHERE id ="+identificatore;
		System.out.println(query);
		st.executeUpdate(query);

	}


}
