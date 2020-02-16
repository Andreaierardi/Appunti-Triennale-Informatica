<?php include("Template/top.php"); ?>
<?php include_once("db.php"); ?>

<?php

$prodotto = $_GET["id"];
$_SESSION['prodotto'] = $prodotto;

if(isset($_POST['testo']) && isset($_POST['valutazione']))
{
  $testo = $_POST['testo'];
  $valutazione = $_POST['valutazione'];
  insertReview($testo, $valutazione,$prodotto);
}

$rows = perform_query("SELECT * FROM prodotto where id=" . $prodotto . ";");
$string =   array();
$string =$rows->fetch(PDO::FETCH_BOTH);
#print_r($string);
$array = array($string[0], $string[1],$string[2], $string[3],$string[4],$string[5],$string[6], $string[7]);
list($id, $nome, $categoria, $foto, $descrizione, $costo, $spedizione, $giacenza) = $array;


/*
SELECT recensione.descrizione, utente.nome, utente.cognome FROM recensione JOIN utente ON utente.id = recensione.utente JOIN prodotto on prodotto.id = recensione.prodotto where prodotto.id = 1
*/
//$search_rec = perform_query("SELECT recensione.descrizione, utente.nome, utente.cognome FROM recensione JOIN utente ON utente.id = recensione.utente JOIN prodotto on prodotto.id = recensione.prodotto where prodotto.id = $id");

if(isset($_POST['ordine']))
{
  $ordine = $_POST['ordine'];
  if($ordine=="uno")
  {

    $q = "SELECT recensione.descrizione, utente.nome, utente.cognome, recensione.valore
    FROM recensione
    JOIN utente ON utente.id = recensione.utente JOIN prodotto on prodotto.id = recensione.prodotto
     where prodotto.id = $id
    ORDER BY valore DESC";
    $search_rec = perform_query($q);

  }
  if($ordine =="due")
  {

    $q = "SELECT recensione.descrizione, utente.nome, utente.cognome, recensione.valore
    FROM recensione
    JOIN utente ON utente.id = recensione.utente JOIN prodotto on prodotto.id = recensione.prodotto
     where prodotto.id = $id
    ORDER BY valore ASC";
    $search_rec = perform_query($q);
  }

}
else
  $search_rec = perform_query("SELECT recensione.descrizione, utente.nome, utente.cognome, recensione.valore FROM recensione JOIN utente ON utente.id = recensione.utente JOIN prodotto on prodotto.id = recensione.prodotto where prodotto.id = $id");


/*
RICERCA TUTTO
SELECT titolo, regista.nome as nome_regista,
regista.cognome as cognome_regista, genere, anno_uscita, attore.nome,
attore.cognome,attore.sesso,attore.data_nascita, attore.luogo_nascita,
ruoli.ruolo
FROM supporto_video
JOIN film ON supporto_video.id = film.dvd
JOIN regista ON regista.id = film.regista JOIN ruoli ON ruoli.film= film.id
JOIN attore ON ruoli.attore= attore.id
WHERE supporto_video.prodotto= $id




RICERCA FILM E REGISTA
SELECT titolo, regista.nome as nome_regista,
regista.cognome as cognome_regista, genere, anno_uscita
FROM supporto_video
JOIN film ON supporto_video.id = film.dvd
JOIN regista ON regista.id = film.regista
WHERE supporto_video.prodotto= $id


RICERCA ATTORI
SELECT attore.nome, attore.cognome,attore.sesso,attore.data_nascita, attore.luogo_nascita, ruoli.ruolo FROM supporto_video JOIN film ON supporto_video.id = film.dvd JOIN regista ON regista.id = film.regista JOIN ruoli ON ruoli.film= film.id JOIN attore ON ruoli.attore= attore.id
WHERE supporto_video.prodotto=$id
*/

?>

<script>
function addqta(max)
{
  var qt = document.getElementById("quantity");
  var val = qt.value;
  if(val < max)
    val++;
  qt.value= val;
}

function rmqta()
{
  var qt = document.getElementById("quantity");
  var val = qt.value;
  if(val >1)
  val--;
  qt.value= val;

}

function startAnimation(value)
{
  for(i= value; i>=1; i--)
  {
    var x = document.getElementById("star"+i);
    x.setAttribute("src","img/star.gif");
  }
  for(i= value+1; i<=4; i++)
  {
    var y= document.getElementById("star"+i);
    y.setAttribute("src","img/nstar.gif");
  }

  var h = document.getElementById("hidestart");
  h.value = value;
}
</script>

