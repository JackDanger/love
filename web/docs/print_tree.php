<?php

include_once('XMLParser.php');


if($fh = fopen("data.xml", "r")) {
	$parser = new XMLParser($fh, 'stream', 1);
	$result = $parser->getTree();
	fclose($fh);
}
  
$tree = $parser->getTree();

  echo "<pre>";
  print_r($tree);
  echo "</pre>";
  
  
  
  if($fh = fopen("functions.xml", "r")) {
	$parser = new XMLParser($fh, 'stream', 1);
	$result = $parser->getTree();
	fclose($fh);
}
  
$tree = $parser->getTree();

  echo "<pre>";
  print_r($tree);
  echo "</pre>";
 
  
?>