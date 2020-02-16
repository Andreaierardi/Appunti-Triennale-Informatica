<%@ include file="top.jsp"%>

<div id="container">
	<% 
	out.println("<h4>Benvenuto, <br></h4>"
				  + "<table class=\"table\">"
			 + "<tr><td>Totale utenti: " + db.nUtenti() + "</td></tr>"
			 + "<tr><td>Totale prodotti: " + db.nPrdotti()+ "</td></tr>"
	
			 + "<tr><td>Totale ordini: " + db.nOrdini()+ "</td></tr>"
				  + "</table>");
	




%>
</div>

<%@ include file="footer.jsp"%>
