<?php

	include_once("../tools/geshi/geshi.php");

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
	
?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
  <head>
    <title>LOVE Reference manual</title>
    <link rel="stylesheet" type="text/css" href="css/default.css" />
  </head>
  <body>


    <table class="master-table">
    <tr>
    <td class="left">


  	<div class="logo">
		&nbsp;
	</div>
  	<div class="version">
             Version 0.1-pre-a
         </div>


         <div href="#" class="horizontal"></div>
        <a href="#" class="element">Overview</a>
        <a  href="#" class="element">License</a>
        <a  href="#" class="element">Credits</a>
        <a  href="#" class="element">First LÖVE</a>
        <div href="#" class="horizontal"></div>
        <a  href="#" class="element">LÖVE Types</a>
        <a  href="#" class="element">LÖVE Objects</a>
        <div href="#" class="horizontal"></div>
        <a  href="#" class="element">Image</a>
        <a  href="#" class="element">Sound</a>
        <a  href="#" class="element">FrameAnimation</a>
        <div href="#" class="horizontal"></div>
        <a  href="#" class="element">love</a>
        <a  href="#" class="element">game</a>
        <a  href="#" class="element">text</a>
        <a  href="#" class="element">gl</a>


    </td>
    <td class="right">


   <div class="chapter">
  	<div class="header">
  		<span class="title"> Introduction </span>
  	</div>
  	<div class="text">
  		Blah blah blah. The love engine blah blah. 
<br/>
And the license and stuff, reproduced below:
	


		<div class="code">
		<div class="content">
		
		  		
  	<?php
  	
	 $str = "Copyright (c) 2007 LØEV DEVELOMAENT TAEM
	
	This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.
	
	Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:
	
	1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
	
	2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
	
	3. This notice may not be removed or altered from any source distribution.";
	 
	 echo nl2br(htmlspecialchars($str));
	 
	 ?>
	 </div>
		</div>
		
  		


  	</div>
  </div>
  
  <div class="chapter">
  	<div class="header">
  		<span class="title"> 1. Features overview </span>
  	</div>
  	<div class="text">
