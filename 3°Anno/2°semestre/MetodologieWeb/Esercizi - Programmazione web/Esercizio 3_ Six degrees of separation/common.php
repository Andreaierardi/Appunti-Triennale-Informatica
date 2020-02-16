<!-- < Andrea Ierardi 20018785 > -->
<?php

//Classe con funzioni comuni nei file

/*Cerca il miglior risultato relativo al nome dell'attore che è stato digitato
e salva il risultato in un array che poi viene ritornato
*/
function searchBestResult($nome, $cognome)
{

  $query = "SELECT nome, cognome
  FROM
  (SELECT actors.first_name as nome, actors.last_name as cognome, actors.film_count, actors.id
  FROM actors
  WHERE actors.film_count = (SELECT MAX(actors.film_count) FROM actors WHERE actors.last_name =
'$cognome')
  AND actors.first_name LIKE '$nome%' AND actors.last_name= '$cognome'
  ORDER BY actors.id) as T
  LIMIT 1";

  $best  = perform_query($query);
  if ($best->rowCount())
  {
      foreach ($best as $row)
      {
          $array = array($row["nome"], $row["cognome"]);
      }
  }
  return $array;
}

//Funzione che esegue la query
function perform_query($query) {

$dsn = 'mysql:dbname=test;host=127.0.0.1;port=3306';


  try {
  //  $db = new PDO($dsn, 'root', '');
   $db = new PDO($dsn, '20018785', '20018785');
    $rows = $db->query($query);

    return $rows;
  } catch (PDOException $ex) {
    ?>
    <p>Sorry, a database error occurred.</p>
    <?php
    return NULL;
  }
}

/* Funzione che stampa i film trovati con la
formattazione richiesta in consegna
Si usano classi left, centro e right per identare al meglio i dati
*/
function printRow($nome, $cognome, $query)
{

  $rows = perform_query($query);
  ?>
  <h1> Result for <?=  $nome ." ". $cognome ?> </h1>
  <?php
  if ($rows->rowCount()) {  ?>
    <table>
      <p id="testotabella"> All films </p>
      <tr>
          <th class="left" >#</th>
          <th class="centro" >Title</th>
          <th class="right">Year</th>
      </tr>
    <?php
    foreach ($rows as $row) {
        ?>
        <tr>
          <td class="left"> <?= $row["#"] ?> </td>
          <td class="centro" > <?= $row["Title"] ?> </td>
          <td class="right"> <?= $row["Year"] ?> </td>
        </tr>
        <?php
    }
  ?> </table>
<?php
}
//Se non viene trovato l'attore
else { ?>

  <p class="nf_text"> Actor <strong > <?= "'" . $nome . "' " . "'".  $cognome . "'" ?> </strong >not found </p>

  <?php
}

 }
?>
