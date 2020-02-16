<?php include("Template/top.php"); ?>
<?php include_once("db.php");?>


<!-- http://bootstrapvalidator.votintsev.ru/validators/regexp/
https://www.tutorialspoint.com/javascript/javascript_regexp_object.htm
-->
<div class="sfondo">
  <div class="container register-form">
    <div class="note">
      <p>REGISTRATI su HobbyShop</p>
    </div><br>
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

    <form action="registrazione-submit.php" method="POST">
      <div class="form-row">
        <h3> Informazioni personali </h3>
      </div>

        <div class="form-row">

        <div class="form-group col-md-6">
          <label for="inputEmail4">Nome</label>
          <input type="text" name="nome" class="form-control" id="inputEmail4" placeholder="Inserisci il tuo nome" required
          pattern ="[A-Za-z]{1,32}">
        </div>
        <div class="form-group col-md-6">
          <label for="inputPassword4">Cognome</label>
          <input type="text" name="cognome" class="form-control" id="inputPassword4" placeholder="Inserisci il tuo cognome" required
          pattern ="[A-Za-z]{1,32}">
        </div>
      </div>
      <div class="form-row">
        <div class="form-group col-md-6">
          <label for="inputEmail4">Email</label>
          <input type="email" name="email" class="form-control" id="inputEmail4" placeholder="Inserisci la tua e-mail" required>
        </div>
        <div class="form-group col-md-6">
          <label for="inputPassword4">Password (almeno 8 caratteri)</label>
          <input type="password" name="password" class="form-control" id="inputPassword4" placeholder="Inserisci una password" pattern="(?=^.{8,}$)(?!.*\s).*$" required>
        </div>


      </div>

      <div class="form-row">
        <div class="form-group col-md-6">
          <label for="inputPassword4">Data di nascita (giorno/mese/anno)</label>
          <input type="data" name="data_nascita" class="form-control" id="inputPassword4" placeholder="Data di nascita" pattern="(0?[1-9]|[12][0-9]|3[01])/(0?[1-9]|1[012])/\d{4}"required>
        </div>
        <div class="form-group col-md-6">
          <label for="inputPassword4">Numero di telefono</label>
          <input type="telefono" name="telefono" class="form-control" id="inputPassword4" placeholder="Inserisci il tuo numero di telefono" pattern="[0-9]{10}" required>
        </div>
      </div><br>


      <div class="form-row">
        <h3> Informazioni indirizzo </h3>
      </div>
      <div class="form-row">
        <div class="form-group col-md-4">

          <label for="inputAddress">Via di residenza</label>
          <input type="text" name="via" class="form-control" id="inputAddress" placeholder="Via" required
          pattern ="[A-Za-z'\.\-\s\,]"
          >
        </div>
        <div class="form-group col-md-2">

          <label for="inputCity">Numero Civico</label>
          <input type="text" name="civico" class="form-control" id="inputCity" required placeholder="n." pattern="[0-9]{1,5}">
        </div>

      </div>
        <div class="form-row">

          <div class="form-group col-md-4">
            <label for="inputCity">Città</label>
            <input type="text" name="citta" class="form-control" id="inputCity" placeholder="Inserisci la città"required pattern="[A-Za-z]{1,32}">
          </div>
          <div class="form-group col-md-2">
            <label for="inputCity">Provincia (Sigla)</label>
            <input type="text" name="provincia" class="form-control" id="inputCity" placeholder="Inserisci la provincia" pattern="[A-Z]{2}"required>
          </div>
          <div class="form-group col-md-2">
            <label for="inputZip">CAP</label>
            <input type="text" name="cap" placeholder="Inserisci CAP" class="form-control" id="inputZip" pattern="[0-9]{5}" required>
          </div>
          <div class="form-group col-md-4">
            <label for="inputZip">Stato</label>
            <input type="text" name="stato" class="form-control" id="inputZip" placeholder="Inserisci lo stato" required pattern="[A-Za-z]{1,32}">
          </div>

        </div><br>


        <div class="form-row">
          <h3> Informazioni carta di credito </h3>
        </div>


        <div class="form-row">


          <div class="form-group col-md-6">
            <label for="inputPassword4">Nome intestatario</label>
            <input type="text" name="nome_carta" class="form-control" id="inputPassword4"  pattern="[A-Za-z]{1,32}"placeholder="Nome"required>
          </div>
          <div class="form-group col-md-6">
            <label for="inputPassword4">Cognome intestatario</label>
            <input type="text" name="cognome_carta" class="form-control" id="inputPassword4" pattern="[A-Za-z]{1,32}" placeholder="Cognome"required>
          </div>
          <div class="form-group col-md-6">
            <label for="inputPassword4">Numero della carta</label>
            <input type="text" name="carta" class="form-control" id="inputPassword4" placeholder="Numero" pattern="[0-9]{16}"required>
          </div>
          <div class="form-group col-md-2">
            <label for="inputPassword4">Codice della carta</label>
            <input type="text" name="codice_carta" class="form-control" id="inputPassword4" pattern="[1-9]{3}" placeholder="Codice"required>
          </div>
          <div class="form-group col-md-2">
            <label for="inputPassword4">Scadenza della carta</label>
            <input type="data" name="scadenza_carta" class="form-control" id="inputPassword4" pattern="(0?[1-9]|[12][0-9]|3[01])/(0?[1-9]|1[012])/\d{4}" placeholder="Data di scadenza"required>
          </div>
        </div>


        <button type="submit" class="btn btn-primary">Registrati </button>
      </div>

    </form>
  </div>

<?php include("Template/footer.php"); ?>
