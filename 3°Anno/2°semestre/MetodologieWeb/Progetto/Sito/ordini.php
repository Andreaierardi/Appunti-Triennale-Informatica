<?php include("db.php"); ?>
<?php include("Template/top.php"); ?>
<?php
ensure_logged_in("login.php", "Effettua il login per accedere");


function printCart()
{

  $ordine = $_SESSION['ordine'];
  $query = "SELECT * FROM cont_ordine
  JOIN prodotto ON prodotto = prodotto.id
    WHERE ordine = $ordine ORDER BY cont_ordine.timestamp DESC";
  $rows = perform_query($query);
  $totale = 0;
  $totale_sped=0;
  global $totale;
  global $totale_sped;
  if($rows)
  {

    if($rows -> rowCount())
    {
      foreach ($rows as $key => $value) {

        $p = $value['costo'];
        $q = $value['quantita'];
        $s = $value['costo_spedizione'];
        $totale += $p* $q + $s;
        $totale_sped += $s;
        ?>
        <li>
          <div class="media" href="visualizza_prodotto.php">
            <div class="row">
              <div class="column" >
                <a href="visualizza_prodotto.php?id=<?= $value['prodotto'] ?>">
                  <img src=" img/<?= $value['foto'] ?>" class="mr-3" alt="...">
                  <div class="media-body">
                    <h5 class="mt-0"> <?= $value['nome'] ?> </h5>

                    <p> Prezzo:  <p2 id="highlight"><?= $value['costo'] ?>€  </p2> </p>
                    <p>  Prezzo di spedizione:   <p2 id="highlight"> <?= $value['costo_spedizione'] ?>€ </p2></p>
                  </div>
                </a>
              </div>
              <div class="column">
                <button type="button" class="btn btn-success">Compra di nuovo!</button>
                <br>
                <p> Numero di istanze del prodotto acquistate: <strong> <?= $value['quantita']?></strong></p> <br>
                 <h5> Totale ordine: <?= $value['costo']*$value['quantita'] + $value['costo_spedizione']."€"; ?></h5>
              </div>
            </div>

          </li>

          <?php
        }

      }
      else {
        echo "Nessun prodotto presente nel carrello";
      }
      return $rows->rowCount();
    }
    else {
      echo "Nessun prodotto presente nel carrello";
    }
  }
  ?>

  <div class= "carrello">
    <div class="carrello_header">
      <h1>STORICO ORDINI</h1>
    </div>
    <?php if(isset($_SESSION['flash']))
    {
      if($_SESSION['flag']==1)
      {
        ?>
        <div class="alert alert-success" role="alert">

        <?php
      }
      if($_SESSION['flag']==0){
        ?>

        <div class="alert alert-danger" role="alert">
        <?php
      }
      ?>
        <?= $_SESSION['flash']; $_SESSION['flag']=null;$_SESSION['flash']=null?>
      </div>

    <?php
  }
  ?>

    <div class="carrello_list">

      <ul>


        <?php $n_product = printCart(); ?>
      </ul>


    </div>
  <?php include("Template/footer.php"); ?>
