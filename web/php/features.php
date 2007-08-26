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
     $overview = array(
                new Feature("Ease of use", "Very little programming experience required. Everything is done with scripts. No compiling needed.", true),
                new Feature("Hardware acceleration", "Very fast OpenGL powerered graphics.", true),
                new Feature("Cross platform", "Available on Windows, Linux and Mac OS X", false),
                new Feature("Highly flexible", "Use the built in objects, or create your own!", true),
                new Feature("Free", "Licensed under the zlib license, which allows you to do whatever the fuck you want.", true),
                new Feature("Focus on 2D projects", "Who the fuck needs the z-axis anyway.", true)
     );

     // Array of Features
     $concrete = array(
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
     );

     // Array of Features
     $distant = array(
                new Feature("Vector graphics", "Support for reading and rendering SVG files.", true),
                new Feature("Save game state", "General game saving system that will work for any game.", true), 
                new Feature("General network support", "", true),
                new Feature("Automatic updates", "", true)
     );


?>

<div class="title">
     Information
</div>
<div class="text">
   Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Proin dui turpis, semper ut, ornare vel, placerat sed, augue. Morbi sit amet magna sit amet enim nonummy dignissim. Duis tincidunt sollicitudin purus. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Morbi sed nulla. Duis elementum ultrices odio. In sed pede. Mauris tincidunt bibendum urna. Aliquam hendrerit odio at mauris. Integer leo est, malesuada sed, scelerisque at, mattis ut, lectus.
   The overview should present the vision ... and shit.
</div>


<div class="title">
     Overview
</div>
<ul class="feature_list">

<?php


     // Output features
     
     for($i=0;$i<sizeof($overview);$i++)
     {

       ?>
         
       <li>
           
           <div class="title"><?php  echo $overview[$i]->title; ?></div>
           <div class="subtext"><?php  echo $overview[$i]->subtext; ?></div>

       </li>

       <?php

     }

?>


</ul>


<div class="text">                                                                                                                                                                                                                                                                                                                                                                                                                                                    <br /><br />
Aliquam a enim id tortor hendrerit suscipit. Vestibulum pulvinar ligula a nisi. Curabitur consectetuer, lacus sed accumsan molestie, urna lorem tempor augue, eu rhoncus velit risus eu sapien. Phasellus sit amet tortor. Nulla sapien. Curabitur felis turpis, fringilla sed, luctus sit amet, pulvinar et, velit. Nam id nibh. Phasellus non tortor. Maecenas gravida tellus quis felis. Duis ullamcorper dolor vitae tellus aliquam mattis. Praesent molestie. Nam turpis felis, vulputate vel, volutpat et, adipiscing at, eros.
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

<div class="text">                                                                                                                                                                                                                                                                                                                                                                                                                                                    <br /><br />
Aliquam a enim id tortor hendrerit suscipit. Vestibulum pulvinar ligula a nisi. Curabitur consectetuer, lacus sed accumsan molestie, urna lorem tempor augue, eu rhoncus velit risus eu sapien. Phasellus sit amet tortor. Nulla sapien. Curabitur felis turpis, fringilla sed, luctus sit amet, pulvinar et, velit. Nam id nibh. Phasellus non tortor. Maecenas gravida tellus quis felis. Duis ullamcorper dolor vitae tellus aliquam mattis. Praesent molestie. Nam turpis felis, vulputate vel, volutpat et, adipiscing at, eros.
</div>

<div class="title">
     Distant Features
</div>
<ul class="feature_list">

<?php


     // Output features

     for($i=0;$i<sizeof($distant);$i++)
     {

       ?>
         
       <li>

           <div class="title"><?php  echo $distant[$i]->title; ?></div>
           <div class="subtext"><?php  echo $distant[$i]->subtext; ?> </div>

       </li>

       <?php

     }

?>


</ul>
