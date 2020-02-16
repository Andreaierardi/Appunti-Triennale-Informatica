<?php include_once("db.php");?>

<script>
$(document).ready(function(){
    $('[data-toggle="popover"]').popover();
});

function hidePop(){
  document.getElementById("")
}
</script>
<nav class="navbar navbar-expand-lg navbar-dark bg-primary">
  <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarColor02" aria-controls="navbarColor02" aria-expanded="false" aria-label="Toggle navigation">
    <span class="navbar-toggler-icon" onclick="hidePop()"></span>
  </button>

  <div class="collapse navbar-collapse" id="navbarColor02">
    <ul class="navbar-nav mr-auto">
      <?php  $page = basename($_SERVER['PHP_SELF']);?>
      <li class="<?php echo ($page == "index.php" ? "active" : "")?>">
        <a class="nav-link" href="index.php"> <span class="fa fa-home"> </span> Home </a>
      </li>
      <li class="<?php echo ($page == "prodotti.php" ? "active" : "")?>">
        <a class="nav-link" href="categoria.php"><span class= "fa fa-rocket" ></span>Prodotti</a>
      </li>
      <li class="<?php echo ($page == "contatti.php" ? "active" : "")?>">
        <a class="nav-link" href="contatti.php"><span class= "fa fa-address-book-o" ></span> Contatti</a>
      </li>



    </ul>

    <ul class="navbar-nav mr-right">
      <?php if (isset($_SESSION["email"]))
      {
        ?>
        <li class="<?php echo ($page == "login.php" ? "active" : "") ?>" style="float: right">     <a class="nav-link" href="login.php"> <span class="fa fa-user"></span> Profilo </a> </li>
        <?php
      }
      else{
        ?>

        <li class="<?php echo ($page == "registrazione.php" ? "active" : "")?>" style="float: right">     <a class="nav-link" href="registrazione.php"> <span class= "fa fa-pencil-square-o"> </span>Registati </a> </li>
        <li class="<?php echo ($page == "login.php" ? "active" : "")?>">  <a class="nav-link" href="login.php"> <span class="fa fa-user"> </span> Accedi </a> </li>
      <?php } ?>
    </ul>
    <form class="form-inline" action="ricerca_prodotto.php" method="POST">
      <input class="form-control mr-sm-2" type="search" name="cerca" placeholder="Search" aria-label="Search">
      <button class="btn btn-outline-light my-2 my-sm-0" type="submit"><i class="fa fa-search" aria-hidden="true"></i></button>

    </form>

    <ul class="navbar-nav mr-right" id="OK">
      <li class="<?php echo ($page == "carrello.php" ? "active" : "")?>" style="float: right">
        <a  class="nav-link" href="carrello.php" title="Carrello" >
      <!--  <a  class="nav-link" href="#" title="Carrello" data-toggle="popover" data-toggle="popover" data-placement="bottom"> -->
        <span class="fa fa-shopping-cart">
      </span>
      Carrello

      <?php if(isset($_SESSION['numel']))
      {
        ?>
        <span id="count_cart"><?php $num = getCartEl($_SESSION['carrello']); echo $num; ?></span>
          <?php
      }
      else {
      ?>
      <span id="count_cart">0<span>

    <?php }
      ?>
      </a> </li>
    </ul>

  </div>

</nav>
