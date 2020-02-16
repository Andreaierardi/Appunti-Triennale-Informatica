<%@ include file="top.jsp"%>


	<a class="btn btn-primary" href="prodotti.jsp" role="button">Indietro</a>


<h1>Modifica dei prodotti</h1>

<% 
	out.print(db.visualizzaProdotti());
%>
	
<p>Inserisci l'id del prodotto che vuoi modificare</p>

<form action="modifica.jsp" method="POST">
 <input name="id" type="number" class="form-control" id="durata1" aria-describedby="emailHelp" placeholder="Id del prodotto">
 <br>
 

<button type="submit" class="btn btn-primary">Invia</button>
</form>	

<%@ include file="footer.jsp"%>
