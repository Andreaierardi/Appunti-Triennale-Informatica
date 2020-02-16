<%@ include file="top.jsp"%>


<script type="text/javascript">
	var last = null;
	var ncanzoni = 1;
	var nattori = 1;
	
	function checked() {
		console.log("OKJ")
		var get = document.getElementById("cat");
		var cat = get.value;
		console.log(cat);

		if (cat == "film") {
			show("film");
		}

		if (cat == "musica") {
			show("musica");
		}

		if (cat == "videogiochi") {
			show("videogiochi");

		}
		if (cat == "libri") {
			show("libri");

		}

	}
	function show(id) {
		if (last != null)
			hide(last);
		var x = document.getElementById(id);
		x.style.display = "block";
		last = id;
	}
	function hide(id) {
		var x = document.getElementById(id);
		x.style.display = "none";
	}
	
	
	function rimCanzone()
	{
		
		if(ncanzoni> 1)
		{
			var b = document.getElementById("append");
			b.removeChild(b.lastChild);
			ncanzoni--;
			
		}
		
		
	}
	function addCanzone()
	{

		var butt= document.getElementById("append");
		ncanzoni++;
		var ht = "<h5>  <strong> Canzone n."+ncanzoni+"</strong></h5>";
		var lab= "<label for=\"exampleInputEmail1\">Titolo di una canzone</label>";
		var ip= "<input name=\"canzone\" type=\"text\" class=\"form-control\" id=\"exampleInputEmail1\"aria-describedby=\"emailHelp\" placeholder=\"Titolo della canzone\">";
		var lab2= "<label for=\"exampleInputEmail1\">Durata della canzone </label>";
		var ip2= "<input name=\"durata\" type=\"text\" class=\"form-control\" id=\"durata\"aria-describedby=\"emailHelp\" placeholder=\"Durata\">";
		
		var html = document.createElement("div");
		html.innerHTML =(ht+lab+ip+lab2+ip2);
		butt.appendChild(html);
		
		
	}
	
	/*JS per gli attori */

	function rimAttore()
	{
		
		if(nattori> 1)
		{
			var b = document.getElementById("append_film");
			b.removeChild(b.lastChild);
			nattori--;
			
		}
		
		
	}
	function addAttore()
	{

		var butt= document.getElementById("append_film");
		nattori++;
		var ht = "<h5>  <strong> Attore n."+nattori+"</strong></h5>";
		
	
		
		var lab= "<label for=\"exampleInputEmail1\">Nome dell'attore</label>";
		var ip= "<input name=\"nome_attore\" type=\"text\" class=\"form-control\" id=\"exampleInputEmail1\"aria-describedby=\"emailHelp\" placeholder=\"Nome\">";
		
		var lab2= "<label for=\"exampleInputEmail1\">Cognome dell'attore</label>";
		var ip2= "<input name=\"cognome_attore\" type=\"text\" class=\"form-control\" id=\"cognome_attore\"aria-describedby=\"emailHelp\" placeholder=\"Cognome\">";
		
		var lab3= "<label for=\"exampleInputEmail1\">Sesso dell'attore</label>";
		var ip3= "<input name=\"sesso_attore\" type=\"text\" class=\"form-control\" id=\"sesso_attore\"aria-describedby=\"emailHelp\" placeholder=\"Sesso\">";
		
			
		var lab4= "<label for=\"exampleInputEmail1\">Data dell'attore</label>";
		var ip4= "<input name=\"data_attore\" type=\"text\" class=\"form-control\" id=\"data_attore\"aria-describedby=\"emailHelp\" placeholder=\"Data\">";
		
	 		
		var lab5= "<label for=\"exampleInputEmail1\">Luogo dell'attore</label>";
		var ip5= "<input name=\"luogo_attore\" type=\"text\" class=\"form-control\" id=\"luogo_attore\"aria-describedby=\"emailHelp\" placeholder=\"Luogo\">";
		 
		var html = document.createElement("div");
		html.innerHTML =(ht+lab+ip+lab2+ip2+lab3+ip3+lab4+ip4+lab5+ip5);
		butt.appendChild(html);
		
		
	}
