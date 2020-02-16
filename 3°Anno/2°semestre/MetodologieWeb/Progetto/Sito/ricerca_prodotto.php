<?php include("db.php"); ?>

<?php include("Template/top.php"); ?>

<?php


function printNotFound($ricerca)
{ ?>
  <div class="card" >
    <div class="card-header">
      <h5> Nessun risultato trovato per <?= $ricerca ?> </h5>
    </div>
  </div>
  <?php
}


if(isset($_POST['cerca']) )
{
  $ricerca = $_POST["cerca"];
  $_SESSION['ricerca']= $ricerca;
}


if(isset($_POST['ordine']))
{
  $ordine = $_POST['ordine'];
  if($ordine=="uno")
  {

    /*
    SELECT *,AVG(valore) as media
    FROM prodotto
    JOIN recensione ON prodotto.id = recensione.prodotto
    GROUP BY prodotto.id
    ORDER BY media DESC
    */

    $categoria = "SELECT prodotto.id,nome,categoria,foto,prodotto.descrizione,costo,costo_spedizione,giacenza,prodotto.timestamp, recensione.prodotto, AVG(valore) as media
    FROM prodotto
    JOIN recensione ON prodotto.id = recensione.prodotto
    WHERE nome LIKE '%" . $_SESSION['ricerca']. "%'
    GROUP BY prodotto.id
    ORDER BY media DESC";
    $rows = perform_query($categoria);

  }
  if($ordine =="due")
  {

    $categoria = "SELECT *
    FROM prodotto
    WHERE nome
    LIKE '%" . $_SESSION['ricerca']. "%'
    ORDER BY timestamp DESC";
    $rows = perform_query($categoria);
  }
  if($ordine=="tre")
  {
    $categoria = "SELECT *
    FROM prodotto
    WHERE nome
    LIKE '%" . $_SESSION['ricerca']. "%' ORDER BY costo ASC";
    $rows = perform_query($categoria);

  }
  if($ordine=="quattro")
  {
    $categoria = "SELECT *
    FROM prodotto
    WHERE nome
    LIKE '%" . $_SESSION['ricerca']. "%' ORDER BY costo DESC";
    $rows = perform_query($categoria);

  }

}
else {
  $categoria = "SELECT *
  FROM prodotto
  WHERE nome
  LIKE '%" . $_SESSION['ricerca']. "%'";
  $rows = perform_query($categoria);
}


//MANCA RICERCA PER ATTORE, FILM, CD, CANTANTE ECC.


function printCard($rows)
{

  foreach ($rows as $key => $row) {

    ?>
    <!--onmouseover="animateCard()" onmouseout="NotanimateCard()"-->
    <div class="card" > <a href="visualizza_prodotto.php?id= <?= $row["id"] ?>" action="POST"  >
      <img class="card-img-top"src="<?= "img/". $row['foto'] ?>" id = "overID"  alt="...">
      <div class="card-body">
        <h5 class="card-title" id="card-title"> <?= $row["nome"] ?>  </h5>
        <p class="card-text"> Prezzo: <?= $row["costo"]."€" ?> </p>
        <p class="card-text">  Media voti: <?= getMediarecensioni($row['id'])?></p>
        <p class="card-text"> <?= $row["descrizione"] ?> </p>
        <p class="card-text"> Ultima modifica <small class="text-muted"><?= $row['timestamp']?></small></p>
      </div>
    </a>
  </div>
  <?php
  if($key % 2 == 0 && $key!=0)
  {
    return;}
  }

}

?>
<div class="main">
  <h1> Prodotto ricercato </h1>
</div>

<?php

if($rows->rowCount())
{
  ?>
  <a href="categoria.php" id="backbutton">&#8249;</a>


  <div class="sfondo">
    <form style="float:right" method="POST"  action="">
      <fieldset class="form-group">
        <div class="row">
          <legend class="col-form-label col-sm-2 pt-0">Ordina per:</legend>
          <div class="col-sm-10">
            <div class="form-check">
              <input class="form-check-input" type="radio" name="ordine" id="gridRadios1" value="uno" checked>
              <label class="form-check-label" for="gridRadios1">
                Media recensioni
              </label>
            </div>
            <div class="form-check">
              <input class="form-check-input" type="radio" name="ordine" id="gridRadios2" value="due">
              <label class="form-check-label" for="gridRadios2">
                Ultimi Arrivi
              </label>
            </div>
            <div class="form-check ">
              <input class="form-check-input" type="radio" name="ordine" id="gridRadios3" value="tre" >
              <label class="form-check-label" for="gridRadios3">
                Prezzo crescente
              </label>
            </div>

            <div class="form-check ">
              <input class="form-check-input" type="radio" name="ordine" id="gridRadios3" value="quattro">
              <label class="form-check-label" for="gridRadios3">
                Prezzo descrescente
              </label>
            </div>
          </div>


          <input class="btn btn-primary" type="submit" value="Submit">

        </div>
      </fieldset>
    </form>

    <row>

      <h3 style="text-align:center"> Risultati per: "<?=$_SESSION['ricerca']?>" </h3> <br>

      <?php
      for ($i=0; $i <$rows->rowCount() ; $i++) {
        // code...?>

        <div class="col-sm-6">

          <div class="card-deck">

            <?php printCard($rows);



            if($rows -> rowCount()%3 != 0 && $i == 1)
            {
              $index = ($rows->rowCount()%3);
              for($j = 0; $j<3-$index; $j++)
              {
                ?>

                <div class="card" style="visibility: hidden">
                </div>

                <?php
              }
            }
            ?>


          </div>
        </div>
      <?php }


      ?>
    </row>

  </div>

  <?php

}
else {
  printNotFound($ricerca);
}
?>
<?php include("Template/footer.php") ?>
