<?php
?>

<div class="title">
     Contact
</div>

<div class="text">
     For further information, feel free to send an email to any of our team members:<br /><br />
     <?php
      $result = mysql_query("SELECT * FROM `profile` ORDER BY `name` ASC");
      while($array = mysql_fetch_array($result))
      {
        echo $array['name'] . ": <a href=\"mailto:{$array['email']}\">{$array['email']}</a><br />";
      }
     ?>
</div>

