<?php

$glue_in = "lualove_glue.cpp";
$types_out = "lualove_types.h";

$std_header = "/*\n" .
"* LOVE: Totally Awesome 2D Gaming.\n" .
"* Website: http://love.sourceforge.net\n" .
"* Licence: ZLIB/libpng\n" .
"* Copyright © 2006-2008 LOVE Development Team\n" .
"*/\n\n\n";

/****************************************************/
/***************** FIX WARNINGS *********************/
/****************************************************/


$c = file_get_contents("../../../../src/$glue_in");

$t = $std_header;

$t .= "// Made by AutoLOVE\n// IGNORE WARNINGS PLZ\n"; 

// Disable warnings ...

$t .= "#ifdef WIN32\n";
$t .= "#pragma warning( push )\n";
$t .= "#pragma warning ( disable : 4005)\n";
$t .= "#pragma warning ( disable : 4244)\n";
$t .= "#pragma warning ( disable : 4102)\n";
$t .= "#pragma warning ( disable : 4800)\n";
$t .= "#endif\n";
$t .= "\n"
    . "#include <list>\n"
    . "#include <string>\n"
    . "using std::list;\n"
    . "using std::string;\n";
$t .= "\n" . $c;

// And then enable warnings

$t .= "\n\n";
$t .= "// Made by AutoLOVE\n// ENABLE WARNINGS PLZ\n"; 
$t .= "#ifdef WIN32\n";
$t .= "#pragma warning( pop )\n";
$t .= "#endif\n";


file_put_contents("../../../../src/$glue_in", $t);


/****************************************************/
/***************** CREATE TYPES	*********************/
/****************************************************/


$out = "/**\n";
$out .= "* @file love_script_types.h\n";
$out .= "* @brief Contains generated types from SWIG.\n";
$out .= "* @date 2006-11-19\n";
$out .= "* @author AUTO-LOVE\n";
$out .= "* THIS FILE IS GENERATED AUTOMAGICALLY.\n";
$out .= "* DO NOT TOUCH THIS FILE.\n";
$out .= "**/\n\n";



$out .= "#ifndef LOVE_SCRIPT_TYPES_H\n";
$out .= "#define LOVE_SCRIPT_TYPES_H\n\n";

$out .= "enum script_types\n";
$out .= "{\n";

// Get file contents
$raw = file_get_contents("../../../../src/$glue_in");

// Convert to lines
$ar = explode("\n", $raw);

// Find type-lines

$ls = sizeof($ar);

for($i=0;$i<$ls;$i++)
{
	if(substr($ar[$i],0,17) == "#define SWIGTYPE_")
	{
		// Strip #define
		$s = substr($ar[$i],17);
		
		// Numeric identifier
		$left_sb = strpos($s, "[");
		$right_sb = strpos($s, "]");
		$n = substr($s, $left_sb + 1, $right_sb - $left_sb - 1);
		
		// Strip swig_types -- from $s
		$s = substr($s, 0, strpos($s, " "));
		
		$out .= "\t";
		$out .= "script_type_" . $s . " = $n,";		
		$out .= "\n";
	}
}

// Remove ",\n" from the back, and add a new \n
$out = substr($out, 0, strlen($out) - 2);
$out .= "\n";


$out .= "};\n";

$out .= "\n#endif\n";

file_put_contents("../../../../src/$types_out", $out);


/****************************************************/
/***************** ADD PUSH POINTER FUNCTION ********/
/****************************************************/



?>