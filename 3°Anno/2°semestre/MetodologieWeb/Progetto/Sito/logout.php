<?php
# This page shows a login form for the student to log out of the system.
require_once("db.php");
/*if (!isset($_SESSION)) {
  session_start();
  if (isset($_SESSION["name"])) {
    unset($_SESSION["name"]);
  }
}*/
session_destroy();
session_regenerate_id(TRUE);
session_start();
redirect("login.php", "Logout successful.", 1);
?>
