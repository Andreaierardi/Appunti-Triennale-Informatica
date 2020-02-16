<?php include("Template/top.php"); ?>

<form action="#" method="post">

<div class="container register-form">
            <div class="form">


                <div class="form-content">
                    <div class="row">

                        <div class="col-md-6">
                          <div class="note">
                              <p>Login </p>
                          </div>
                            <div class="form-group">
                            <p>  Email: </p>
                                <input type="email" class="form-control" placeholder="Email *" value=""/>
                            </div>
                            <div class="form-group">
                              <p> Password: </p>
                                <input type="password" class="form-control" placeholder="Password *" value=""/>
                            </div>
                            <br>
                            <button type="submit" class="btnSubmit">Login</button>
                          </div>
                          <br>

                          <div class="col-md-6">
                            <div class="note">
                                <p>Registrati </p>
                            </div>
                          <!--    <div class="form-group">
                              <p>  Email: </p>
                                  <input type="text" class="form-control" placeholder="Nome *" value=""/>
                              </div>
                              <div class="form-group">
                                <p> Password: </p>
                                  <input type="password" class="form-control" placeholder="Cognome *" value=""/>
                              </div>-->
                              <br>

                            <h2>  Se non hai un account registrati ora!</h2>
                              <br>
                              <a  href="registrazione.php" ><button type="text" class="btnSubmit">Registrati</button> </a>
                            </div>

                        </div>


                      </div>

                    </div>

                  </div>
</form>
<?php include("Template/footer.php"); ?>