</script>


<%


String nome = (String) request.getParameter("nome");
String categoria = (String) request.getParameter("categoria");
String immagine = (String) request.getParameter("immagine");
String descrizione = (String) request.getParameter("descrizione");
String prezzo = (String) request.getParameter("prezzo");
String prezzo_spedizione = (String) request.getParameter("prezzo_spedizione");
String giacenza = (String) request.getParameter("prezzo_spedizione");

if(nome!=null && categoria!=null && immagine!=null && descrizione!=null && prezzo!=null && prezzo_spedizione!=null && giacenza!=null)
{
	if(categoria.equals("musica"))
	{
		String titolo = (String) request.getParameter("titolo_album");
		String genere = (String) request.getParameter("genere_album");
		String anno= (String) request.getParameter("anno_album");
		String artista= (String) request.getParameter("artista");
		String data= (String) request.getParameter("data_artista");
		String luogo = (String) request.getParameter("luogo_artista");
		String tipo= (String )request.getParameter("tipo_album");
		String [] canzone = request.getParameterValues("canzone");
		String [] durata= request.getParameterValues("durata");
		
		for(int i =0 ; i<canzone.length; i++)
		{
			System.out.println(canzone[i]+" d:"+durata[i]);
		}
		
		System.out.println(titolo+" "+ genere+" "+  anno+" "+ artista+" "+  data +" "+ luogo+" "+  tipo);
		if(titolo!=null && tipo!=null && genere!=null && anno!=null && artista!=null && data!=null && luogo!=null && canzone!=null && durata!=null)
		{
			
			String prodotto = db.addProdottoMusica( nome,  "2", tipo, immagine,  descrizione,  prezzo,  prezzo_spedizione,  giacenza, titolo, genere, anno, artista, data,luogo, canzone, durata);
		}

	}
	if(categoria.equals("film"))
	{
			String titolo = (String) request.getParameter("titolo_film");
			String genere= (String) request.getParameter("genere_film");
		
			String anno=(String) request.getParameter("anno_film");
			String nomer = (String) request.getParameter("nome_regista");
			String cognomer = (String) request.getParameter("cognome_regista");
			String datar = (String) request.getParameter("data_regista");
			String luogor = (String) request.getParameter("luogo_regista");

			
			String [] ruoli = request.getParameterValues("ruolo");
			String [] nomea =  request.getParameterValues("nome_attore");
			String [] cognomea = request.getParameterValues("cognome_attore");
			String [] sessoa=  request.getParameterValues("sesso_attore");
			String [] dataa = request.getParameterValues("data_attore");
			String [] luogoa =request.getParameterValues("luogo_attore");

			if(titolo!=null && genere!=null && anno!=null && nomer!=null && datar!=null && luogor!=null && 
					ruoli!=null && nomea!=null && cognomea!=null && sessoa!=null && dataa!=null && luogoa!=null)
			{
				
				String prodotto = db.addProdottoFilm(nome,  "1", immagine,  descrizione,  prezzo,  prezzo_spedizione, giacenza,
						titolo, genere, anno, nomer, cognomer, datar,luogor, ruoli,nomea,cognomea,sessoa,dataa,luogoa);
			}
	}
	if(categoria.equals("videogiochi"))
	{
		String titolo = (String) request.getParameter("titolo_videogioco");
		String genere= (String) request.getParameter("genere_videogioco");
		String sviluppatore= (String) request.getParameter("sviluppatore");
		String sede= (String) request.getParameter("sede_sviluppatore");

		String anno = (String) request.getParameter("anno_videogioco");
		
		if(titolo!=null && genere!=null && sviluppatore!=null && sede!=null && anno!=null)
		{
			String prodotto=	db.addProdottoVideogioco(nome,  "3", immagine,  descrizione,  prezzo,  prezzo_spedizione,  giacenza,titolo, genere, sviluppatore, sede, anno);
		}
	}
	if(categoria.equals("libri"))
	{
		String titolo = (String) request.getParameter("titolo_libro");
		String tipo = (String) request.getParameter("tipo_libro");
		String genere = (String) request.getParameter("genere_libro");
		
		String nomeautore = (String) request.getParameter("na_libro");
		String cognomeautore= (String) request.getParameter("ca_libro");
		String sessoautore= (String) request.getParameter("sa_libro");
		String dataautore= (String) request.getParameter("da_libro");
		String luogoautore= (String) request.getParameter("la_libro");

		String editore = (String) request.getParameter("editore");
		String ISBN= (String) request.getParameter("isbn");
		String pagine = (String) request.getParameter("pagine");
		String anno = (String) request.getParameter("anno_libro");

		if(titolo!=null && tipo!=null && genere!=null && nomeautore!=null 
				&&cognomeautore!=null && sessoautore!=null && dataautore!=null && luogoautore!=null && editore!=null &&
				ISBN !=null && pagine !=null && anno!=null)
		{
			String prodotto = db.addProdottoLibro(nome,  "4", immagine,  descrizione,  prezzo,  prezzo_spedizione, 
					giacenza,titolo, tipo,genere, nomeautore, cognomeautore, sessoautore, dataautore,
					luogoautore, editore, ISBN, pagine, anno);
					
		}
	}

}


