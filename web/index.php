<?php
 session_start();
 include("php/init.php");
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  <head>
    <title>LOVE</title>
    <link rel="stylesheet" type="text/css" href="css/default.css" />

    <!--[if IE]>
    <link rel="stylesheet" type="text/css" href="css/ie.css" />
    <![endif]-->


	<script type="text/javascript" src="js/prototype.js"></script>
    <script type="text/javascript" src="js/global.js"></script>
  </head>
  <body>
   <div id="imageview" style="display:none;" onclick="javascript:closeImage()">&nbsp;</div>


        <div id="wrap">
             <div id="head">
                  <div id="rainbow">
                       <div id="sun">

                       </div>
                  </div>
                  <div id="body">

                       <div id="left">
                            <div id="menu">
							
								<div id="download">
									<a class="menu_item_large" href="#" style="display:block; padding:22px 25px 0px 25px; border-bottom:1px solid #e2e3e4; height:41px;">
										<div class="image"> </div>
										<div class="text">Coming soon!</div>
										<div class="sub_text">This summer</div>
									</a>
								</div>
								
								<div id="buttons">
									<?php include("php/menu.php"); ?>
								</div>




                            </div>
                       </div>

                       <div id="right">
                       
                       <?php

                       if(!isset($_GET['page']))
                         require("php/home.php");
                       else
                         require("php/".$_GET['page'].".php");

                       ?>




                       </div>  <! -- right -->
                       <div class="breaker">&nbsp;</div>

                  </div>
             </div>

             <div id="bottom">
             </div>

        </div> <! -- Wrap -->

        <div id="subwrap">
             <div id="copyright">
                &copy; <?php echo date("Y"); ?> - LÖVE Development Team
             </div>
             <div id="links">
				<a href="http://sourceforge.net"><img src="http://sflogo.sourceforge.net/sflogo.php?group_id=174065&type=1" alt="SourceForge.net Logo" /></a>
                <a href="http://www.getfirefox.net"><img src="graphics/firefox.png" alt="Get firefox" /></a>
             </div>
        </div>

  </body>
</html>