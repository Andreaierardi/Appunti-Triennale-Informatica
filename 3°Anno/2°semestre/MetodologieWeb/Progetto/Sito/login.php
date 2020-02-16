<?php include("db.php") ?>


<?php include("Template/top.php"); ?>

<?php

function printInfo($rows)
{
      foreach ($rows as $key => $value) {
   ?>

   <div class="card-group">

   <div class="card" style="width: 18rem;">
   <div class="card-header">
     <h2> Dati dell'account </h2>
   </div>
   <ul class="list-group list-group-flush">
   <li class="list-group-item"><strong> Email: </strong><?= $value['email']?></li>
   <li class="list-group-item"><strong> Password: </strong><?= $value['password']?></li>
   <li class="list-group-item"><strong> Nome: </strong><?= $value['nome']?></li>
   <li class="list-group-item"><strong> Cognome: </strong><?= $value['cognome']?></li>
   <li class="list-group-item"><strong> Data di nascita: </strong><?= $value['data_nascita']?></li>
   <li class="list-group-item"><strong> Telefono: </strong><?= $value['telefono']?></li>

 </ul>
</div>

 <div class="card" style="width: 18rem;">
 <div class="card-header">
   <h2> Dati sull'indirizzo </h2>
 </div>
 <ul class="list-group list-group-flush">
   <li class="list-group-item"><strong>  Via: </strong><?= $value['via']?></li>
   <li class="list-group-item"><strong> N. civico: </strong><?= $value['civico']?></li>
   <li class="list-group-item"><strong> Città: </strong><?= $value['citta']?></li>
   <li class="list-group-item"><strong> Provincia: </strong><?= $value['provincia']?></li>
   <li class="list-group-item"><strong> CAP: </strong><?= $value['cap']?></li>
   <li class="list-group-item"><strong> Stato: </strong><?= $value['stato']?></li>
 </ul>
 </div>

 <div class="card" style="width: 18rem;">
 <div class="card-header">
   <h2> Dati sulla carta  </h2>
 </div>
 <ul class="list-group list-group-flush" style="text-align: center">

 <li class="list-group-item"><strong> Intestatario delle carta:  </strong> <?= $value['nome_intestatario']." ". $value['cognome_intestatario']?></li>
 <li class="list-group-item"><strong> Numero della carta:  </strong><?= $value['numero']?></li>
 <li class="list-group-item"><strong> Codice a tre cifre della carta:  </strong><?= $value['codice']?></li>
 <li class="list-group-item"><strong> Scandenza:</strong> <?= $value['scadenza']?></li>
</ul>
 </div>

</div>

   <?php
      }

}
 ?>
<div class="sfondo">

  <?php if (isset($_SESSION["email"])) { ?>

    <div class="main">
    <h1> Profilo Utente </h1>
    </div>
    <form id="logout" action="logout.php" method="post">
      <input class="btn btn-primary" type="submit" value="Log Out">

      <input type="hidden" name="logout" value="true" />

    </form>

    <br>



    <?php
    $query = "SELECT email, password, nome,cognome, cognome,data_nascita, telefono, via, civico, citta,
    provincia, stato, cap, nome_intestatario, cognome_intestatario, numero, codice, scadenza
    FROM utente JOIN carta ON utente.carta=carta.id JOIN indirizzo ON indirizzo.id=utente.indirizzo
    WHERE utente.id=".$_SESSION["id"];

    $rows = perform_query($query);
printInfo($rows);

?>
<a class="nav-link" href="ordini.php"><span class= "fa fa-rocket" ></span>Storico ordini</a>


    <?php if(isset($_SESSION['flash']))
    {
      ?>
      <div class="alert alert-success" role="alert">
        <?= $_SESSION['flash']; $_SESSION['flash']=null?>
      </div>

    <?php
  }


        $item = getCartEl($_SESSION['carrello']);
        $_SESSION['numel']=$item;

  }

    else { ?>
  <div class="container register-form">
    <div class="note">
        <p>ACCEDI a HobbyShop</p>
    </div>
  <form action="login-submit.php" method="post">
    <div class="form-group">
      <label >Email address</label>
      <input type="email" name="email"  class="form-control" id="email" aria-describedby="emailHelp" placeholder="Enter email" required>
      <small id="emailHelp" class="form-text text-muted">We'll never share your email with anyone else.</small>
    </div>
    <div class="form-group">
      <label for="exampleInputPassword1">Password</label>
      <input type="password" name="password" class="form-control" id="password" placeholder="Password" required>
    </div>

    <button type="submit" class="btn btn-primary" >Invia</button>
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
  </form>
</div> <?php } ?>

</div>

<?php include("Template/footer.php"); ?>
