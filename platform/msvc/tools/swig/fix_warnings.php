<?php

$c = file_get_contents("../src/love_lua_glue.cpp");

$t = "// Made by AutoLOVE\n// IGNORE WARNINGS PLZ\n"; 

// Disable warnings ...
$t .= "#pragma warning( push )\n";
$t .= "#pragma warning ( disable : 4005)\n";
$t .= "#pragma warning ( disable : 4244)\n";
$t .= "#pragma warning ( disable : 4102)\n";
$t .= "#pragma warning ( disable : 4800)\n";
$t .= "\n\n" . $c;

// And then enable warnings

$t .= "\n\n";
$t .= "// Made by AutoLOVE\n// ENABLE WARNINGS PLZ\n"; 
$t .= "#pragma warning( pop )";


file_put_contents("../src/love_lua_glue.cpp", $t);


?>