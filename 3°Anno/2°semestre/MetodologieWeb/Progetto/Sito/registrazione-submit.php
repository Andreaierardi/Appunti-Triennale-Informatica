<?php include_once("db.php");?>

<?php

/*DEFINIRE CARRELLO E ORDINE!!!!*/


$nome = $_POST["nome"];
$cognome = $_POST["cognome"];
$email = $_POST["email"];
$password = $_POST["password"];
$data_nascita = $_POST["data_nascita"];


$indirizzo = $_POST["via"];
$civico = $_POST["civico"];
$citta = $_POST["citta"];
$provincia = $_POST["provincia"];
$cap = $_POST["cap"];
$stato  = $_POST["stato"];

$telefono = $_POST["telefono"];
$carta = $_POST["carta"];
$nome_intestatario = $_POST['nome_carta'];
$cognome_intestatario= $_POST['cognome_carta'];
$codice_carta = $_POST["codice_carta"];
$scadenza_carta = $_POST["scadenza_carta"];

print($nome. "<br>". $cognome ."<br>". $email."<br>". $password . "<br>"."<br>". $data_nascita."<br>".$indirizzo."<br>".
$citta."<br>".
$provincia."<br>".
$cap."<br>".
$stato."<br>".
$telefono."<br>".
$carta ."<br>".
$codice_carta ."<br>".
$scadenza_carta);

//$id_indirizzo =
//$id_carta
/*
$utente_carta
$nome_intestatario
$cognome_intestatario
$numero
$codice_carta
$scadenza_carta
*/
$check_email = "SELECT * from utente WHERE email = '$email'";
$check_card = "SELECT * from carta WHERE numero= '$carta'";


$rows = perform_query($check_email);
$rows2 = perform_query($check_card);
if($rows->rowCount())
redirect("registrazione.php","Errore - Account con email già registrata",0);
if($rows2->rowCount())
redirect("registrazione.php","Errore - Account con carta di credito già registrata",0);

$queryind = "INSERT INTO indirizzo (id,via, civico, citta, provincia, stato,cap) VALUES (DEFAULT, '".$indirizzo."','".$civico."','".$citta."','".$provincia."','".$stato."', '".$cap."')";
insertDB($queryind);
$q = "SELECT id FROM indirizzo WHERE via='".$indirizzo."' AND civico='".$civico."' AND cap='".$cap."' ORDER BY id DESC";
$r = perform_query($q);
foreach ($r as $key => $v) {
  $id_indirizzo = $v['id'];
}

$querycar = "INSERT INTO carta (id, nome_intestatario, cognome_intestatario, numero, codice, scadenza) VALUES
(DEFAULT,'". $nome_intestatario."','".$cognome_intestatario."', '".$carta."', '".$codice_carta."','".$scadenza_carta."')";
insertDB($querycar);
$q2 = "SELECT id FROM carta WHERE numero=$carta";
$r2 = perform_query($q2);
foreach ($r2 as $key => $v2) {
  $id_carta = $v2['id'];
}

$queryut = "INSERT INTO utente (id,email, password, nome, cognome, data_nascita, indirizzo, carta, telefono) VALUES
(DEFAULT, '".$email."','".$password."','".$nome."','".$cognome."','".$data_nascita."','".$id_indirizzo."', '".$id_carta."', '".$telefono."')";
insertDB($queryut);

$q3 = "SELECT id FROM utente WHERE carta='".$id_carta."' AND indirizzo='".$id_indirizzo."'";
$r3 = perform_query($q3);
foreach ($r3 as $key => $v3) {
  $id_utente= $v3['id'];
}

$query_cart = "INSERT INTO carrello (id, utente) VALUES (DEFAULT, '".$id_utente."')";
insertDB($query_cart);
$query_ordine = "INSERT INTO ordine (id, utente) VALUES(DEFAULT, '".$id_utente."')";
insertDB($query_ordine);

redirect("login.php", "Registrazione avvenuta con successo",1);


?>
