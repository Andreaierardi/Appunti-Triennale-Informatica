<?php include_once("db.php");?>

<?php include("Template/top.php"); ?>
<?php
$query = "SELECT * FROM categoria";

$rows = perform_query($query);
?>

<?php
function printCard($rows)
{

foreach ($rows as $key => $row) {

  ?>
   <!--onmouseover="animateCard()" onmouseout="NotanimateCard()"-->
  <div class="card" > <a href="prodotti.php?id= <?= $row["id"] ?>"  action="POST">
  <img class="card-img-top"src="<?= "img/". $row['immagine'] ?>" id = "overID"  alt="...">
  <div class="card-body">
    <h5 class="card-title" id="card-title"> <?= $row["nome"] ?>  </h5>

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
<h1> Scegli la categoria di prodotto </h1>
</div>
<div class="sfondo">
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
