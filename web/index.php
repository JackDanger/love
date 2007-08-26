<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  <head>
    <title>LOVE</title>
    <link rel="stylesheet" type="text/css" href="css/default.css" />

    <!--[if IE]>
    <link rel="stylesheet" type="text/css" href="css/ie.css" />
    <![endif]-->


    <script type="text/javascript" src="js/global.js"></script>
  </head>
  <body>



        <div id="wrap">
             <div id="head">
                  <div id="rainbow">
                       <div id="sun">

                       </div>
                  </div>
                  <div id="body">

                       <div id="left">
                            <div id="menu">
                            	
                            	 <a id="download" href="?page=download">
	                                 <div class="menu_item_large">
	                                      <div class="image">
	                                      </div>
	                                      <div class="text">
	                                           Download Now!
	                                      </div>
	                                      <div class="sub_text">
	                                           Version 0.1pre-a
	                                      </div>
	                                 </div>
                                 </a>

                                 <?php include("php/menu.php"); ?>




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
                 &copy; 2006 - LÖVE Development Team
             </div>
             <div id="links">
                   <a href="http://www.getfirefox.net"><img src="gfx/firefox.png" alt="Get firefox" /></a>
                   <!-- <a href="http://sourceforge.net"><img src="http://sflogo.sourceforge.net/sflogo.php?group_id=174065&amp;type=1" alt="SourceForge.net Logo" /></a> -->
             </div>
        </div>

  </body>
</html>