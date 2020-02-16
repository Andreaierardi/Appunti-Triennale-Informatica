<?php include("db.php");?>
<?php include("Template/top.php");?>

<?php
ensure_logged_in("login.php","Effettua il login per poter effettuare un ordine");


$carrello = $_SESSION["carrello"];
if(isset($_REQUEST['prodotto']))
$prodotto = $_REQUEST['prodotto'];
if(isset($_REQUEST['quantita']))
$quantita = $_REQUEST['quantita'];
$ordine = $_SESSION['ordine'];

if(!checkDateCarta($_SESSION['id']))
{
  $flag=0;
  redirect("ordini.php", "La tua carta è scaduta");
}

if(isset($_REQUEST['all']))
{
  $flag=1;
  $result = buyAll($carrello, $ordine);

  if(!$result)
  {
    $flag = 0;
    redirect("ordini.php", "Uno dei tuoi ordini non è stato completato", $flag);
  }
  else {
    $flag=1;
    redirect("ordini.php", "Hai acquistato tutti i prodotti!", $flag);

  }
}
else {

  $result = completeOrder($prodotto,$quantita,$ordine,$carrello);

  if(!$result)
  {
    $flag = 0;
    redirect("ordini.php", "Il tuo ordine non ha avuto successo", $flag);
  }
  else {
    $flag=1;
    redirect("ordini.php", "Hai acquistato il prodotto con successo!", $flag);

  }

}

?>