%>
<form id="informazioni" method="post" action="">

	<a class="btn btn-primary" href="prodotti.jsp" role="button">Indietro</a>
	
	<h3>
		<strong>Aggiungi prodotto</strong>
	</h3>

	<div class="form-group">
		<label for="exampleInputEmail1">Nome</label> <input name="nome"
			type="text" class="form-control" id="exampleInputEmail1"
			aria-describedby="emailHelp" placeholder="Nome del prodotto">
	</div>
	<div class="form-group">
		<label for="exampleInputEmail1">Categoria</label> <select
			onchange="checked()" id="cat" name="categoria"
			class="custom-select custom-select-lg mb-3">
			<option selected>Scegli la categoria</option>
			<%
				ArrayList<String> list = db.listCategorie();

				for (String cat : list) {
					out.println("<option value=\"" + cat + "\">" + cat + "</option>");
				}
			%>

		</select>
	</div>
	<div class="form-group">
		<label for="exampleInputEmail1">Nome immagine</label> <input
			name="immagine" type="text" class="form-control"
			id="exampleInputEmail1" aria-describedby="emailHelp"
			placeholder="Immagine del prodotto ">
	</div>
	<div class="form-group">
		<label for="exampleInputEmail1">Descrizione</label> <input
			name="descrizione" type="text" class="form-control"
			id="exampleInputEmail1" aria-describedby="emailHelp"
			placeholder="Descrizione del prodotto">
	</div>
	<div class="form-group">
		<label for="exampleInputEmail1">Prezzo</label> <input type="text"
			name="prezzo" class="form-control" id="exampleInputEmail1"
			aria-describedby="emailHelp" placeholder="Prezzo del prodotto">
	</div>
	<div class="form-group">
		<label for="exampleInputEmail1">Prezzo di spedizione</label> <input
			name="prezzo_spedizione" type="text" class="form-control"
			id="exampleInputEmail1" aria-describedby="emailHelp"
			placeholder="Prezzo di spedizione">
	</div>
	<div class="form-group">
		<label for="exampleInputEmail1">Giacenza</label> <input type="text"
			name="giacenza" class="form-control" id="exampleInputEmail1"
			aria-describedby="emailHelp" placeholder="Giacenza del prodotto">
	</div>

	<br>

	<div class="form-group hide" id="musica">
		<div id="append">
			<h5>
				<strong> Aggiungi dati per un CD o un vinile </strong>
			</h5>

			<label for="exampleInputEmail1">Titolo dell'album</label> <input
				name="titolo_album" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Titolo dell'album"> <label
				for="exampleInputEmail1">Tipo</label> <select onchange="checked()"
				id="cat" name="tipo_album"
				class="custom-select custom-select-lg mb-3">
				<option selected>Scegli il tipo di supporto</option>
				<option value="CD">CD</option>
				<option value="Vinile">Vinile</option>

			</select> <label for="exampleInputEmail1">Genere </label> <input
				name="genere_album" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Genere"> <label for="exampleInputEmail1">Anno
				di uscita</label> <input name="anno_album" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Anno di uscita">

			<h5>
				<strong> Dati dell'artista</strong>
			</h5>

			<label for="exampleInputEmail1">Nome dell'artista </label> <input
				name="artista" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Nome artista"> <label for="exampleInputEmail1">Data
				di nascita dell'artista (formato dd/mm/yyyy)</label> <input
				name="data_artista" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Data di nascita"> <label
				for="exampleInputEmail1">Luogo di nascita della'artista</label> <input
				name="luogo_artista" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Luogo di nascita"> <br>
			<h5>
				<strong> Canzone n.1 </strong>
			</h5>

			<label for="exampleInputEmail1">Titolo di una canzone</label> <input
				name="canzone1" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Titolo della canzone"> <label
				for="exampleInputEmail1">Durata della canzone</label> <input
				name="durata1" type="text" class="form-control" id="durata1"
				aria-describedby="emailHelp" placeholder="Durata"> <br>
		</div>
		<button type="button" id="addsong" onclick="addCanzone()"
			class="btn btn-info">Aggiungi canzone</button>
		<button type="button" id="remsong" onclick="rimCanzone()"
			class="btn btn-info">Rimuovi ultima canzone</button>

	</div>







	<div class="form-group hide" id="film">
		<div id="append_film">
			<h5>Aggiungi dati per un film</h5>

			<label for="exampleInputEmail1">Titolo del film</label> <input
				name=titolo_film "
			type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Titolo del film"> <label
				for="exampleInputEmail1">Genere del film</label> <input
				name="genere_film" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Genere"> <label for="exampleInputEmail1">Anno
				di uscita</label> <input name="anno_film" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Anno di uscita">

			<h5>Dati del regista</h5>

			<label for="exampleInputEmail1">Nome del regista</label> <input
				name="nome_regista" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Nome"> <label for="exampleInputEmail1">Cognome
				del regista</label> <input name="cognome_regista" type="text"
				class="form-control" id="exampleInputEmail1"
				aria-describedby="emailHelp" placeholder="Cognome"> <label
				for="exampleInputEmail1">Data di nascita del
				regista(dd/mm/yyyy)</label> <input name="data_regista" type="text"
				class="form-control" id="exampleInputEmail1"
				aria-describedby="emailHelp" placeholder="Data di nascita">
			<label for="exampleInputEmail1">Luogo di nascita</label> <input
				name="luogo_regista" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Luogo di nascita">

			<h5>
				<strong> Attore n.1 </strong>
			</h5>

			<label for="exampleInputEmail1">Nome dell'attore </label> <input
				name="nome_attore" type="text" class="form-control"
				id="exampleInputEmail1" aria-describedby="emailHelp"
				placeholder="Nome"> <label for="exampleInputEmail1">Cognome
				dell'attore</label> <input name="cognome_attore" type="text"
				class="form-control" id="durata1" aria-describedby="emailHelp"
				placeholder="Cognome"> <label for="exampleInputEmail1">Sesso
			</label> <input name="sesso_attore" type="text" class="form-control"
				id="durata1" aria-describedby="emailHelp" placeholder="Sesso">

			<label for="exampleInputEmail1">Data di nascita</label> <input
				name="data_attore" type="text" class="form-control" id="durata1"
				aria-describedby="emailHelp" placeholder="Data di nascita">

			<label for="exampleInputEmail1">Luogo di nascita</label> <input
				name="luogo_attore" type="text" class="form-control" id="durata1"
				aria-describedby="emailHelp" placeholder="Luogo di nascita">
			<br>
		</div>
		<button type="button" id="addact" onclick="addAttore()"
			class="btn btn-info">Aggiungi attore</button>
		<button type="button" id="remact" onclick="rimAttore()"
			class="btn btn-info">Rimuovi ultimo attore</button>

	</div>




	<div class="form-group hide" id="videogiochi">
		<h5>Aggiungi dati per un videogioco</h5>

		<label for="exampleInputEmail1">Titolo del videogioco</label> <input
			name="titolo_videogioco" type="text" class="form-control"
			id="exampleInputEmail1" aria-describedby="emailHelp"
			placeholder="Titolo del videogioco"> <label
			for="exampleInputEmail1">Genere </label> <input
			name="genere_videogioco" type="text" class="form-control" id="genere"
			aria-describedby="emailHelp" placeholder="Genere"> <label
			for="exampleInputEmail1">Anno di uscita</label> <input
			name="anno_videogioco" type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="Anno">

		<h5>Dati sviluppatore</h5>

		<label for="exampleInputEmail1">Nome dello sviluppatore</label> <input
			name="sviluppatore" type="text" class="form-control"
			id="sviluppatore" aria-describedby="emailHelp" placeholder="Nome">

		<label for="exampleInputEmail1">Sede dello sviluppatore</label> <input
			name="sede_sviluppatore" type="text" class="form-control"
			id="durata1" aria-describedby="emailHelp" placeholder="Luogo">


	</div>


	<div class="form-group hide" id="libri">
		<h5>Aggiungi dati per un libro</h5>

		<label for="exampleInputEmail1">Titolo del libro</label> <input
			type="text" class="form-control" id="exampleInputEmail1"
			aria-describedby="emailHelp" placeholder="Titolo del libro">

		<label for="exampleInputEmail1">Tipo </label> <input name="tipo_libro"
			type="text" class="form-control" id="tipo"
			aria-describedby="emailHelp" placeholder="Tipo"> <label
			for="exampleInputEmail1">Genere</label> <input name="genere_libro"
			type="text" class="form-control" id="genere"
			aria-describedby="emailHelp" placeholder="Genere"> 
			
			<label for="exampleInputEmail1">Codice ISBN</label> <input name="isbn"
			type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="ISBN"> <label
			for="exampleInputEmail1">Pagine del libro</label> <input
			name="pagine" type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="Numero delle pagine">

		<label for="exampleInputEmail1">Anno di uscita</label> <input
			name="anno_libro" type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="Anno di uscita">
			
					<h5>Dati dell'autore</h5>
			
			<label
			for="exampleInputEmail1">Nome</label> <input name="na_libro"
			type="text" class="form-control" id="na_libro"
			aria-describedby="emailHelp" placeholder="Nome dell'autore">

		<label for="exampleInputEmail1">Cognome </label> <input
			name="ca_libro" type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="Cognome dell'autore">

		<label for="exampleInputEmail1">Sesso (M/F)</label> <input
			name="sa_libro" type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="Sesso dell'autore">

		<label for="exampleInputEmail1">Data di nascita</label> <input
			name="da_libro" type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="Data di nascita"> <label
			for="exampleInputEmail1">Luogo di nascita</label> <input
			name="luogo_attore" type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="Luogo di nascita">

		<label for="exampleInputEmail1">Luogo di nascita</label> <input
			name="la_libro" type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="Luogo di nascita">


		<h5>Dati dell'editore</h5>

		<label for="exampleInputEmail1">Editore</label> <input name="editore"
			type="text" class="form-control" id="durata1"
			aria-describedby="emailHelp" placeholder="Nome dell'editore">

		
	</div>


	<button type="submit" class="btn btn-primary">Invia</button>

</form>
<br>
<%@ include file="footer.jsp"%>
