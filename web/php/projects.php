<?php
?>

<div class="title">
     Information
</div>

<div class="text">
   <?php
    $array = mysql_fetch_array(mysql_query("SELECT * FROM `content` WHERE `category` = 'projects'"));
    echo nl2br($array['text']);
   ?>
</div>
                            
<div class="title">
     Projects
</div>


<?php

$result = mysql_query("SELECT * FROM `project` ORDER BY `id` DESC");

while($array = mysql_fetch_array($result))
{


?>

<div class="project">

<?php
 $i_array = mysql_fetch_array(mysql_query("SELECT * FROM `screenshot` WHERE `id` = '{$array['screenshot']}'"));
?>

  <div class="ss_box">
     <div class="top"><!-- --></div>
	 <?php
	    $size = getimagesize("screenshot/" .  $i_array['image']); 
	   ?>
     <a class="image_info_inactive" href="javascript:void(0)" onclick="javascript:viewImage('screenshot/<?php echo $i_array['image']; ?>', <?php echo $size[0]; ?>, <?php echo $size[1]; ?>)" onmouseover="ssOver(this)" onmouseout="ssOut(this)">
          <div class="title"><?php echo $i_array['title']; ?></div>
          <div class="date"><?php echo date("Y-m-d G:i", $i_array['date']); ?></div>
     </a>
     <img src="php/phpThumb.php?src=../screenshot/<?php echo $i_array['image']; ?>&amp;w=200&amp;h=150" alt="<?php echo $i_array['title']; ?>" />
     <div class="caption">
          <?php echo $i_array['text']; ?>
     </div>
     <div class="bot"><!-- --></div>
</div>
  
     <div class="data">
          <div class="header"><?php echo $array['title']; ?></div>
          <div class="author"><?php echo $array['creator']; ?></div>
          <div class="date"><?php echo date("F jS, Y", $array['date']); ?></div>
          <br />
          <?php echo nl2br($array['text']); ?>

     <div class="textmenu">
	<div class="items">
		<?php if(trim($array['file']) != "") { ?> <a href="project/<?php echo $array['file']; ?>"><div class="item" style="border-color: #ddd;"> + Download</div></a> <?php } ?>
		<?php if(trim($array['link']) != "") { ?> <a href="<?php echo $array['link']; ?>"><div class="item" style="border-color: #ddd;"> + Website</div></a> <?php } ?>
	</div>
     </div>

     </div>


<div class="breaker"><!-- --></div>
</div>  <!-- Project -->
<br />

<?php } ?>