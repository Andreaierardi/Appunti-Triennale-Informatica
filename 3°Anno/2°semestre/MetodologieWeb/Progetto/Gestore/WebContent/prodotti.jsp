<%@ include file="top.jsp"%>


<h1>Prodotti</h1>

<% 
	out.print(db.visualizzaProdotti());
	%>
<p>Quale operazione vuoi fare?</p>
<a class="btn btn-primary" href="aggiungi_prodotti.jsp" role="button">Aggiungi un prodotto</a>
<a class="btn btn-primary" href="modifica_prodotti.jsp" role="button">Modifica un prodotto</a>
<a class="btn btn-primary" href="rimuovi_prodotti.jsp" role="button">Rimuovi un prodotto</a>

<br>
<br>
<%@ include file="footer.jsp"%>
