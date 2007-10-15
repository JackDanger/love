<?php
 // Connect to database
 $serverLink = "mysql4-l";
 $serverName = "l174065ro";
 $serverPass = "readonly";
 $dbName = "l174065_web";
 $link = mysql_connect("$serverLink", "$serverName", "$serverPass") or die("Could not connect to MySQL database:" . mysql_error());
 mysql_select_db("$dbName") or die("Could not select database:" . mysql_error());
 
?>