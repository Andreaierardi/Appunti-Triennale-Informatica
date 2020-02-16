
<?php include_once("Template/top.php"); ?>
<div class="bd-example">
<div id="carousel" class="carousel slide carousel-fade" data-ride="carousel">
  <ol class="carousel-indicators">
    <li data-target="#carouselExampleIndicators" data-slide-to="0" class="active"></li>
    <li data-target="#carouselExampleIndicators" data-slide-to="1"></li>
    <li data-target="#carouselExampleIndicators" data-slide-to="2"></li>
  </ol>
  <div class="carousel-inner">
    <div class="carousel-item active">
      <a class="nav-link" href="prodotti.php?id=2"><img src="img/vinile.jpg" id="it" alt="..."></a>
    </div>
    <div class="carousel-item">
      <a class="nav-link" href="prodotti.php?id=3"><img src="img/videogiochi.jpg" id ="it"  alt="..."></a>
    </div>
    <div class="carousel-item">
        <a class="nav-link" href="prodotti.php?id=4"><img src="img/fumetti.jpg" id="it" alt="..."></a>
    </div>
  </div>
  <a class="carousel-control-prev" href="#carousel" role="button" data-slide="prev">
    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
    <span class="sr-only">Previous</span>
  </a>
  <a class="carousel-control-next" href="#carousel" role="button" data-slide="next">
    <span class="carousel-control-next-icon" aria-hidden="true"></span>
    <span class="sr-only">Next</span>
  </a>
</div>
</div>

<!--
<div id="myCarousel" class="carousel slide" data-ride="carousel">
     Indicators
    <ol class="carousel-indicators">
      <li data-target="#myCarousel" data-slide-to="0" class="active"></li>
      <li data-target="#myCarousel" data-slide-to="1"></li>
			<li data-target="#myCarousel" data-slide-to="2"></li>

    </ol>

   Wrapper for slides
    <div class="carousel-inner" role="listbox">
      <div class="item active">
        <img src="img/vinile.jpg" alt="Image">
        <div class="carousel-caption">
          <h3>Vinili</h3>
          <p>Money Money.</p>
        </div>
      </div>

      <div class="item">
        <img src="img/videogiochi.jpg" alt="Image">
        <div class="carousel-caption">
          <h3>Videogiochi</h3>
          <p>Lorem ipsum...</p>
        </div>
      </div>

			<div class="item">
        <img src="img/fumetti.jpg" alt="Image">
        <div class="carousel-caption">
          <h3>Fumetti</h3>
          <p>Lorem ipsum...</p>
        </div>
      </div>
    </div>

   Left and right controls
    <a class="left carousel-control" href="#myCarousel" role="button" data-slide="prev">
      <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
      <span class="sr-only">Previous</span>
    </a>

    <a class="right carousel-control" href="#myCarousel" role="button" data-slide="next">
      <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
      <span class="sr-only">Next</span>
    </a>
</div>
-->

<div class="album py-5 bg-light">
  <div class="main">
<h1> Ultimi arrivi <h1>
</div>
<?php
$query = "SELECT * from prodotto ORDER BY timestamp DESC LIMIT 6";
$rows = perform_query($query);

?>

<?php
for($i = 0 ; $i<2; $i++)
{
  ?>
<div class="container">
  <div class="row">
<?php
foreach ($rows as $key => $value) {

 ?>

    <div class="col-sm-4">
      <div class="panel panel-primary">
        <div class="panel-heading"><h5><?= $value['nome']?></h5></div>
          <a class="nav-link" href="visualizza_prodotto.php?id=<?=$value['id']?>"><div class="panel-body"><img src="img/<?= $value['foto'];?>" class="img-responsive" style="width:60%" alt="Image"></div></a>
        <div class="panel-footer">A soli <?= $value['costo']?> euro!</div>
      </div>
    </div>

  <?php
  }
  ?>

</div>


</div>

<?php
}
?> </div><br>
	<?php include("Template/footer.php"); ?>
