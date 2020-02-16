<?php include("db.php");?>

<?php
ensure_logged_in("login.php","Efettua il login prima di prenotare un prodotto");

$prodotto = $_SESSION['prodotto'];
$utente = $_SESSION['id'];


//=====> C'E DA FARE IL CONTROLLO SE L'ITEM È GIÀ PRESENTE IN DB
$result = bookProduct($prodotto, $utente);

if(!$result)
{  $alert= "Prodotto già prenotato";
  $flag = 2;
}
else {
  $alert = "Prenotazione effettuata con successo";
  $flag=1;
}
redirect("visualizza_prodotto.php?id=".$prodotto,$alert, $flag);
//$_SESSION['numel'] =getCartEl($_SESSION['carrello'])-1;


?>
