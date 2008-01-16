<?php

if($argc < 2) die("Incorrect arguments.");

include("lovedoc2.php");


// Get file from cmd.
lovedoc($argv[1]);
?>