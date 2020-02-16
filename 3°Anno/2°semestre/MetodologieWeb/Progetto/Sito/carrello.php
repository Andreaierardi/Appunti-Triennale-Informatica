<?php include("db.php"); ?>
<?php include("Template/top.php"); ?>

<?php
ensure_logged_in("carrello.php", "Effettua il login per accedere");
$delete = null;
$alterqta= null;
if(isset($_GET['del_all']))
{
  $carrello = $_SESSION['carrello'];
  $query ="DELETE FROM cont_carrello WHERE carrello=$carrello";
  perform_query($query);
}
if (isset($_GET['load']) && isset($_GET['id']) ) {

  $alter = $_GET['load'];
  $id_p = $_GET['id'];
  $query= "UPDATE cont_carrello SET quantita='$alter' WHERE prodotto=$id_p";
  $rows = perform_query($query);
}

if (isset($_GET['del_id'])) {
  $delete = $_GET['del_id'];
  $query= "DELETE FROM cont_carrello WHERE prodotto=$delete";
  $_SESSION['numel'] =getCartEl($_SESSION['carrello']);
  $rows = perform_query($query);
  redirect("carrello.php",NULL,NULL);
}



function printCart()
{

  $carrello = $_SESSION['carrello'];
  $query = "SELECT * FROM cont_carrello
  JOIN prodotto ON prodotto.id = cont_carrello.prodotto
  WHERE carrello = $carrello";
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
        $prodotto = $value['prodotto'];
        $maxquery = "SELECT giacenza FROM prodotto WHERE id=$prodotto";
        $rowm = perform_query($maxquery);
        foreach ($rowm as $key => $valuem) {
          $max = $valuem['giacenza'];
        }
        $_SESSION['max']= $max;

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
                <form method="POST"  action="ordini-submit.php">
                  <input name="prodotto" style="display:none"  value="<?= $value['prodotto']?>" >
                <button type="submit" class="btn btn-success">Compra!</button>
                <br>
                <button type="button" class="btn btn-outline-secondary" onclick="deleteme( <?php  $delete= $value['prodotto']; echo $value['prodotto']; ?> )" >Rimuovi dal carrello</button>
                <br>
                <label class="my-1 mr-2" for="inlineFormCustomSelectPref">Quantità selezionata:</label>
                <select name="quantita" onchange="uploadQTA('<?php echo $value['prodotto'];?>','<?= $max ?>')"  class="custom-select my-1 mr-sm-2" id="elementId<?php echo $value['prodotto']; ?>">

                  <?php


                  for($i = 1; $i<11; $i++)
                  {
                    if($i == $value['quantita'])
                    {

                      ?>    <option value="<?= $value['quantita']?>" selected>  <?= $value['quantita'] ?> </option>
                      <?php
                    }
                    else {
                      ?>
                      <option  value="<?= $i ?>"><?= $i ?></option>

                    <?php   } }

                    ?>
                  </select>
                </form>
                </div>
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
  <script language="javascript">
  function deleteme(delid)
  {
    /*var y = document.getElementById("count_cart");
    var inner = y.innerHTML;
    y.innerHTML = (inner*1)-1; */
    window.location.href='carrello.php?del_id='+delid+'';
    return true;
  }

  function uploadQTA(id,max)
  {
    var e = document.getElementById("elementId"+id);
    var value = e.options[e.selectedIndex].value;
    console.log("v: "+value);
    if(value>max)
     {
       e.options[e.selectedIndex].value = max;
       value=max;
     }

    var alter = e.options[e.selectedIndex].text;

    console.log("max:" +max);
    if(alter> max)
      {
        e.options[e.selectedIndex].text = max;
        alter = max;
      }
   window.location.href='carrello.php?load='+alter+''+'&id='+id;
    return true;
  }
  function delete_all()
  {
    window.location.href='carrello.php?del_all';
    return true;
  }


  </script>
<!-- Modal -->
<div class="modal fade" id="exampleModalCenter" tabindex="-1" role="dialog" aria-labelledby="exampleModalCenterTitle" aria-hidden="true">
  <div class="modal-dialog modal-dialog-centered" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="exampleModalCenterTitle">Sei sicuro di voler eliminare tutti i prodotti nel tuo carrello?</h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        Clicca su annulla per non rimuovere nessun prodotto dal tuo carrello, oppure clicca su Conferma per eliminarli tutti.
      </div>
      <div class="modal-footer">
        <button type="button" class="btn btn-secondary" data-dismiss="modal">Annulla</button>
        <button type="button" class="btn btn-primary" onclick="delete_all()">Conferma</button>
      </div>
    </div>
  </div>
</div>

<div class="modal fade" id="exampleModalCenter2" tabindex="-1" role="dialog" aria-labelledby="exampleModalCenterTitle" aria-hidden="true">
  <div class="modal-dialog modal-dialog-centered" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <h5 class="modal-title" id="exampleModalCenterTitle2">Sei sicuro di voler acquistare tutti i prodotti?</h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body">
        Clicca su Conferma per acquistare tutti i prodotti nel tuo carrello.
      </div>
      <div class="modal-footer">
        <form method="POST"  action="ordini-submit.php?all">
        <button type="button" class="btn btn-secondary" name="all" data-dismiss="modal">Annulla</button>
        <button type="submit" class="btn btn-primary">Conferma</button>
      </form>
      </div>
    </div>
  </div>
</div>

  <div class= "carrello">
    <div class="carrello_header">
      <h1>Carrello</h1>
    </div>
    <div class="carrello_list">

      <ul>


        <?php $n_product = printCart(); ?>
      </ul>

      <?php
      if($n_product>0)
      {
        ?>
        <div class="outcarrello" id="resume">
          <p> Totale: <?= $totale?>€ </p>
          <p> di cui di spedizione: <?= $totale_sped ?>€</p>
          <button type="button" class="btn btn-primary"  data-toggle="modal"  data-target="#exampleModalCenter2"> Acquista tutto </button>
          <button type="button" class="btn btn-outline-danger"  data-toggle="modal"  data-target="#exampleModalCenter">Rimuovi tutti gli elementi nel carrello</button>
          <br><br>
        </div>
      </div>
      <?php
    }
    ?>
</div>
  <?php include("Template/footer.php"); ?>
