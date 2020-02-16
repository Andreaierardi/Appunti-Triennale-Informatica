<?php include("Template/top.php"); ?>
<?php include_once("db.php");?>

<?php
$categoria = $_GET['id'];
$_SESSION['categoria'] = $categoria;
$query = "SELECT * FROM prodotto WHERE categoria = $categoria";

$rows = perform_query($query);



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

    $q = "SELECT prodotto.id,nome,categoria,foto,prodotto.descrizione,costo,costo_spedizione,giacenza,prodotto.timestamp, recensione.prodotto, AVG(valore) as media
    FROM prodotto
    JOIN recensione ON prodotto.id = recensione.prodotto
    WHERE prodotto.categoria=$categoria
    GROUP BY prodotto.id
    ORDER BY media DESC";
    $rows = perform_query($q);

  }
  if($ordine =="due")
  {

    $q = "SELECT *
    FROM prodotto
    WHERE categoria=$categoria
    ORDER BY timestamp DESC";
    $rows = perform_query($q);
  }
  if($ordine=="tre")
  {
    $q = "SELECT *
    FROM prodotto
    WHERE categoria=$categoria
    ORDER BY costo ASC";
    $rows = perform_query(  $q);

  }
  if($ordine=="quattro")
  {
    $q = "SELECT *
    FROM prodotto
    WHERE categoria=$categoria
    ORDER BY costo DESC";
    $rows = perform_query(  $q);

  }
}
  //echo $rows->rowCount();

  /* https://pods.io/docs/code/pods/field/
  <?php
  // We have a "books" Pod with "category" and "the_author"
  // as single-select relationship fields, related to
  // "categories" and "authors" Pods
  $params = array(
  'where'   => 't.name LIKE "%rings%"',
  'limit'   => -1  // Return all rows
);

// Create and find in one shot
$books = pods( 'books', $params );

if ( 0 < $books->total() ) {
while ( $books->fetch() ) {
?>
<h2><?php echo $books->field( 'name' ); ?></h2>
<p>Author: <?php echo $books->field( 'the_author.name' ); ?></p>
<br />
<p>Category: <?php echo $books->field( 'category.name' ); ?></p>
<br />
<?php
} // end of books loop
} // end of found books */
?>
<script>
/*
function changeClass(btn, cls)
{
if(!hasClass(btn, cls)) {
addClass(btn, cls);
}
}

function animateCard()
{
let x = document.getElementById("overID");

//  x.className= ".sfondo > row > .col-sm-6 > .card-deck> .card a img:hover";
console.log(x.className);
x.style.cssText = "transform: scale(1.1); -webkit-transition: all 1s ease;      -moz-transition: all 1s ease; -o-transition: all 1s ease;-ms-transition: all 1s ease;transition: all 1s ease;  opacity: 1;";
//  console.log("STYLE");
}

function NotanimateCard()
{
let x = document.getElementById("overID");
let str = "padding: 1rem 1rem 1rem 1rem; margin-left: 5%;  width: 90%;  height: 90%; transition: transform .2s; opacity: 0.6;";
x.style.cssText = str;
}

*/
</script>
<?php
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
        <p class="card-text">  Media recensioni: <?= getMediarecensioni($row['id'])?></p>
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
<!-- .sfondo > row > .filter -->
<div class="main">
  <h1> Catalogo prodotti </h1>
</div>


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



    <?php for ($i=0; $i < 3; $i++) {
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
<?php include("Template/footer.php"); ?>
