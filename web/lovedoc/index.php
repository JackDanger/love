<?php

include("lovedoc.php");
$doc = new LoveDoc();


$verbose = false;



$file = "data.xml";
$depth = array();

$element = "";
$current_attr;

$type;
$func;
$mode = array("root");

function startElement($parser, $name, $attrs)
{
    global $depth;
    global $element;
    global $current_attr;
    global $mode;
    global $verbose;

    global $doc;
    
    array_push($mode, $name);

    end($mode);

    $curr_mode = end($mode);
    $prev_mode = prev($mode);

    $current_attr = $attrs;

    $depth[$parser]++;


    if($name == "documentation")
    {
     if($verbose) echo "Setting documentation attribs<br />";
     $doc->setVersion($attrs);
    }


    if($name == "global")
    {
     if($verbose) echo "Pushing global ...<br />";
     $doc->pushGlobal($attrs);
    }
    
    if($name == "code" && $prev_mode = "global")
    {
     $doc->pushGlobalDataCodeBegin();
    }

    if($name == "type")
    {
     if($verbose) echo "Pushing type ...<br />";
     $doc->pushType($attrs);
    }
    
    if($name == "object")
    {
     if($verbose) echo "Pushing object ...<br />";
     $doc->pushType($attrs);
    }
    
    if($name == "callback")
    {
     if($verbose) echo "Pushing callback ...<br />";
     $doc->pushCallback($attrs);
    }

    if($name == "function")
    {
     if($verbose) echo "Pushing function .. <br />";
     $doc->pushFunction($attrs);
    }

    if($name == "separator" && ($prev_mode == "type" || $prev_mode == "object"))
    {
     if($verbose) echo "Pushing function separator<br />";
     $doc->pushFunctionSeparator();
    }


    if($name == "param")
    {
     if($verbose) echo "Pushing param .. <br />";
     $doc->pushParam($attrs);
    }

    if($name == "returns")
    {
     if($verbose) echo "Pushing return .. <br />";
     $doc->pushReturns($attrs);
    }
    
    if($name == "see" && $prev_mode == "type")
    {
     if($verbose) echo "Pushing see .. <br />";
     $doc->pushTypeSee($attrs);
    }

    if($name == "see" && $prev_mode == "function")
    {
     if($verbose) echo "Pushing see .. <br />";
     $doc->pushFunctionSee($attrs);
    }

    if($name == "example" && $prev_mode == "type")
    {
     if($verbose) echo "Pushing type example.. <br />";
     $doc->pushTypeExample($attrs);
    }

    if($name == "example" && $prev_mode == "function")
    {
     if($verbose) echo "Pushing function example.. <br />";
     $doc->pushFunctionExample($attrs);
    }
    
    if($name == "example" && $prev_mode == "callback")
    {
     if($verbose) echo "Pushing function/callback example.. <br />";
     $doc->pushFunctionExample($attrs);
    }

    $element = $name;



    //echo "Start: mode = $mode, name = $name<br />";

}

function endElement($parser, $name)
{
    global $element;
    global $current_attr;
    global $doc;
    global $mode;
    global $verbose;


    $curr_mode = end($mode);
    $prev_mode = prev($mode);

    array_pop($mode);
    //echo "Popping mode: ".."<br />";

    //echo "End: mode = $mode, name = $name<br />";

    if($curr_mode == "code" && $prev_mode = "global")
    {
     $doc->pushGlobalDataCodeEnd();
    }


    if($name == "type")
    {
     if($verbose) echo "Popping type ...<br />";
     $doc->popType();
    }

    if($name == "callback")
    {
     if($verbose) echo "Popping callback ...<br />";
     $doc->popCallback();
    }
    
    if($name == "object")
    {
     if($verbose) echo "Popping object ...<br />";
     $doc->popObject();
    }


    global $depth;
    $depth[$parser]--;
}

function characterData($parser, $data)
{



    global $element;
    global $current_attr;
    global $doc;
    global $mode;
    global $verbose;
    
    $curr_mode = end($mode);
    $prev_mode = prev($mode);

    if($curr_mode == "global")
    {
          if($verbose) echo "Pushing global data: $data<br />";
          $doc->pushGlobalData($data);
    }
    
    if($curr_mode == "code" && $prev_mode = "global")
    {
          if($verbose) echo "Pushing global CODE: $data<br />";
          $doc->pushGlobalDataCode($data);
    }

    if($curr_mode == "type")
    {
          if($verbose) echo "Pushing type data: $data<br />";
          $doc->pushTypeData($data);
    }

    if($curr_mode == "object")
    {
          if($verbose) echo "Pushing object data: $data<br />";
          $doc->pushTypeData($data);
    }

    if($curr_mode == "function")
    {
     if($verbose) echo "Pushing function data .. <br />";
     $doc->pushFunctionData($data);
    }
    
    if($curr_mode == "callback")
    {
     if($verbose) echo "Pushing function data .. <br />";
     $doc->pushFunctionData($data);
    }

    if($curr_mode == "param")
    {
     if($verbose) echo "Pushing param data .. <br />";
     $doc->pushParamData($data);
    }
    
    if($curr_mode == "returns")
    {
     if($verbose) echo "Pushing returns data .. <br />";
     $doc->pushReturnsData($data);
    }


    if($curr_mode == "example" && $prev_mode == "type")
    {

     if($verbose) echo "Pushing type example data.. $data <br />";
     $doc->pushTypeExampleData($data);
    }

    if($curr_mode == "example" && $prev_mode == "function")
    {
     if($verbose) echo "Pushing function example data.. $data <br />";
      $doc->pushFunctionExampleData($data);
    }
    
    if($curr_mode == "example" && $prev_mode == "callback")
    {
     if($verbose) echo "Pushing callback example data.. $data <br />";
      $doc->pushFunctionExampleData($data);
    }

}

$xml_parser = xml_parser_create();
xml_set_element_handler($xml_parser, "startElement", "endElement");
xml_set_character_data_handler($xml_parser, "characterData");
xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, false);
if (!($fp = fopen($file, "r"))) {
    die("could not open XML input");
}

while ($data = fread($fp, 4096)) {
    if (!xml_parse($xml_parser, $data, feof($fp))) {
        die(sprintf("XML error: %s at line %d",
                    xml_error_string(xml_get_error_code($xml_parser)),
                    xml_get_current_line_number($xml_parser)));
    }
}
xml_parser_free($xml_parser);



$doc->write();



        ?>
