<%@ include file="top.jsp"%>


<%

String id = (String) request.getParameter("id");
if(id!=null)
	db.removeProdotto(Integer.parseInt(id));
%>

	<a class="btn btn-primary" href="prodotti.jsp" role="button">Indietro</a>

<h1>Prodotti</h1>

<% 
	out.print(db.visualizzaProdotti());
	%>
	
<p>Inserisci l'id del prodotto che vuoi rimuovere</p>

<form action="" method="POST">
 <input name="id" type="text" class="form-control" id="durata1" aria-describedby="emailHelp" placeholder="Id del prodotto">
 <br>
 

<button type="submit" class="btn btn-primary">Invia</button>
</form>

<br>
<br>
<%@ include file="footer.jsp"%>
