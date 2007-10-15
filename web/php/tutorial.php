<?php
 include_once("geshi.php");

 if(!isset($_GET['id']) || trim($_GET['id']) == "") echo "<div class=\"center\">You need to select a tutorial.</div>";
 else
 {
   $array = mysql_fetch_array(mysql_query("SELECT * FROM `tutorial` WHERE `id` = '{$_GET['id']}'"));
   ?>
    <div class="title"><?php echo $array['title']; ?></div>
    <div class="text">
     <?php
      if(trim($array['image']) != "" && trim($array['image']) != "0")
      {
        $image = mysql_fetch_array(mysql_query("SELECT * FROM `screenshot` WHERE `id` = '{$array['image']}'"));
     ?>
      <div class="ss_box" style="float: right;">
       <div class="top"><!-- --></div>
	   <?php
	    $size = getimagesize("screenshot/" .  $image['image']); 
	   ?>
        <a class="image_info_inactive" href="javascript:void(0)" onclick="javascript:viewImage('screenshot/<?php echo $image['image']; ?>', <?php echo $size[0]; ?>, <?php echo $size[1]; ?>)" onmouseover="ssOver(this)" onmouseout="ssOut(this)">
          <div class="title"><?php echo $image['title']; ?></div>
          <div class="date"><?php echo date("Y-m-d G:i", $image['date']); ?></div>
        </a>
        <img class="kthumb" src="php/phpThumb.php?src=../screenshot/<?php echo $image['image']; ?>&amp;w=200&amp;h=150" alt="<?php echo $image['title']; ?>" />
        <div class="caption">
          <?php echo $image['text']; ?>
        </div>
       <div class="bot"><!-- --></div>
      </div>
     <?php
      }
      $text = $array['text'];
      preg_match_all("/\[code\]((.|\s)*?)\[\/code\]/", $text, $out, PREG_SET_ORDER);
      for($i = 0; $i < count($out); $i++)
      {
        $pos = strpos($text, $out[$i][0]);
        echo (substr($text, 0, $pos));
        //$text = str_replace($out[$i][0], "", $text);

        $geshi =& new GeSHI(trim($out[$i][1]), "lua");
        $geshi->set_header_type(GESHI_HEADER_NONE);
	$geshi->set_keyword_group_style(1, 'color: #1f6ed9; font-weight: bold;', true);
	$geshi->set_comments_style(1, 'color: #4db12a;', true);
	$geshi->set_brackets_style('color: #1f6ed9;');
	$geshi->set_numbers_style('color: #358917;');
	$geshi->set_strings_style('color: #a31515;');
	/**
	$geshi->add_keyword_group(10, 'color: #666; font-weight: bold;', false, array(
		'main', 'init', 'update', 'render',
		'keyboard:isDown',
		'mouse:getX','mouse:getY',
		'game:addImage'));
	$geshi->set_url_for_keyword_group(10, "?page=documentation&amp;lookup={FNAME}");
	**/

	$geshi->set_tab_width(3);
	echo "<div class=\"code\"><div class=\"content\"><code>" . $geshi->parse_code() . "</code></div></div>";

        $text = substr($text, $pos + strlen($out[$i][0]));
      }
      echo ($text);
     ?>
    </div>

    <div class="spacer"> </div>

    <div class="textmenu">
	<div class="header">
		That's great! But now I'd like to:
	</div>
	<div class="items">
		<a class="item" href="?page=documentation"> + Go back to the tutorial list</a>
		<a class="item" href="tutorial/<?php echo $array['file']; ?>"> + Download the source</a>
		<a class="item" href="javascript:void(0)" onclick="javascript:toggleVisible('reportbug')"> + Report a bug</a>
		<div id="reportbug" style="border-top:1px solid #EEEEEE;padding:5px;text-align:center;display:none;">Not ready yeat.</div>
	</div>
    </div>
   <?php
 }
?>