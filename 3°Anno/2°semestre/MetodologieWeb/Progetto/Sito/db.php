<?php

function connect()
{

  $dsn = 'mysql:dbname=HobbyShop;host=127.0.0.1;port=3306';
  $db = new PDO($dsn, 'root', '');

  //  $dsn = 'mysql:dbname=20018785;host=127.0.0.1;port=3306';
  //  $db = new PDO($dsn, '20018785', '20018785');
  return $db;
}
if (!isset($_SESSION)) {

  session_start(); }

  function is_password_correct($name, $password) {

    $db = connect();

    //   $dsn = 'mysql:dbname=test;host=127.0.0.1;port=3306';
    //   $db = new PDO($dsn, '20018785', '20018785');
    $name = $db->quote($name);
    $rows = $db->query("SELECT password FROM utente WHERE email = $name");
    if ($rows) {
      foreach ($rows as $row) {
        $correct_password = $row["password"];
        return $password === $correct_password;
      }
    } else {
      return FALSE;   # user not found
    }
  }


  # Redirects current page to the given URL and optionally sets flash message.
  function redirect($url, $flash_message, $flag) {
    if ($flash_message) {
      $_SESSION["flash"] = $flash_message;

    }
    if($flag)
    {
      $_SESSION['flag'] = $flag;
    }
    # session_write_close();
    header("Location: $url");
    die;
  }


  function perform_query($query)
  {
    // $dsn = 'mysql:dbname=test;host=127.0.0.1;port=3306';
    try {
      $db = connect();
      //   $db = new PDO($dsn, '20018785', '20018785');

      $rows = $db->query($query);
      return $rows;
    } catch (PDOException $e) {
      ?>
      <p>Sorry, a database error occurred.</p>
      <?php
      return NULL;
    }
  }

  function insertReview($testo,$valutazione, $prodotto)
  {
    $utente = $_SESSION['id'];
    $num = "SELECT * FROM recensione";
    $num = perform_query($num);
    $id = ($num -> rowCount()*1)+1;
    $query="INSERT INTO recensione (id,prodotto,utente,valore,descrizione,timestamp) VALUES (DEFAULT,'".$prodotto."','".$utente."','".$valutazione."','".$testo."',DEFAULT)";
    insertDB($query);
  }

  function getOrderEl($utente)
  {
    $query = "SELECT id FROM ordine WHERE utente=$utente";
    $f = perform_query($query);
    foreach ($f as $key => $value) {
      $valore = $value['id'];
    }

    //echo "ILVALORE: ".$valore;
    return $valore;
  }

  function completeOrder($prodotto,$quantita,$ordine,$carrello)
  {

    if(mt_rand(1, 4)==2)
    return false;

    $query = "INSERT INTO cont_ordine (id,ordine,prodotto, quantita,timestamp) VALUES (DEFAULT,'".$ordine."','".$prodotto."','".$quantita."',CURRENT_TIMESTAMP)";
    insertDB($query);

    $query ="DELETE FROM cont_carrello WHERE carrello=$carrello AND prodotto=$prodotto";
    perform_query($query);



    return true;
  }

  function checkDateCarta($id)
  {
    $query = "SELECT carta.scadenza FROM carta WHERE utente=$id";
    $rows = perform_query($query);

    foreach ($rows as $key => $value) {
      $scadenza= $value['scadenza'];
    }
    $data = explode("/",$scadenza);
    $anno = $data[2];
    $mese = $data[1];
    $giorno = $data[0];

    $curretday = date("d");
    $currentmonth = date("m");
    $currentyear=date("Y");

    if(strcmp($anno,$currentyear)>1 )
    return false;

    if(strcmp($anno,$currentyear)==0)
    {
      if(strcmp($mese,$currentmonth)>1)
      return false;
      if(strcmp($mese,$currentmonth)==0)
      {
        if(strcmp($giorno,$curretday)>1)
        {
          return false;
        }
      }
    }
    return true;

  }

  function buyAll($carrello, $ordine)
  {
    $query_carrello = "SELECT * FROM cont_carrello WHERE carrello = $carrello";
    $rows = perform_query($query_carrello);

    foreach ($rows as $key => $value) {
      $prodotto = $value['prodotto'];
      $prob = mt_rand(1, 4);
      if($prob==2)
      return false;

      $qta = $value['quantita'];
      $query_ordine = "INSERT INTO cont_ordine (id,ordine,prodotto, quantita, timestamp) VALUES (DEFAULT, '".$ordine."','".$prodotto."','".$qta."',CURRENT_TIMESTAMP)";
      insertDB($query_ordine);

      $query ="DELETE FROM cont_carrello WHERE carrello=$carrello";
      perform_query($query);
    }
    return true;
  }
  function bookProduct($prodotto, $utente)
  {
    $check = "SELECT * FROM prenotazione where prodotto = $prodotto AND utente = $utente";
    $rows = perform_query($check);
    if($rows->Rowcount())
    return false;
    $query = "INSERT INTO prenotazione (id,prodotto,utente,timestamp) VALUES (DEFAULT, '".$prodotto."', '".$utente."',DEFAULT)";
    insertDB($query);
    return true;
  }

  function insertProduct($prodotto, $utente, $quantita)
  {

    /*    $search_dati_prod = perform_query("SELECT titolo, regista.nome as nome_regista,
    regista.cognome as cognome_regista, genere, anno_uscita
    FROM supporto_video
    JOIN film ON supporto_video.id = film.dvd
    JOIN regista ON regista.id = film.regista
    WHERE supporto_video.prodotto= $prodotto");

    $film = array();
    $film = $search_dati_prod->fetch(PDO::FETCH_BOTH);*/


    $carrello = getUserCart($utente);
    //======DA TOGLIERE=======
    $_SESSION['carrello'] = $carrello;

    $check = "SELECT * FROM cont_carrello where prodotto = $prodotto AND carrello = $carrello";
    $rows = perform_query($check);
    if($rows->Rowcount())
    return false;
    echo "OK";
    //    echo carrello;

    $query =  "INSERT INTO cont_carrello (carrello, prodotto, quantita)VALUES ('".$carrello."','".$prodotto."','".$quantita."')";
    insertDB($query);
    return true;

  }

  function getCartEl($carrello)
  {
    $query = "SELECT COUNT(*) as 'numel' FROM `cont_carrello` WHERE carrello=$carrello";
    $f = perform_query($query);
    foreach ($f as $key => $value) {
      $valore = $value['numel'];
    }

    //echo "ILVALORE: ".$valore;
    return $valore;
  }


  function getUserCart($user)
  {

    $query_carrello = "SELECT id FROM carrello WHERE utente=". "'$user'";
    $f = perform_query($query_carrello);

    foreach ($f as $key => $value) {
      $carrello = $value["id"];
    }
    return $carrello;
  }

  function insertDB($sql)
  {
    try {

      $conn = connect();

      //   $dsn = 'mysql:dbname=test;host=127.0.0.1;port=3306';

      //   $conn = new PDO($dsn, '20018785', '20018785');
      // set the PDO error mode to exception
      $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

      // use exec() because no results are returned
      $conn->exec($sql);
      echo "New record created successfully";
    }
    catch (PDOException $e) {
      echo $sql . "<br>" . $e->getMessage();
    }
  }

  function ensure_logged_in($visitedPage,$errore) {

    $_SESSION["currentPage"] = $visitedPage;

    if (!isset($_SESSION["email"])) {
      redirect("login.php", $errore. " alla pagina", 0);
    }
  }

  # Returns all grades for the given student, as an associative array.
  function get_infos($email) {
    //  $dsn = 'mysql:dbname=test;host=127.0.0.1;port=3306';

    //  $db = new PDO($dsn, '20018785', '20018785');

    $db = connect();

    $email = $db->quote($email);
    return $db->query("SELECT *
      FROM utente WHERE email = $email");
    }

    function show_film($prodotto)
    {

      $search_dati = perform_query(
        "SELECT attore.nome, attore.cognome,attore.sesso,attore.data_nascita, attore.luogo_nascita, ruoli.ruolo
        FROM supporto_video
        JOIN film ON supporto_video.id = film.dvd
        JOIN regista ON regista.id = film.regista
        JOIN ruoli ON ruoli.film= film.id
        JOIN attore ON ruoli.attore= attore.id
        WHERE supporto_video.prodotto=$prodotto");

        $search_dati_prod = perform_query("SELECT titolo, regista.nome as nome_regista,
          regista.cognome as cognome_regista, genere, anno_uscita
          FROM supporto_video
          JOIN film ON supporto_video.id = film.dvd
          JOIN regista ON regista.id = film.regista
          WHERE supporto_video.prodotto= $prodotto");

          $film = array();
          $film = $search_dati_prod->fetch(PDO::FETCH_BOTH);
          list($titolo,$nome_regista, $cognome_regista, $genere, $anno_uscita) = $film;
          ?>
          <div class= "dati_prodotto">

            <div class="card-deck">
              <div class="card">
                <div class="card-header">
                  <h5> Informazioni sul film </h5>
                </div>
                <ul class="list-group list-group-flush">
                  <li class="list-group-item">Titolo: <?= $titolo ?> </li>
                  <li class="list-group-item">Regista: <?= $nome_regista." ".$cognome_regista ?> </li>
                  <li class="list-group-item">Genere: <?= $genere?> </li>
                  <li class="list-group-item">Anno di uscita: <?= $anno_uscita ?> </li>
                </ul>
              </div>

              <div class="card" >
                <div class="card-header">
                  <?php
                  $actor = array();
                  $actor = $search_dati->fetch(PDO::FETCH_BOTH);
                  ?>
                  <h5> Cast </h5>
                </div>
                <ul class="list-group list-group-flush">

                  <?php
                  while($actor)
                  {
                    list($nome_attore,$cognome_attore, $sesso,$data_nascita, $luogo_nascita, $ruolo)=$actor
                    ?>

                    <li class="list-group-item"> <?= $nome_attore . " " . $cognome_attore . " ". $sesso. " ". $data_nascita." ".$luogo_nascita." ".$ruolo ?>  </li>
                    <?php
                    $actor = $search_dati->fetch(PDO::FETCH_BOTH);
                  }

                  ?>
                </ul>
              </div>
            </div>
          </div>
          <?php
        }

        /* CATEGORIA 2 */
        function show_album($prodotto)
        {
          $search= perform_query(
            "SELECT album.id, supporto_audio.titolo, supporto_audio.tipo, supporto_audio.genere, supporto_audio.anno_uscita, artista.nome as nome_artista, artista.data_nascita, artista.luogo_nascita
            FROM supporto_audio
            JOIN album ON album.id = supporto_audio.album
            JOIN artista ON artista.id= supporto_audio.artista
            WHERE supporto_audio.prodotto = $prodotto");



            $album= array();
            $album = $search->fetch(PDO::FETCH_BOTH);
            list($album_id, $titolo,$tipo, $genere, $anno_uscita, $nome_artista, $data_nascita, $luogo_nascita) = $album;

            $search_dati= perform_query(
              "SELECT titolo, durata FROM canzone where album=$album_id");

            ?>

            <div class= "dati_prodotto">

              <div class="card-deck">
                <div class="card">
                  <div class="card-header">
                    <h5> Informazioni sull'album </h5>
                  </div>
                  <ul class="list-group list-group-flush">
                    <li class="list-group-item">Titolo: <?= $titolo ?></li>
                    <li class="list-group-item">Genere: <?= $genere ?> </li>
                    <li class="list-group-item">Anno di uscita: <?= $anno_uscita ?></li>
                    <li class="list-group-item">Supporto audio: <?= $tipo ?> </li>
                  </ul>
                </div>





                <div class="card" >
                  <div class="card-header">
                    <h5> Dati sull'artista </h5>
                  </div>
                  <ul class="list-group list-group-flush">
                    <li class="list-group-item">Nome: <?= $nome_artista ?> </li>
                    <li class="list-group-item">Luogo: <?= $luogo_nascita ?></li>
                    <li class="list-group-item">Inizio di carriera: <?= $data_nascita ?></li>
                  </ul>
                </div>


                <div class="card" >
                  <div class="card-header">
                    <?php
                    $song = array();
                    if ($search_dati->rowCount() > 0)
                    {

                      $song = $search_dati->fetch(PDO::FETCH_BOTH);
                    }
                    ?>
                    <h5> Brani nell'album </h5>
                  </div>
                  <ul class="list-group list-group-flush">

                    <?php
                    while($song)
                    {
                      list($titolo,$durata)=$song;
                      ?>

                      <li class="list-group-item"> <?= "Titolo: ". $titolo . " <br>Durata: " . $durata ?>  </li>
                      <?php
                      $song = $search_dati->fetch(PDO::FETCH_BOTH);
                    }

                    ?>
                  </ul>
                </div>



              </div>
            </div>

            <?php
          }

          function show_videogame($prodotto)
          {
            $search= perform_query("SELECT titolo, genere, sviluppatore.nome as sviluppatore, sede, anno_uscita
              FROM supporto_video
              JOIN videogioco ON supporto_video.id = videogioco.dvd
              JOIN sviluppatore ON sviluppatore.id = videogioco.sviluppatore
              WHERE supporto_video.prodotto= $prodotto");

              $video= array();
              $video = $search->fetch(PDO::FETCH_BOTH);
              list($titolo,$genere, $sviluppatore, $sede, $anno_uscita) = $video;
              ?>

              <div class= "dati_prodotto">

                <div class="card-deck">
                  <div class="card">
                    <div class="card-header">
                      <h5> Informazioni sul videogioco </h5>
                    </div>
                    <ul class="list-group list-group-flush">
                      <li class="list-group-item">Titolo: <?= $titolo ?></li>
                      <li class="list-group-item">Genere: <?= $genere ?> </li>
                      <li class="list-group-item">Anno di uscita: <?= $anno_uscita ?></li>
                    </ul>
                  </div>





                  <div class="card" >
                    <div class="card-header">
                      <h5> Dati sullo sviluppatore </h5>
                    </div>
                    <ul class="list-group list-group-flush">
                      <li class="list-group-item">Nome: <?= $sviluppatore ?> </li>
                      <li class="list-group-item">Luogo della sede: <?= $sede ?></li>
                    </ul>
                  </div>
                </div>
              </div>

              <?php
            }


            function show_book($prodotto)
            {
              $search= perform_query("SELECT titolo, tipo, genere, ISBN,pagine, anno_uscita, editore.nome,
                autore.nome, autore.cognome,autore.sesso, autore.data_nascita, autore.luogo_nascita
                FROM supporto_cartaceo
                JOIN editore ON editore.id = supporto_cartaceo.editore
                JOIN autore ON supporto_cartaceo.autore = autore.id
                WHERE supporto_cartaceo.prodotto= $prodotto");

                $libro= array();
                $libro = $search->fetch(PDO::FETCH_BOTH);
                list($titolo,$tipo,$genere,$isbn,$pagine,$anno_uscita,$editore, $autoren,$autorec,$autores,$autoredn,$autoreln) = $libro;
                ?>

                <div class= "dati_prodotto">

                  <div class="card-deck">
                    <div class="card">
                      <div class="card-header">
                        <h5> Informazioni sul libro </h5>
                      </div>
                      <ul class="list-group list-group-flush">
                        <li class="list-group-item">Titolo: <?= $titolo ?></li>
                        <li class="list-group-item">Tipo: <?= $tipo ?> </li>
                        <li class="list-group-item">Editore: <?= $editore ?></li>

                        <li class="list-group-item">Genere: <?= $genere ?> </li>
                        <li class="list-group-item">Codice ISBN: <?= $isbn ?> </li>
                        <li class="list-group-item">Numero di pagine: <?= $pagine ?> </li>
                        <li class="list-group-item">Anno di uscita: <?= $anno_uscita ?></li>
                      </ul>
                    </div>


                    <div class="card" >
                      <div class="card-header">
                        <h5> Dati sull'autore </h5>
                      </div>
                      <ul class="list-group list-group-flush">
                        <li class="list-group-item">Nome: <?= $autoren." ".$autorec ?> </li>
                        <li class="list-group-item">Sesso: <?= $autores ?></li>
                        <li class="list-group-item">Data di nascita: <?= $autoredn ?> </li>
                        <li class="list-group-item">Luogo: <?= $autoreln ?> </li>


                      </ul>
                    </div>
                  </div>
                </div>

                <?php
              }


              function getMediarecensioni($prodotto)
              {
                  $somma = 0 ;
                  $n = 0 ;
                  $search= perform_query("SELECT valore from recensione where prodotto=$prodotto");
                  foreach ($search as $key => $value) {
                    $somma+= $value['valore'];
                    $n= $n+1;
                  }

                  if($n==0 || $somma==0)
                    $valore= 0;
                  else
                    $valore =  round($somma/$n);


                      $str ="";
                      for($l = 0 ; $l< $valore; $l++)
                      {
                        $str.="<img src='img/star.gif'>";
                      }
                      for($l = 0 ; $l< 4-$valore; $l++)
                      {
                        $str.="<img src='img/nstar.gif'>";
                      }
                      return $str;
              }
              ?>
