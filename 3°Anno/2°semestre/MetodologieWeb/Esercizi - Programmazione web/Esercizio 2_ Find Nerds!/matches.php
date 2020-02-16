<!-- Andrea Ierardi 20018785 -->
<?php include("top.html"); ?>

<!-- Pagina per la ricerca dei matches -->
  <fieldset >
    <legend>
      Returning User:
    </legend>
      <form name="myForm" action="matches-submit.php" method="GET">
        <ul>
        <li>
          <strong> Name: </strong>
          <input type="text" name="name">
        </li>
        <li>
        <input type="submit" value="View My Matches">
        </li>
      </ul>
      </form>
  </fieldset>


<?php include("bottom.html"); ?>
