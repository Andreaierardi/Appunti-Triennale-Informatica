<!-- Andrea Ierardi 20018785 -->
<?php include("top.html"); ?>


<fieldset >
    <legend>
      New User Signup:
    </legend>

    <form name="myForm" action="signup-submit.php" method="POST">
      <ul>
          <li>
             <strong > Name: </strong >
             <input type="text" name="name" size="16">
          </li>
          <li>
              <strong>  Gender:   </strong >
              Male <input type="radio" name="gender" value="M" >
              Female<input type="radio" name="gender" value="F"  checked>
          </li>
          <li>
              <strong>Age:</strong >
              <input type="text" name="age" size="6" maxlength="2" >
          </li>

          <li>
              <strong>  Personality type:</strong >
              <input type="text" name="personality" size="6" maxlength="4" >
              (<a href="http://www.humanmetrics.com/cgi-win/JTypes2.asp">Don't know your type?</a>)
          </li>
          <li>
              <strong>   Favorite OS:</strong >
              <select name="os">
               <option value="Windows">Windows</option>
               <option value="Mac OS X">Mac OS X</option>
               <option value="Linux" selected="selected">Linux</option>
              </select>
         </li>
         <li>
              <strong> Seeking age:</strong >
              <input type="text" name="min" placeholder="min" size="6" maxlength="2" >
              to
              <input type="text" name="max" placeholder="max"size="6"maxlength="2" >
        </li>
        <li>
          <input type="submit" value="Sign Up">
        </li>

      </ul>
  </form>


</fieldset>


<?php include("bottom.html"); ?>
