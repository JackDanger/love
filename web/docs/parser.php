<?php require_once('db_start.php'); ?>

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
  
  <div class="header">

  	<div class="logo">
		&nbsp;
	</div>
	<div class="refman">
         Reference Manual
         </div>
  	<div class="version">Version 0.1-pre-a</div>
  	</div>
  
  
   <div class="chapter">
  	<div class="header">
  		<span class="title"> Introduction </span>
  	</div>
  	<div class="text">
     
             <?php
             
             $sql = "SELECT * FROM doc_globals WHERE id = 'pre-intro'";
             $res = mysql_query($sql) or die(mysql_error());
             $row = mysql_fetch_array($res);
             
             echo nl2br(htmlentities($row['text']));


             ?>




		<div class="code">
		<div class="content">
		
		  		
             <?php
             
             $sql = "SELECT * FROM doc_globals WHERE id = 'license'";
             $res = mysql_query($sql) or die(mysql_error());
             $row = mysql_fetch_array($res);

             echo nl2br(htmlentities($row['text']));


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




             <?php
             
             $sql = "SELECT * FROM doc_globals WHERE id = 'overview'";
             $res = mysql_query($sql) or die(mysql_error());
             $row = mysql_fetch_array($res);

             echo nl2br(htmlentities($row['text']));


             ?>



        </div>
  </div>




<?php

/***********************************************************************
 * Output types index
 ***********************************************************************/

//$sql = 'SELECT * FROM doc_data_types ORDER BY `order` ASC';
//$res = mysql_query($sql) or die(mysql_error());

		
?>

    <div class="chapter">
  	<div class="header">
  		<span class="title"> 2. Data Type Index </span>
  	</div>
  	<div class="text">
  		<div class="float_list">

			<?php

			// Get data data_types_data
			$sql = 'SELECT * FROM doc_data_types ORDER BY `order` ASC';
			$res = mysql_query($sql) or die(mysql_error());
			
			while ($row = mysql_fetch_array($res)) 
			{
				echo '<div class="element"><a href="#'.$row['name'].'">'.$row['name'].'</a></div>';
			}

			?>
  			
  		</div>
  	</div>
  </div>
  
  
<?php

/***********************************************************************
 * Output function index 
 ***********************************************************************/

$sql = 'SELECT * FROM doc_data_types ORDER BY `order` ASC';
$res = mysql_query($sql) or die(mysql_error());


?>

    <div class="chapter">
  	<div class="header">
    <span class="title"> 3. Function list </span>
  	</div>
  	<div class="text">
  		<div class="float_list">


			<?php
			
			$sql = 	'	SELECT 
						doc_data_types.name AS type_name, 
						doc_functions.name AS function_name,
						doc_functions.id AS function_id,
						doc_functions.text
						FROM doc_data_types, doc_functions 
						WHERE doc_functions.data_type_id = doc_data_types.id 
						ORDER BY doc_data_types.`order`, doc_functions.`order` ASC';
			$res = mysql_query($sql) or die(mysql_error());
			
			
			while ($row = mysql_fetch_array($res)) {
				
		
				/**
				 * Get parameters 
				 */
				
				$ssql = '	SELECT *
							FROM doc_function_arguments	
							WHERE doc_function_arguments.function_id = '.$row['function_id'].'	
							ORDER BY `order` ASC';
				$ssres = mysql_query($ssql) or die(mysql_error());
				
				// Number of parameters
				$nump = mysql_num_rows($ssres);
				
				$par = "(";
				$i = 0;
				
				$formatted_parameter_list = "";
				
				// Add parameters
				while ($ssrow = mysql_fetch_array($ssres)) {
					$par .= ($i == ($nump-1) ? " ".$ssrow['name']." " : " ".$ssrow['name'].",");
					$i++;
					
					$formatted_parameter_list .= '<div class="entry"><span class="name">'.$ssrow['name'].'</span>'.$ssrow['text'].'</div>';
		
					
				}
				
				$par .= ")";
				
				$short_function_name = $row['function_name'].$par;
				$full_function_name = $row['type_name'].":".$row['function_name'].$par;
			

				echo '<div class="element"><a href="#'.$full_function_name.'">'.$full_function_name.'</a></div>';
			}


			?>
  			
  		</div>
  	</div>
  </div>
  
  
  
  
  
<?php

