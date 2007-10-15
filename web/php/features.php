<?php

     // Definition of Feature class.
     class Feature
     {
             var $title;
             var $subtext;
             var $bold;


             function Feature($title, $subtext, $implemented)
             {
               $this->title = $title;
               $this->subtext = $subtext;
               $this->implemented = $implemented;
             }
     }

     // Array of Features
     $result = mysql_query("SELECT * FROM `feature` ORDER BY `position` ASC");
     $i = 0;
     while($array = mysql_fetch_array($result))
     {
       $concrete[$i] = new Feature($array['title'], $array['text'], true);
       $i++;
     }
     /*$concrete = array(
                new Feature("Graphics", "All the common image formats are supported. JPG, PNG, GIF, BMP, TGA to name a few.", true),
                new Feature("Sound", "", true),
                new Feature("Scriptable interface", "Using Lua blah blbh ", true),
                new Feature("Keyboard and mouse input", "", true),
                new Feature("Resources", "", true),
                new Feature("Loader", "", true),
                new Feature("Font", "", true),
                new Feature("Animated objects", "", true),
                new Feature("Collision detection", "", true),
                new Feature("Physics", "", true),
                new Feature("Tilemaps", "", true), 
                new Feature("GUI", "Built in, highly customizable user interface system.", true), 
                new Feature("Particle system", "For fancy effects and shit.", true)
     );*/


?>

<div class="title">
     Overview
</div>
<div class="text">
   <?php
    $array = mysql_fetch_array(mysql_query("SELECT * FROM `content` WHERE `category` = 'features_information'"));
    echo nl2br($array['text']);
   ?>
</div>

<div class="title">
     Features
</div>
<ul class="feature_list">

<?php


     // Output features
     
     for($i=0;$i<sizeof($concrete);$i++)
     {

       ?>
         
       <li>
           
           <div class="title"><?php  echo $concrete[$i]->title; ?></div>
           <div class="subtext"><?php  echo $concrete[$i]->subtext; ?> </div>

       </li>

       <?php

     }

?>


</ul>

<div class="text">
   <?php
    $array = mysql_fetch_array(mysql_query("SELECT * FROM `content` WHERE `category` = 'features_concrete'"));
    echo nl2br($array['text']);
   ?>
</div>
