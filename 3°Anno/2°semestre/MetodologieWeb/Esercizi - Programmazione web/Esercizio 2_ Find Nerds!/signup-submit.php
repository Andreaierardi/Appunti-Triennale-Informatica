<!-- Andrea Ierardi 20018785 -->

<?php include("top.html"); ?>

<?php
/* Si ottengono i valori dal POST del form di sign-up e vengono inseriti in un array*/
$array[] = $nome = $_POST['name'];
$array[] =$gender = $_POST["gender"];
$array[] =$age = $_POST['age'];
$array[] =$personality= $_POST['personality'];
$array[] =$os= $_POST['os'];
$array[] =$min = $_POST['min'];
$array[] =$max= $_POST['max'];


/* Conversione da array a string e poi viene aggiornato il file*/
$user = implode(",", $array);

$file = 'singles.txt';
$current = file_get_contents($file);
$current .= $user."\n";
file_put_contents($file, $current) or die("<br>Error - can't find file 'single.txt'");
?>

<!-- Pagina di Benvenuto-->
<div>
	<p> Welcome to NerdLuv, <?=$nome ?>! </p>

  <p> Now <a href="matches.php">
    log in to see your matches!
  </a> </p>


</div>

<?php include("bottom.html"); ?>