/***********************************************************************
* Output examples index
***********************************************************************/
// Get data data_types_data
$sql = 'SELECT * FROM doc_examples ORDER BY title';
$res = mysql_query($sql) or die(mysql_error());

?>

<div class="chapter">
	<div class="header">
		<span class="title"> 4. Example index </span>
	</div>
	<div class="text">
		<div class="float_list">
	
			<?php


				
				while ($row = mysql_fetch_array($res)) 
				{
					echo '<div class="element"><a href="#example'.$row['id'].'">'.$row['title'].'</a></div>';
				}
	
			?>
			
		</div>
	</div>
</div>
  
  
  
  
  
  
<?php

/***********************************************************************
 * Output types long list
 ***********************************************************************/

//$sql = 'SELECT * FROM doc_data_types ORDER BY `order` ASC;
//$res = mysql_query($sql) or die(mysql_error());

		
?>

  	<div class="chapter">
  	<div class="header">
  		<span class="title"> Data Types </span>
  	</div>

	<?php

	// Get data data_types_data
	$sql = 'SELECT * FROM doc_data_types ORDER BY `order` ASC';
	$res = mysql_query($sql) or die(mysql_error());
	
	while ($row = mysql_fetch_array($res)) {
		
		$subql = '	SELECT * FROM doc_functions 	
					WHERE doc_functions.data_type_id = '.$row['id'].'	
					ORDER BY `order` ASC';
		$subres = mysql_query($subql) or die(mysql_error());
		
	?>
  	
   	<div class="subchapter">
  		<div class="title"><?php echo '<a id="'.$row['name'].'">'.$row['name']."</a>"; ?></div>
	  	<div class="text">
	  		<?php echo $row['description']; ?> 
	  	</div>
	  	
	  	<div class="section">
	  		<div class="functions">
		  		<div class="title">Functions</div>
	  		<div class="code">
	  		
	  			<div class="content">
		  			<code>
		  					  	
		  			<?php
						while ($subrow = mysql_fetch_array($subres)) {
							
							$ssql = '	SELECT *
										FROM doc_function_arguments	
										WHERE doc_function_arguments.function_id = '.$subrow['id'].'	
										ORDER BY `order` ASC';
							$ssres = mysql_query($ssql) or die(mysql_error());
							
							// Number of parameters
							$nump = mysql_num_rows($ssres);
							
							$par = "(";
							$i = 0;
							
							// Add parameters
							while ($ssrow = mysql_fetch_array($ssres)) {
								$par .= ($i == ($nump-1) ? " ".$ssrow['name']." " : " ".$ssrow['name'].",");
								$i++;
							}
							
							$par .= ")";
							
							$src = $row['name'].":".$subrow['name'].$par;
							
							$geshi->set_source($src);
							echo '<a href="#'.$src.'">'.$geshi->parse_code()."</a><br />";
						}
		  			?>	  		

		  				
		  			</code>
		  			
		  		</div>



	  		
	  		</div>
				</div>
	  	</div>
	  	
	  	<div class="section">
	  		<div class="title">Examples</div>
	  		



		     <div class="textmenu" style="width: 50%; border-top: none;">
				<div class="items">
                                     <?php
                                          $e_sql = 'SELECT doc_examples.id, doc_examples.title
                                                    FROM doc_examples, doc_data_types_examples
                                                    WHERE doc_examples.id = doc_data_types_examples.example_id AND
                                                    doc_data_types_examples.data_type_id = '.$row['id'];
                                          $e_res = mysql_query($e_sql) or die(mysql_error());

                                          while($e_row = mysql_fetch_array($e_res))
                                          {
                                     ?>

					<a href="#example<?php echo $e_row['id']; ?>"><div class="item" style="border-color: #ddd;"> + <?php echo $e_row['title']; ?></div></a>

                                     <?php
                                          }
                                     ?>
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
  	
  	<?php } // for loop ?>
  	
  	
  	</div><!-- chapter -->
  	
  	
  	

  	
  	
  	
<?php
  	
/***********************************************************************
 * Output functions long list
 ***********************************************************************/

		
