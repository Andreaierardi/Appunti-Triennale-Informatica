<!-- Andrea Ierardi 20018785 -->
<?php include("top.html"); ?>

<!-- Includo il file con funzioni utili -->
<?php include("functions.php");?>


<?php /* Ottengo il nome inviato dal form*/
  $nome = $_GET['name'];
?>
<h1>
  Matches for name <?= $nome; ?>
</h1>

<div class = "match" >
<?php

/* Apro il file e ricerco l'user nel file. Se non trova l'utente o il file ritorna un errore*/
  $lines = file('singles.txt') or die("<br>Error - can't find file 'single.txt'");
  $user = searchUser($nome, $lines);
  if(!$user)
    die("<br>User not found");

/* Ottengo una lista dei match e controllo che non sia vuota.
Se vuota scrivo che non ho trovato nessun match compatibile*/
  $matches = matchesList($lines, $user);
  if(!$matches)
    noMatch();

/* Riempo un'array con i tipi in modo da poterli stampare e scorro anche i dati dei match e li renderizzo*/
  for($i = 0 ; $i < sizeof($matches); $i++)
  {
    $type = array("name","gender","age","type","OS");
    $person = explode(",",$matches[$i]);

    stampaPersona($person , $type);
  }
?>

</div>
<?php include("bottom.html"); ?>
