<?php
# The student login form submits to here.
# Upon login, remembers student login name in a PHP session variable.

include("db.php");

if (isset($_REQUEST["email"]) && isset($_REQUEST["password"])) {
  $email = $_REQUEST["email"];
  echo $email;
  $password = $_REQUEST["password"];
  echo $password;

    if (is_password_correct($email, $password)) {
    if (isset($_SESSION)) {
        if(isset($_SESSION["currentPage"]))
            $currentPage = $_SESSION["currentPage"];
        else {
            $currentPage = NULL;
            unset($currentPage);
        }

        session_destroy();
        session_regenerate_id(TRUE);
        session_start();
    }
    $_SESSION["email"] = $email;     # start session, remember user
    $info = get_infos( $email );
    if($info)
    {
      foreach ($info as $value)
        {
          echo  $value["id"];
          $_SESSION["id"]= $value["id"];
        }
    }
    $id = $_SESSION["id"];
    $carrello = getUserCart($id);
        //======DA TOGLIERE=======
    $_SESSION['carrello'] = $carrello;
    $_SESSION['numel'] = getCartEl($_SESSION['carrello']);
    $_SESSION['ordine'] = getOrderEl($_SESSION['id']);
  /*  $_SESSION["nome"] = $nome;
    $_SESSION["cognome"] = $cognome;
    $_SESSION["id"] =$id;
    $_SESSION["telefono"] =$telefono;
    $_SESSION["indirizzo_spedizione"] = $spedizione;*/

    echo "Login successful! Welcome back.";
    if(isset($currentPage))
        redirect($currentPage, "Il login ha avuto successo, Bentornato!",1);
       else
          redirect("login.php", "Il login ha avuto successo, Bentornato!",1);
    }
    else {
       redirect("login.php", "Password o email non corrette",0);
    }
}


?>
