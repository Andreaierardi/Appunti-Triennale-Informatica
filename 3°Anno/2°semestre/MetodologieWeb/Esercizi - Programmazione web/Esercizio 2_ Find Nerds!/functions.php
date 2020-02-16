<!-- Andrea Ierardi 20018785 -->
<?php
/* File che include tutte le funzioni utili */

/* Funzioni di check per verificare se due persone sono compatibili */
  function checkGenre($sex, $genre)
  {
    if($genre==$sex)
      return false;
    return true;
  }
  function checkAge( $age,$min, $max)
  {
    if($age>= $min && $age <= $max)
      return true;
    return false;
  }
  function checkSO($so, $soUt)
  {
    if(!($so == $soUt))
      return false;
    return true;
  }
  function checkPersonality($personality, $personalityUt)
  {

    $str1 = str_split($personality);
    $str2 = str_split($personalityUt);
    for($i = 0 ; $i< strlen($personality); $i++)
        if($str1[$i] == $str2[$i])
          return true;

    return false;
  }

/* Funzione che cerca i dati dell'utente loggato e li ritorna in un array.
Passo il nome e le linee del file come parametri
*/
  function searchUser($nome, $lines)
  {
      foreach ($lines as $line_num => $line)
      {
        $data = explode(",", $line);
        list($name, $sex, $age, $personality, $so, $agemin, $agemax)= $data;
        if($name == $nome)
          return $data;
      }
  }

/* Funzione che ricerca i profili compatibili
Passo le linee del file e le informazioni dell'utente e li indicizzo con list
 */
  function matchesList($lines, $userInfo)
  {
    list($name, $sex, $age, $personality, $so, $agemin, $agemax)= $userInfo;
    $matches = array();  //Array che conterrà la lista dei matches

    foreach ($lines as $line_num => $line)
    {
      $data = explode(",", $line);
      list($n, $sx, $a, $p, $s, $amin, $amax)= $data;
      //Richiamo i check e se il profilo è compatibile lo aggiorno alla lista dei matches
      if (checkGenre($sex,$sx) && checkAge($a,$agemin,$agemax) &&  checkSO($so,$s) && checkPersonality($p, $personality))
          $matches[] = $line;
    }
    return $matches;
  }
//Funzione che indica all'utente che nessun match è compatibile
  function noMatch()
  {
     ?> <p> Sorry, no matches for you :( </p>
     <?php
 }

 /* Stampa la lista dei matchesList
   Passo come parametri l'array $person, che concide con una persona e i suoi dati
   e l'array $type che contiene le stringhe con i tipi di dato ("nome", "sesso " ecc.)
 */
   function stampaPersona($person , $type)
   {?>
     <p>
       <img src = "http://www.cs.washington.edu/education/courses/cse190m/12sp/homework/4/user.jpg" >
       <?= $person[0] ?>
     </p>
       <ul>
           <?php
           for($per = 1 ; $per < sizeof($person)-2; $per++)
           {
               ?>

              <li>
                <strong ><?=  $type[$per].":"?> </strong >
                <?= $person[$per] ?>
              </li>
           <?php
           }
           ?>


       </ul>
       <?php
   }
 ?>
