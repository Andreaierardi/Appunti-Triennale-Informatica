<!-- < Andrea Ierardi 20018785 > -->
<?php include("top.html"); ?>

<?php include("common.php"); ?>

<?php

/* Si ottengono il nome e il cognome con una get */
$n = $_GET["firstname"];
$c = $_GET["lastname"];

/* Si ricercano il miglior risultato relativo*/
list($nome, $cognome) = searchBestResult($n, $c);

/* Una volta ottenuto il risultato relativo, si esegue la query */
/* La query restituisce la lista di tutti i film di un dato attore */
$query = "SELECT (ROW_NUMBER() OVER (ORDER BY movies.year DESC, 2 ASC)) as '#', movies.name as Title, movies.year as Year
FROM actors JOIN roles ON roles.actor_id= actors.id
JOIN movies ON movies.id= roles.movie_id
WHERE actors.last_name =  '$cognome' AND actors.first_name = '$nome'
ORDER BY 1, 2 ASC " ;

/* Eseguita la query, si stampa la lista dei film (se trovati)*/
printRow($nome,  $cognome, $query);

?>

<?php include("bottom.html"); ?>
