<?php

/***
* HTML constants, for cleaner PHP code.
***/

$HTML_PRE = <<< HEADER
          <!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "DTD/xhtml1-strict.dtd">
          <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
            <head>
              <title>LOVEDOC</title>
              <link rel="stylesheet" type="text/css" href="css/default.css" />
              <meta http-equiv="content-type" content="text/html; charset=utf-8"/>
            </head>

            <table class="master-table">
              <tr>
              <td class="left">


              <div class="logo">
                   &nbsp;
              </div>
HEADER;



$HTML_MIDDLE  = <<< MIDDLE
       
          </td>
          <td class="right">
MIDDLE;

$HTML_POST = <<< POST

            </td>
            </tr>
            </table>


      <body>
      </body>
      </html>
POST;


$HTML_CHAPTER_START = <<< CHAPTER_START
               
   <div class="chapter">
  	<div class="header">
  		<span class="title">
CHAPTER_START;

$HTML_CHAPTER_MIDDLE = <<< CHAPTER_MIDDLE
                     </span>
  	</div>
  	<div class="text">

CHAPTER_MIDDLE;


$HTML_CHAPTER_END = <<< CHAPTER_END

        </div>
        </div>
CHAPTER_END;


/***
* GeSHI setup ...
***/

include_once("../php/geshi.php");

$geshi =& new GeSHI("", "lua");
	
$geshi->set_header_type(GESHI_HEADER_NONE);

$geshi->set_keyword_group_style(1, 'color: #1f6ed9; font-weight: bold;', true);
$geshi->set_comments_style(1, 'color: #4db12a;', true);
$geshi->set_brackets_style('color: #1f6ed9;');
$geshi->set_numbers_style('color: #358917;');
$geshi->set_strings_style('color: #a31515;');
$geshi->set_tab_width(3);

/***
* Global helper functions.
***/

function toCode($string)
{
  // Remove whitespace from each line.
  $lines = explode("\n", $string);
  
  for($i=0;$i<sizeof($lines);$i++)
  {
   $lines[$i] = trim($lines[$i]);
  }
  
  $src = implode("\n", $lines);
  $src = str_replace("[tab /]", "\t", $src);
  
  global $geshi;
  
  $geshi->set_source(trim($src));
  
  
  return "<code>".$geshi->parse_code()."</code>";
}
	
function strtocode($string)
{
  global $geshi;
  $geshi->set_source($string);
  return $geshi->parse_code();
}
	
function toHtml($string)
{
 return str_replace(array("[", "]"), array("<", ">"),$string);
}


?>