<?php
?>

<div class="title">
     Screenshots
</div>


<?php

$count = 0;
$result = mysql_query("SELECT * FROM `screenshot` WHERE `show` = '1' ORDER BY `id` DESC");
while($array = mysql_fetch_array($result))
{
?>

<div class="ss_box">
     <div class="top"><!-- --></div>
	 <?php
	  $size = getimagesize("screenshot/" .  $array['image']); 
	 ?>
     <a class="image_info_inactive" href="javascript:void(0)" onclick="javascript:viewImage('screenshot/<?php echo $array['image']; ?>', <?php echo $size[0]; ?>, <?php echo $size[1]; ?>)" onmouseover="ssOver(this)" onmouseout="ssOut(this)">
          <div class="title"><?php echo $array['title']; ?></div>
          <div class="date"><?php echo date("Y-m-d G:i", $array['date']); ?></div>
     </a>
     <img src="php/phpThumb.php?src=../screenshot/<?php echo $array['image']; ?>&amp;w=200&amp;h=150&amp;q=100" alt="<?php echo $array['title']; ?>" />
     <div class="caption">
          <?php echo $array['text']; ?>
     </div>
     <div class="bot"><!-- --></div>
</div>

<?php
	$count = $count + 1;
	if($count == 2)
	{
		?> <div class="spacer"> </div> <?php
		$count = 0;
	}
}
?>