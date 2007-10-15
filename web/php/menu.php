<?php

     // Definition of MenuItem class.
     class MenuItem
     {
             var $file;
             var $displayName;
             var $css;

             function MenuItem($file, $displayName, $css)
             {
               $this->file = $file;
               $this->displayName = $displayName;
               $this->css = $css;
             }
     }

     // Array of MenuItems
     $mi = array(
                new MenuItem("home", "Home", "home"),
                new MenuItem("features", "Features", "purple"),
                new MenuItem("screenshots", "Screenshots", "green"),
                new MenuItem("documentation", "Documentation", "blue"),
                new MenuItem("projects", "Projects", "red"),
                new MenuItem("faq", "FAQ", "apple"),
                new MenuItem("contact", "Contact", "ocean"),
     );
     
     //removed
     //new MenuItem("page_tool_demo", "Page Tool Demo", "#ffffff", "#4e85e0"),
     //new MenuItem("tut_demo", "Tutorial demo", "#ffffff", "#4e85e0")
     
     // Output menu

     for($i=0;$i<sizeof($mi);$i++)
     {

       ?>

       <a href="?page=<?php echo $mi[$i]->file; ?>"
          class="<?php echo $mi[$i]->css; ?>">
          <?php echo $mi[$i]->displayName; ?>
       </a>

       <!--<a href="?page=<?php echo $mi[$i]->file; ?>">
          <div class="menu_item_medium" style="background-color: <?php echo $mi[$i]->bgColor; ?>" onmouseover="overMenu(this, '<?php echo $mi[$i]->hoverBgColor; ?>')" onmouseout="outMenu(this)">
               <?php echo $mi[$i]->displayName; ?>
          </div>
       </a>-->
       <?php

     }

?>

