<?php
?>

<div class="title">
     Documentation
</div>
<div class="text" style="margin-bottom: 10px;">
	<?php
		$array = mysql_fetch_array(mysql_query("SELECT * FROM `content` WHERE `category` = 'documentation'"));
		echo nl2br($array['text']);
	?>
</div>
<?php /*
<div class="textmenu">
	<div class="header">
		Documents
	</div>
	<div class="items">
		<a href="./docs"><div class="item"> + Online Reference Manual</div></a>
		<a href="#"><div class="item"> + Download Documentation</div></a>
	</div>		
</div>
*/ ?>
<div class="text">

</div>
                            
<div class="title">
     Tutorials
</div>

<?php

$result = mysql_query("SELECT * FROM `tutorial` ORDER BY `position` ASC");
while($array = mysql_fetch_array($result))
{
?>

<div class="project">
  
  <?php

   if(trim($array['image']) != "" && trim($array['image']) != "0")
   {
     $image = mysql_fetch_array(mysql_query("SELECT * FROM `screenshot` WHERE `id` = '{$array['image']}'"));
  ?>

   <div class="ss_box">
     <div class="top"><!-- --></div>
     <a class="image_info_inactive" href="?page=tutorial&amp;id=<?php echo $array['id']; ?>" onmouseover="ssOver(this)" onmouseout="ssOut(this)">
          <div class="title"><?php echo $image['title']; ?></div>
          <div class="date"><?php echo date("Y-m-d G:i", $image['date']); ?></div>
     </a>
     <img src="php/phpThumb.php?src=../screenshot/<?php echo $image['image']; ?>&amp;w=200&amp;h=150" alt="<?php echo $image['title']; ?>" />
     <div class="caption">
          <?php echo $image['text']; ?>
     </div>
     <div class="bot"><!-- --></div>
   </div>
  
  <?php
   }
  ?>
  
     <div class="data">
          <div class="header"><?php echo $array['title']; ?></div>
          <div class="author"><?php echo nl2br($array['description']); ?></div>
          <div class="date"><?php echo date("F jS, Y", $array['date']); ?></div>

     <div class="textmenu">
	<div class="items">
		<a href="?page=tutorial&amp;id=<?php echo $array['id']; ?>"><div class="item" style="border-color: #ddd;"> + Go To Tutorial</div></a>
		<a href="tutorial/<?php echo $array['file']; ?>"><div class="item" style="border-color: #ddd;"> + Download source</div></a>
	</div>
     </div>

     </div>


<div class="breaker"><!-- --></div>
</div>  <!-- Project -->

<?php } ?>
