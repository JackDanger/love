<?php

     // Definition of MenuItem class.
     class MenuItem
     {
             var $file;
             var $displayName;
             var $bgColor;
             var $hoverBgColor;

             function MenuItem($file, $displayName, $bgColor, $hoverBgColor)
             {
               $this->file = $file;
               $this->displayName = $displayName;
               $this->bgColor = $bgColor;
               $this->hoverBgColor = $hoverBgColor;
             }
     }

     // Array of MenuItems
     $mi = array(
                new MenuItem("home", "Home", "#f9f9f9", "#ff3f19"),
                new MenuItem("features", "Features", "#ffffff", "#92278f"),
                new MenuItem("screenshots", "Screenshots", "#ffffff", "#28903a"),
                new MenuItem("documentation", "Documentation", "#ffffff", "#b0b0b0"),
                new MenuItem("projects", "Projects", "#ffffff", "#0072bc"),
                new MenuItem("faq", "FAQ", "#ffffff", "#7abb25"),
                new MenuItem("contact", "Contact", "#ffffff", "#4e85e0"), 
                new MenuItem("page_tool_demo", "Page Tool Demo", "#ffffff", "#4e85e0"),
                new MenuItem("tut_demo", "Tutorial demo", "#ffffff", "#4e85e0")
     );
     
     // Output menu
     
     for($i=0;$i<sizeof($mi);$i++)
     {

       ?>
       <a href="?page=<?php echo $mi[$i]->file; ?>">
          <div class="menu_item_medium" style="background-color: <?php echo $mi[$i]->bgColor; ?>" onmouseover="overMenu(this, '<?php echo $mi[$i]->hoverBgColor; ?>')" onmouseout="outMenu(this)">
               <?php echo $mi[$i]->displayName; ?>
          </div>
       </a>
       <?php

     }

?>