Vestibulum molestie ante id risus. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Morbi orci ante, congue et, rutrum ac, dictum at, sapien. Donec mi. Aenean ut elit ut urna dignissim hendrerit. Nulla suscipit. Quisque venenatis, arcu id ultrices nonummy, nisl risus pellentesque nunc, nec ullamcorper ante tortor non justo. Proin elit. 
<br /><br />
Mauris pede arcu, lobortis vel, malesuada in, posuere eget, elit. Maecenas euismod metus porta enim posuere malesuada. Aenean rhoncus. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos hymenaeos. Sed feugiat, orci quis tincidunt tincidunt, diam quam tempor justo, ac viverra enim metus in arcu. In aliquet. Duis vehicula eros et urna. Donec vel urna. Vivamus ac neque. Praesent eleifend. Morbi eleifend nisl et lorem pharetra tempus. Vestibulum non mi. Morbi tempor suscipit turpis. Integer fringilla nisi non felis. Nam condimentum. Proin sem. Etiam facilisis sodales enim. Nullam nec lacus. 
<br /><br />
Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos hymenaeos. Etiam in urna. Mauris laoreet gravida dolor. Donec varius urna at dui. Nam imperdiet augue nec purus. Aliquam ultrices, ipsum eget ornare ornare, neque dui nonummy erat, in fringilla nulla velit quis eros. Sed ut elit. Vivamus lorem. In adipiscing lectus at pede. Curabitur eget mauris. Curabitur euismod elit sed dolor. Nunc eu risus at nunc sollicitudin eleifend. In augue enim, eleifend vitae, gravida sed, vehicula ac, diam. Maecenas libero risus, consectetuer et, semper non, viverra non, ante. Curabitur vestibulum cursus dolor. Aliquam erat volutpat. Vivamus a eros eu augue pharetra aliquet.  		
  	</div>
  </div>
  

    <div class="chapter">
  	<div class="header">
  		<span class="title"> 2. Data Type Index </span>
  	</div>
  	<div class="text">
  		<div class="float_list">
  			<div class="header">Core</div>
  			<div class="element">game</div>
  			<div class="element">timer</div>
   			<div class="element">mouse</div>
  			<div class="element">keyboard</div>
  		</div>
   		<div class="float_list">
   			<div class="header"> Name plz</div>
  			<div class="element">Image</div>
  			<div class="element">Sound</div>
  		</div>
  	</div>
  </div>
  
  <div class="chapter">
  	<div class="header">
  		<span class="title"> 3. Function Index </span>
  	</div>
  	<div class="text">
  		<div class="float_list">
  			<div class="header"> zomg 1</div>
  			<div class="element">game:addImage</div>
  			<div class="element">game:getImage</div>
  			<div class="element">game:deleteImage</div>
  			<div class="element">game:isImage</div>
  			<div class="element">image:render</div>
  			<div class="element">image:load</div>
  			<div class="element">sound:play</div>
  			<div class="element">Image</div>
   			<div class="element">Image</div>
  			<div class="element">ImageImage</div>
  			<div class="element">Image</div>
  			<div class="element">Audio</div>
  			<div class="element">AbstractEntityController</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  		</div>
  		<div class="float_list">
  			<div class="header"> Listing 1</div>
  			<div class="element">Image</div>
  			<div class="element">ImageImage</div>
  			<div class="element">Image</div>
  			<div class="element">Audio</div>
  			<div class="element">AbstractEntityController</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  			<div class="element">ImageImage</div>
  			<div class="element">Image</div>
  			<div class="element">Audio</div>
  			<div class="element">AbstractEntityController</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
 
  		</div>
   		<div class="float_list">
   			<div class="header"> Listing 1</div>
  			<div class="element">Image</div>
  			<div class="element">ImageImage</div>
  			<div class="element">Image</div>
  			<div class="element">Audio</div>
  			<div class="element">AbstractEntityController</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  		</div>  		
  	</div>
  </div>
  
  
  
  
  
  <div class="chapter">
  	<div class="header">
  		<span class="title"> 4. Examples Index </span>
  	</div>
  	<div class="text">
  		<div class="float_list">
  			<div class="header"> Listing 1</div>
  			<div class="element">Image</div>
  			<div class="element">ImageImage</div>
  			<div class="element">Image</div>
  			<div class="element">Audio</div>
  			<div class="element">AbstractEntityController</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  		</div>
  		<div class="float_list">
  			<div class="header"> Listing 1</div>
  			<div class="element">Image</div>
  			<div class="element">ImageImage</div>
  			<div class="element">Image</div>
  			<div class="element">Audio</div>
  			<div class="element">AbstractEntityController</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  		</div>
  		<div class="float_list">
  			<div class="header"> Listing 1</div>
  			<div class="element">Image</div>
  			<div class="element">ImageImage</div>
  			<div class="element">Image</div>
  			<div class="element">Audio</div>
  			<div class="element">AbstractEntityController</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  			<div class="element">Image</div>
  		</div>
  	</div>
  </div> 
 
  
  
  
  
  
  
  
  
  	<div class="chapter">
  	<div class="header">
  		<span class="title"> Data Types </span>
  	</div>
  	
  	
 	<?php for($i=0;$i<10;$i++){ ?>
  	
   	<div class="subchapter">
  		<div class="title">Image</div>
	  	<div class="text">
	  		Blah blah 
	  	</div>
	  	
	  	
	  	
  	
	  	
	  	
	  	<div class="section">
	  		<div class="functions">
		  		<div class="title">Functions</div>
	  		<div class="code">
	  		
	  			<div class="content">
		  			<code>
		  			
		  			<a href="#">
		  			<?php
		  				$geshi->set_source("image:render( x, y )");
		  				echo $geshi->parse_code();
		  			?>	  		
		  			</a>
					<br />
					<a href="#">
		  			<?php
		  				$geshi->set_source("image:load()");
		  				echo $geshi->parse_code();
		  			?>	  		
		  			</a>
					<br />
					<a href="#">
		  			<?php
		  				$geshi->set_source("image:replaceColor( color_src, color_dest )");
		  				echo $geshi->parse_code();
		  			?>	  	
		  			</a>
		  				
		  			</code>
		  			
		  		</div>



	  		
	  		</div>
				</div>
	  	</div>
	  	
	  	<div class="section">
	  		<div class="title">Examples</div>
	  		


	  		
		     <div class="textmenu" style="width: 50%; border-top: none;">
				<div class="items">
					<a href="#"><div class="item" style="border-color: #ddd;"> + Using Images</div></a>
					<a href="#"><div class="item" style="border-color: #ddd;"> + Advanced Cockrocet- and Imagery</div></a>
				</div>
		     </div>
     
     
	  	</div>
	  	<div class="section">
	  		<div class="title">See also</div>
	  		
	  		
		     <div class="textmenu" style="width: 50%; border-top: none;">
				<div class="items">
					<a href="#"><div class="item" style="border-color: #ddd;"> + Tutorial 6: Fuzzy stuff</div></a>
				</div>
		     </div>
     
     
     
	  	</div>
  	</div> <!-- subchapter -->
  	
  	<?php } ?>
  	
  	
  	
  	
  </div>
  
  
  
  
  
  
  
  
  
  
  
  
  
   <div class="chapter">
  	<div class="header">
  		<span class="title"> Functions </span>
  	</div>
  	
  	
 	<?php for($i=0;$i<10;$i++){ ?>
  	
   	<div class="subchapter">
  		<div class="title">addImage</div>
	  	<div class="text">
	  		Loads an image.
	  	</div>
	  	
	  	
	  	
	  	<div class="section">
	  		<div class="title">Usage</div>
	  		<div class="code">
	  		
	  		<div class="content">
	  			<code>
	  			<?php
	  				$geshi->set_source("game:addImage( name, filename );");
	  				echo $geshi->parse_code();
	  			?>	  		
	  			</code>
	  		</div>
	  		
	  		</div>
	  	</div>
	  	
	  	
	  	
	  	<div class="section">
	  		<div class="arguments">
		  		<div class="title">Arguments</div>
		  		<div class="entry"><span class="name">name</span>The image's internal name.</div>
		  		<div class="entry"><span class="name">filename</span>The file from which to load the image.</div>
				</div>
	  	</div>
	  	
	  	<div class="section">
	  		<div class="title">Examples</div>
	  		


	  		<div class="code">
	  		
		  		<div class="content">
		  			<code>
		  			<?php
		  				$geshi->set_source("-- Example 1. \nimage = game:addImage( name, filename );");
		  				echo $geshi->parse_code();
		  			?>	  		
		  			</code>
		  		</div>
	  		
	  		</div>

	  		
		     <div class="textmenu" style="width: 50%; border-top: none;">
				<div class="items">
					<a href="#"><div class="item" style="border-color: #ddd;"> + Using Images</div></a>
				</div>
		     </div>
     
     
	  	</div>
	  	<div class="section">
	  		<div class="title">See also</div>
	  		
	  		
		     <div class="textmenu" style="width: 50%; border-top: none;">
				<div class="items">
					<a href="#"><div class="item" style="border-color: #ddd;"> + Tutorial 6: Fuzzy stuff</div></a>
				</div>
		     </div>
     
     
     
	  	</div>
  	</div> <!-- subchapter -->
  	
  	<?php } ?>
  	
  	
  	
        </td>
        </tr>
        </table>



   
  </body>
</html>