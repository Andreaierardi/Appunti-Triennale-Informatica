<%@ include file="top.jsp"%>

<script>
	/*
	 * <label for="exampleInputEmail1">Nome immagine</label> 
	
	 <input
	name="immagine" type="text" class="form-control"
		id="exampleInputEmail1" aria-describedby="emailHelp"
		placeholder="Immagine del prodotto ">
	 */

	var clicked = [];
	function showLabel(id, nome, tabella, identificatore) {
		var l = document.getElementById(id + "_" + tabella);

		if (!clicked.includes(id + "_" + tabella)) {

			var form = document.createElement("form");
			form.setAttribute("method", "post");
			//form.setAttribute("action", "");

			var label = document.createElement("label");
			label.setAttribute("for", "exampleInputEmail1");
			label.innerHTML = "Inserisci un nuovo valore";

			var input = document.createElement("input");
			input.setAttribute("name", id);
			input.setAttribute("type", "text");
			input.setAttribute("class", "form-control");
			input.setAttribute("id", "exambleInputEmail1");
			input.setAttribute("aria-describedby", "emailHelp");
			input.setAttribute("placeholder", name);

			var input2 = document.createElement("input");
			input2.setAttribute("name", tabella);
			input2.setAttribute("value", tabella);
			input2.style.display = "none"; //("display","none");

			console.log("ident: " + identificatore);
			var input3 = document.createElement("input");
			input3.setAttribute("name", "identificatore");
			input3.setAttribute("value", identificatore);
			input3.style.display = "none"; //("display","none");

			var but = document.createElement("button");
			but.setAttribute("type", "submit");
			but.innerHTML = "Invio";
			but.setAttribute("class", "btn btn-outline-success");
			form.appendChild(label);
			form.appendChild(input);
			form.appendChild(input2);
			form.appendChild(input3);
			form.appendChild(but);

			l.appendChild(form);

			clicked.push(id + "_" + tabella);
		}

	}
</script>


<%
	ArrayList<String> par = new ArrayList<String>();
	ArrayList<String> name = new ArrayList<String>();
	ArrayList<String> tabelle = new ArrayList<String>();
	ArrayList<String> identificatori = new ArrayList<String>();

	String id = null;

	Enumeration en = request.getParameterNames();
	if (en != null) {
		while (en.hasMoreElements()) {

			String p = (String) en.nextElement();
			if (p.equals("id")) {
				id = (String) request.getParameter("id");

				if (!id.isEmpty()) 
					session.setAttribute("id", id);
				else
					{
						id=null;
						response.sendRedirect("modifica_prodotti.jsp");
					}
				
			}

			else {
				System.out.println("p:" + p);
				par.add((String) request.getParameter(p));
				name.add(p);

				String p2 = (String) en.nextElement();

				System.out.println("GET tabella: " + (String) request.getParameter("tabella"));
				tabelle.add((String) request.getParameter(p2));

				String p3 = (String) en.nextElement();

				identificatori.add((String) request.getParameter("identificatore"));

			}
		}
	}

	if (par != null) {
		for (int i = 0; i < par.size(); i++) {

			System.out.println("Tabella: " + tabelle.get(i));
			db.modificaTabella((String) session.getAttribute("id"), tabelle.get(i), name.get(i), par.get(i),
					identificatori.get(i));
			response.sendRedirect("modifica_prodotti.jsp");

		}
	}

	if (id != null ) {
		String cat = db.getCategoria(id);
		
		
		String print = null;
		if (cat!=null && cat.equals("1")) {
			String ris = db.printFilm(id);
			out.print(ris);
		}

		if (cat!=null && cat.equals("2")) {
			String ris = db.printMusica(id);
			out.print(ris);

		}

		if (cat!=null && cat.equals("3")) {
			String ris = db.printVideogiochi(id);
			out.print(ris);

		}

		if (cat!=null && cat.equals("4")) {
			String ris = db.printLibri(id);
			out.print(ris);

		}
		
		if(print==null)
		{
			out.print("<br> <br> <h2> Nessun prodotto corrispondente all'id inserito</h2> <br> <br> ");
			out.print("<a class=\"btn btn-primary\" href=\"modifica_prodotti.jsp\" role=\"button\">Indietro</a>");
	
		}
	}
%>



<%@ include file="footer.jsp"%>
