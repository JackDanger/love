<div class="title">FAQ</div>

<?php
 $result = mysql_query("SELECT * FROM `faq` ORDER BY `position` ASC");
 while($array = mysql_fetch_array($result))
 {
   ?>
    <div class="text">
     <strong><?php echo $array['question']; ?></strong><br />
     <?php echo nl2br($array['answer']); ?>
    </div>
   <?php
 }
?>