<?php include("db.php");?>
<?php include("Template/top.php");?>

<?php
ensure_logged_in("login.php","Effettua il login prima di aggiungere al carrello");

$prodotto = $_SESSION['prodotto'];
$utente = $_SESSION['id'];
$quantita = $_REQUEST['quantita'];
echo $quantita;
echo $prodotto;
echo $utente;



//=====> C'E DA FARE IL CONTROLLO SE L'ITEM È GIÀ PRESENTE IN DB
$result = insertProduct($prodotto, $utente,$quantita);
if(!$result)
{
  $flag = 0;
  redirect("visualizza_prodotto.php?id=".$prodotto, "Prodotto già inserito nel carrello", $flag);
}
else {
  $flag=1;
  redirect("visualizza_prodotto.php?id=".$prodotto, "Prodotto inserito con successo nel carrello", $flag);

}

//$_SESSION['numel'] =getCartEl($_SESSION['carrello'])-1;

?>
