<!-- < Andrea Ierardi 20018785 > -->

<?php include("top.html"); ?>

<?php include("common.php"); ?>

  <?php

  /* Si ottengono il nome e il cognome con una get */
  $n = $_GET["firstname"];
  $c = $_GET["lastname"];

  /* Si ricercano il miglior risultato relativo*/
  list($nome, $cognome) = searchBestResult($n, $c);

/* La query restituisce la lista di tutti i film che il
dato attore ha fatto insieme a Kevin Bacon */
  $query = "SELECT (ROW_NUMBER() OVER (ORDER BY Year DESC, 2 ASC)) as '#', Title, Year
      FROM
      (
          SELECT movies.name as Title, movies.year as Year, movies.id as id_film
          FROM  actors
        JOIN roles ON roles.actor_id= actors.id
        JOIN movies ON movies.id= roles.movie_id
          WHERE actors.last_name =  '$cognome' AND actors.first_name = '$nome'
      ) as T
      LEFT JOIN roles ON roles.movie_id= id_film
      LEFT JOIN actors ON actors.id = roles.actor_id
      WHERE actors.first_name='Kevin' AND actors.last_name='Bacon'
      ORDER BY 1, 2 ASC " ;

/* Eseguita la query, si stampa la lista dei film (se trovati)*/
    printRow($nome, $cognome,$query);

    ?>

  <?php include("bottom.html"); ?>
