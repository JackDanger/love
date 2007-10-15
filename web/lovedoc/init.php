<?php

	include_once("../php/geshi.php");

	$geshi =& new GeSHI("", "lua");
	
	$geshi->set_header_type(GESHI_HEADER_NONE);
	
	$geshi->set_keyword_group_style(1, 'color: #1f6ed9; font-weight: bold;', true);
	$geshi->set_comments_style(1, 'color: #4db12a;', true);
	$geshi->set_brackets_style('color: #1f6ed9;');
	$geshi->set_numbers_style('color: #358917;');
	$geshi->set_strings_style('color: #a31515;');
	
	/*$geshi->add_keyword_group(10, 'color: #666; font-weight: bold;', false, array(
		'main', 'init', 'update', 'render', 
		'keyboard:isDown',
		'mouse:getX','mouse:getY',
		'game:addImage',
		'image:render'));*/

	//$geshi->set_url_for_keyword_group(10, "?page=documentation&amp;lookup={FNAME}");
		
	$geshi->set_tab_width(3);
	
	
	function toCode($string)
	{

             global $geshi;
	
             $geshi->set_source(trim($string));


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