?>

  	<div class="chapter">
  	<div class="header">
  		<span class="title"> Function Types </span>
  	</div>

	<?php
	
	$sql = 	'	SELECT 
				doc_data_types.name AS type_name, 
				doc_functions.name AS function_name,
				doc_functions.id AS function_id,
				doc_functions.text
				FROM doc_data_types, doc_functions 
				WHERE doc_functions.data_type_id = doc_data_types.id 
				ORDER BY doc_data_types.`order`, doc_functions.`order` ASC';
	$res = mysql_query($sql) or die(mysql_error());
	
	
	while ($row = mysql_fetch_array($res)) {
		

		/**
		 * Get parameters 
		 */
		
		$ssql = '	SELECT *
					FROM doc_function_arguments	
					WHERE doc_function_arguments.function_id = '.$row['function_id'].'	
					ORDER BY `order` ASC';
		$ssres = mysql_query($ssql) or die(mysql_error());
		
		// Number of parameters
		$nump = mysql_num_rows($ssres);
		
		$par = "(";
		$i = 0;
		
		$formatted_parameter_list = "";
		
		// Add parameters
		while ($ssrow = mysql_fetch_array($ssres)) {
			$par .= ($i == ($nump-1) ? " ".$ssrow['name']." " : " ".$ssrow['name'].",");
			$i++;
			
			$formatted_parameter_list .= '<div class="entry"><span class="name">'.$ssrow['name'].'</span>'.$ssrow['text'].'</div>';

			
		}
		
		$par .= ")";
		
		$short_function_name = $row['function_name'].$par;
		$full_function_name = $row['type_name'].":".$row['function_name'].$par;
		
		
		
	?>
  	
   	<div class="subchapter">
  		<div class="title"><?php echo '<a id="'.$full_function_name.'">'.$full_function_name.'</a>'; ?></div>
	  	<div class="text">
	  		<?php echo $row['text']; ?> 
	  	</div>
	  	
	  	<div class="section">
	  		<div class="functions">
		  		<div class="title">Usage</div>
	  		<div class="code">
	  		
	  			<div class="content">
		  			<code>
		  					  	
		  			<?php

							$geshi->set_source($full_function_name);
							echo $geshi->parse_code();
		  			?>	
		  			
		  				
		  			</code>
		  			
		  		</div>

	  		
	  		</div><!-- code -->

			<div class="section">
				<div class="arguments">
					<div class="title">Arguments</div>
					
					<?php echo $formatted_parameter_list; ?>
				</div>
			</div>
					
				</div>
	  	</div>
	  	
	  	<div class="section">
	  		<div class="title">Examples</div>
	  		


	  		
		     <div class="textmenu" style="width: 50%; border-top: none;">
				<div class="items">
				
                                     <?php
                                          $e_sql = 'SELECT doc_examples.id, doc_examples.title
                                                    FROM doc_examples, doc_functions_examples 
                                                    WHERE doc_examples.id = doc_functions_examples.example_id AND
                                                    doc_functions_examples.function_id = '.$row['function_id'];
                                          $e_res = mysql_query($e_sql) or die(mysql_error());

                                          while($e_row = mysql_fetch_array($e_res))
                                          {
                                     ?>

					<a href="#example<?php echo $e_row['id']; ?>"><div class="item" style="border-color: #ddd;"> + <?php echo $e_row['title']; ?></div></a>

                                     <?php
                                          }
                                     ?>
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
  	
  	<?php } // for loop ?>
  	
  	
  	</div><!-- chapter -->










<?php

/***********************************************************************
 * Output Example long list
 ***********************************************************************/

?>

  	<div class="chapter">
  	<div class="header">
  		<span class="title"> Examples </span>
  	</div>

	<?php

	$sql = 'SELECT * FROM doc_examples';
	$res = mysql_query($sql) or die(mysql_error());


	while ($row = mysql_fetch_array($res)) {
		
	?>

   	<div class="subchapter">
  		<div class="title"><?php echo '<a id="example'.$row['id'].'">'.$row['title'].'</a>'; ?></div>

	  		<div class="code">
	  		
	  			<div class="content">
		  			<code>

		  			<?php

							$geshi->set_source($row['text']);
							echo $geshi->parse_code();
		  			?>	

		  				
		  			</code>
		  			
		  		</div>

	  		
	  		</div><!-- code -->

  	</div> <!-- subchapter -->
  	
  	<?php } // for loop ?>
  	
  	
  	</div><!-- chapter -->

  	
  	
  	
  	
  	
  	
  	
  	
  	 	
  	
  	
  	
  	
  	
  	
  	
  
<?php require_once('db_end.php'); ?>



</body>

</html>