<div class = "prodotto">

  <row>
    <a href="prodotti.php?id=<?= $categoria?>" id="backbutton">&#8249;</a>

    <div class="col-sm-12">

      <img src="img/<?= $foto ?>"  >


      <div class="nome_prodotto">
        <h2> <?= $nome ?> </h2>
        <br>
        <div class="descrizione_prodotto">

          <p class="text-secondary"> <?= $descrizione ?> </p>
        </div>
        <p> Prezzo : <?= $costo ?> € </p>
        <p> Prezzo di spedizione : <?= $spedizione ?> €</p>
        <p> Media recensioni: <?= getMediarecensioni($prodotto)?></p>
        <?php
        if($giacenza <=3 && $giacenza >=1)
        {
          ?>
          <h5> Affrettati! Solo <?= $giacenza?> disponibile/i! </h5>
          <?php
        }

        if($giacenza <=0 )
        { ?>
          <h5> Il prodotto non è disponibile, prenotalo! </h5>
          <?php
        }



        if($giacenza >0 )
        {
          ?>
          <form method="POST"  action="carrello_submit.php">


            <button type="submit" class="btn btn-warning" name="buy">Aggiungi al carrello</button>
            <br>
            <br>
            <div class="quantita" style="display=inline-block">
              <button type="button" class="btn btn-info" onclick="rmqta()" > - </button>

              <input type="number" name="quantita" id="quantity" value="1" readonly>
              <button type="button" class="btn btn-info" onclick="addqta('<?= $giacenza?>')"> + </button>

            </div>
          </form>
          <?php
        }
        else {
          ?>
          <form method="POST"  action="prenota-submit.php">
            <button type="submit" class="btn btn-warning" name="prenota">Prenota ora!</button>
          </form>
          <br>

          <?php

        }
        ?>

        <?php if(isset($_SESSION['flash']))
        {
          if($_SESSION['flag']==1)
          {
          ?>
          <div class="alert alert-success" role="alert">
          <?php
        }
        else{
          ?>
          <div class="alert alert-warning" role="alert">
<?php
        }
        ?>
            <?= $_SESSION['flash']; $_SESSION['flag']=null; $_SESSION['flash']=null?>
          </div>

        <?php
      }

?>
      </div>

    </div>

  </row>
  <?php

  if($categoria==1)
  show_film($id);
  else if($categoria==2)
  show_album($id);
  else if($categoria==3)
  show_videogame($id);
  else if($categoria==4)
  show_book($id);
  ?>
  <form style="float:right" method="POST"  action="">
    <fieldset class="form-group">
      <div class="row">
        <legend class="col-form-label col-sm-6 pt-0">Ordina per:</legend>
        </div>
        <div class="row" style="text-align:left">
        <div class="col-sm-10">
          <div class="form-check">
            <input class="form-check-input" type="radio" name="ordine" id="gridRadios1" value="uno" checked>
            <label class="form-check-label" for="gridRadios1">
              Recensioni piu' migliori
            </label>
          </div>
          <div class="form-check">
            <input class="form-check-input" type="radio" name="ordine" id="gridRadios2" value="due">
            <label class="form-check-label" for="gridRadios2">
              Recensioni peggiori
            </label>
          </div>

        </div>
        <input class="btn btn-primary" type="submit" value="Submit">

      </div>
    </fieldset>
  </form>

  <div class="recensioni" style="margin-left:7rem">


    <div class="titolo-rec">
      <h1 > Recensioni </h1>
    </div>

    <?php
    if($search_rec->rowCount())
    {
      foreach ($search_rec as $key => $rec){
        $str ="";
        for($l = 0 ; $l< $rec["valore"]; $l++)
        {
          $str.="<img src='img/star.gif'>";
        }
        for($l = 0 ; $l< 4-$rec["valore"]; $l++)
        {
          $str.="<img src='img/nstar.gif'>";
        }
        ?>
        <div class="rec">

          <p> Utente:<strong> <?= $rec["nome"] ." " . $rec["cognome"]?>  </strong></p>
          <p> Voto: <?=  $str ?> </p>
          <p> Recensione <?= '<br>'. $rec["descrizione"]?>   </p>
        </div>
        <?php
      }
    }
    else {
      ?>
      <h5> Nessuna recensione per questo prodotto </h5>




      <?php
    }
    ?>

    <div class="scrivi_recensione">

      <?php    if(isset($_SESSION["email"]))
      { ?>
        <form action="visualizza_prodotto.php?id=<?= $prodotto ?>" method="post">

          <div class="form-group">

            <label for="exampleFormControlTextarea1"> Lascia la tua recensione! </label>
            <div class="stars" >
              <img id="star1" src='img/star.gif' onmouseover=startAnimation(1)>
              <img id="star2"src='img/nstar.gif'onmouseover=startAnimation(2)>
              <img id="star3"src='img/nstar.gif'onmouseover=startAnimation(3)>
              <img id="star4"src='img/nstar.gif'onmouseover=startAnimation(4)>
              <input type="text" id="hidestart" name="valutazione" value="1">

            </div>
            <textarea class="form-control" id="exampleFormControlTextarea1" rows="3" name="testo" minlength ="80"  maxlength="512"></textarea>
            <button type="submit" class="btn btn-primary">Invia recensione</button>
          </div>
        </form>
        <?php
      }
      else {

        ?>
        <p> Effettua il   <a href="login.php">login   </a> o   <a href="registrazione.php"> registrati   </a>per lasciare una recensione! </p>
        <?php
      }
      ?>

    </div>
  </div>
</div>

<?php include("Template/footer.php") ?>
