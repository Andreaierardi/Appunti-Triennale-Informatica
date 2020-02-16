<%@ include file="top.jsp"%>

<%

String id = (String) request.getParameter("id");
if(id!=null)
	db.removeUtente(Integer.parseInt(id));
%>

<h1>Utenti</h1>

<% 
	out.print(db.visualizzaUtenti());
	%>
	
<h5> Quale utente vuoi eliminare? (scrivere l'id)</h5>
<form action="" method="POST">
 <input name="id" type="text" class="form-control" id="durata1" aria-describedby="emailHelp" placeholder="Id dell'utente">
 <br>
 

<button type="submit" class="btn btn-primary">Invia</button>
</form>

<br>
<br>
<%@ include file="footer.jsp"%>
