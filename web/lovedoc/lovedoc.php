<?php

include_once("init.php");

include("LoveType.php");

class LoveGlobal
{
 public $name;
 public $url;
 public $data;
}

class LoveDoc
{

      var $version = "";
      var $love_types = array();
      var $love_objects = array();
      var $love_callbacks = array();
      var $global_text = array();
      
      var $temp_code = "";

      var $pre;
      var $middle;
      var $post;
      
      // States.
      public $type;
      public $func;
      public $param;

      // Temp type
      public $t_data = "";


      function __construct() {


      $this->pre = <<< HEADER
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




       $this->middle = <<< MIDDLE
       
          </td>
          <td class="right">
MIDDLE;

       $this->post = <<< POST

            </td>
            </tr>
            </table>


      <body>
      </body>
      </html>
POST;


      }

      function setVersion($atr)
      {
      
       $version = isset($atr['version']) ? $atr['version'] : "UNKNOWN VERSION";

        $this->pre .= '<div class="version">';
        $this->pre .= $version;
        $this->pre .= '</div>';
      }

      function pushGlobal($atr)
      {
         $name = isset($atr['name']) ? $atr['name'] : "";
         $url = isset($atr['url']) ? $atr['url'] : "";

         $g = new LoveGlobal();
         $g->name = $name;
         $g->url = $url;

         $this->global_text[] = $g;
      }
      
      function pushGlobalData($data)
      {
         $current_global = end($this->global_text);
         $current_global->data .= toHtml($data);
      }
      
      function pushGlobalDataCodeBegin()
      {
         $current_global = end($this->global_text);
         $current_global->data .= "<code>";
         $this->temp_code = "";
      }

      function pushGlobalDataCodeEnd()
      {
         $current_global = end($this->global_text);
         $current_global->data .= strtocode(trim($this->temp_code)) . "</code>";
      }

      function pushGlobalDataCode($code)
      {
         $this->temp_code .= $code;
      }

      function pushType($atr)
      {
         $name = isset($atr['name']) ? $atr['name'] : "";
         $brief = isset($atr['brief']) ? $atr['brief'] : "";

         $this->type = new LoveType($name, $brief, $brief . " ");
      }

      function pushCallback($atr)
      {
         $name = isset($atr['name']) ? $atr['name'] : "";
         $brief = isset($atr['brief']) ? $atr['brief'] : "";

         $this->func = new LoveFunction($name, $brief, $brief . " ");
      }

      function pushTypeData($data)
      {
        if(strlen(trim($data)) > 0)
        {
        $this->type->description .= trim($data);
        }
      }


      function pushFunction($atr)
      {
         $name = isset($atr['name']) ? $atr['name'] : "";
         $brief = isset($atr['brief']) ? $atr['brief'] : "";

         $this->func = new LoveFunction($name, $brief, $brief . " ", $this->type->name);

         $this->type->add($this->func);
      }

      function pushFunctionData($data)
      {
        if(strlen(trim($data)) > 0)
        {
        $current_function = $this->func; //end($this->type->love_functions);
        $current_function->description .= trim($data);
        }
      }
      
      function pushFunctionSeparator()
      {
       $this->type->add(false);
      }

      function pushTypeSee($atr)
      {
         $name = isset($atr['name']) ? $atr['name'] : "";
         $url = isset($atr['url']) ? $atr['url'] : "";

       $this->type->see_also[$name] = $url;
      }
      
      function pushFunctionSee($atr)
      {
         $name = isset($atr['name']) ? $atr['name'] : "";
         $url = isset($atr['url']) ? $atr['url'] : "";

         $current_function = $this->func; //end($this->type->love_functions);

       $current_function->see_also[$name] = $url;
      }

      function pushTypeExample($atr)
      {
        $name = isset($atr['name']) ? $atr['name'] : "";
        $this->type->examples[$name] = "";
      }

      function pushTypeExampleData($data)
      {
        $lastkey = end(array_keys($this->type->examples));

        $this->type->examples[$lastkey] .= $data;
      }

      function pushFunctionExample($atr)
      {
        $current_function = $this->func; //end($this->type->love_functions);
        $name = isset($atr['name']) ? $atr['name'] : "";
        $current_function->examples[$name] = "";
      }

      function pushFunctionExampleData($data)
      {
        $current_function = $this->func; //end($this->type->love_functions);
        $lastkey = end(array_keys($current_function->examples));
        $current_function->examples[$lastkey] .= $data;
      }

      function pushParam($atr)
      {
         $name = isset($atr['name']) ? $atr['name'] : "";
         $brief = isset($atr['brief']) ? $atr['brief'] : "";

         $current_function = $this->func; //end($this->type->love_functions);
         $current_function->add($name, $brief);
      }
      
      function pushReturns($atr)
      {
         $type = isset($atr['type']) ? $atr['type'] : "";
         $brief = isset($atr['brief']) ? $atr['brief'] : "";

         $current_function = $this->func; //end($this->type->love_functions);
         $current_function->returns->name = $type;
         $current_function->returns->description = $brief;
      }

      function pushReturnsData($data)
      {
        if(strlen(trim($data)) > 0)
        {
        $current_function = $this->func; //end($this->type->love_functions);
        $current_function->returns->description .= $data;
        }
      }

      function pushParamData($data)
      {
        $current_function = $this->func; //end($this->type->love_functions);
        $current_parameter = end($current_function->love_parameters);

        $current_parameter->description .= $data;
      }
      
      function popType()
      {
      
          if(strlen(trim($this->type->description)) <= 0)
             $this->type->description = $this->type->brief;

             $this->type->type = "t";
             foreach($this->type->love_functions as $f)
              $f->parent_type = "t";

          $this->love_types[] = $this->type;
      }

      function popObject()
      {
      
          if(strlen(trim($this->type->description)) <= 0)
             $this->type->description = $this->type->brief;

             $this->type->type = "o";
             foreach($this->type->love_functions as $f)
              $f->parent_type = "o";

          $this->love_objects[] = $this->type;
      }
      
      function popCallback()
      {

          if(strlen(trim($this->func->description)) <= 0)
             $this->func->description = $this->func->brief;

          $this->love_callbacks[] = $this->func;
      }

      function createType($atr, $data)
      {

       $name = isset($atr['name']) ? $atr['name'] : "";
       $brief = isset($atr['brief']) ? $atr['brief'] : "";
       $description = isset($data) ? $data : "";
       $description = $description == "" ? $brief : $description;

       $type = new LoveType($name, $brief, $description);
       
       return $type;

      }

      function getTypesList()
      {
         $html = '<div class="subchapter">';
         $html .= '<div class="title">';
         $html .= 'L&#214;VE Types';
         $html .= '</div>';
         $html .= '<div class="text">';
         $html .= '';
         $html .= '</div>';
  
  
         $html .= '<div class="section">';
         $html .= '<div class="title">Types</div>';
         $html .= '<table cellspacing="0" class="functions">';

               foreach($this->love_types as $k=>$v)
               {
                if($v === false)
                    $html .= '<tr><td class="sep"></td><td class="sep"></td><tr>';
                else
                    $html .= '<tr><td class="signature"><a href="'.$v->type.$v->name.'.html">'.$v->name.'</a></td><td class="brief">'.$v->brief.'</td><tr>';
  
               }
  
         $html .= '</table>';
         $html .= '</div>';
         $html .= '</div>';
         
         
         

         
         
         $html .= '</div>';
         
         return $html;

      }
      
      function getObjectsList()
      {
         $html = '<div class="subchapter">';
         $html .= '<div class="title">';
         $html .= 'L&#214;VE Objects';
         $html .= '</div>';
         $html .= '<div class="text">';
         $html .= 'Blah blah blah, global objects blah blah.';
         $html .= '</div>';
  
  
         $html .= '<div class="section">';
         $html .= '<div class="title">Objects</div>';
         $html .= '<table cellspacing="0" class="functions">';

               foreach($this->love_objects as $k=>$v)
               {
                if($v === false)
                    $html .= '<tr><td class="sep"></td><td class="sep"></td><tr>';
                else
                    $html .= '<tr><td class="signature"><a href="'.$v->type.$v->name.'.html">'.$v->name.'</a></td><td class="brief">'.$v->brief.'</td><tr>';
               }
  
         $html .= '</table>';
         $html .= '</div>';
         $html .= '</div>';
         $html .= '</div>';

         return $html;
      }


      function getCallbacksList()
      {
         $html = '<div class="subchapter">';
         $html .= '<div class="title">';
         $html .= 'L&#214;VE Callbacks';
         $html .= '</div>';
         $html .= '<div class="text">';
         $html .= 'Callbacks, lol';
         $html .= '</div>';
  
  
         $html .= '<div class="section">';
         $html .= '<div class="title">Functions</div>';
         $html .= '<table cellspacing="0" class="functions">';

               foreach($this->love_callbacks as $k=>$v)
               {
                if($v === false)
                    $html .= '<tr><td class="sep"></td><td class="sep"></td><tr>';
                else
                    $html .= '<tr><td class="signature"><a href="'.$v->type.$v->name.'.html">'.$v->name.'</a></td><td class="brief">'.$v->brief.'</td><tr>';
               }
  
         $html .= '</table>';
         $html .= '</div>';
         $html .= '</div>';
         $html .= '</div>';
         
         return $html;
      }

      function getMenu()
      {
      
       $tmp = "";

        $tmp .= '<div class="horizontal"></div> ';
        
        foreach($this->global_text as $g)
        {
        $tmp .= '<a  href="'.$g->url.'" class="element">'.$g->name.'</a> ';
        }

        $tmp .= '<div class="horizontal"></div> ';

	$tmp .= '<a href="loveObjects.html" class="element_title">L&#214;VE Devices</a> ';
        $tmp .=  $this->getObjectMenu();

        $tmp .= '<div href="#" class="horizontal"></div>';

        $tmp .= '<a href="loveTypes.html" class="element_title">L&#214;VE Types</a>';
        $tmp .=  $this->getTypeMenu();
        
        $tmp .= '<div class="horizontal"></div> ';
	
	$tmp .= '<a href="callbacks.html" class="element_title">L&#214;VE Callbacks</a> ';
	 $tmp .=  $this->getCallbacksMenu();



        return $tmp;
      }

      function put_string($filename, $out, $title)
      {
      
      
               $chapter_start = <<< CHAPTER_START
               
   <div class="chapter">
  	<div class="header">
  		<span class="title"> $title </span>
  	</div>
  	<div class="text">
CHAPTER_START;

               $chapter_end = <<< CHAPTER_END

        </div>
        </div>
CHAPTER_END;


               $to_file = $this->pre . $this->getMenu() . $this->middle . $chapter_start . $out . $chapter_end . $this->post;
               file_put_contents("out/".$filename, $to_file);

      }

      function put_file($filename, $file_in, $title)
      {
       $this->put_string($filename, file_get_contents($file_in), $title);
      }

      function write()
      {
        // Write globals
        foreach($this->global_text as $g)
        {
          $this->put_string($g->url, $g->data, $g->name);
        }

        $out = "";

        // Write types
        foreach($this->love_types as $t)
        {

         // Write type
         $this->put_string($t->type.$t->name.".html", $t->getFull(), "L&#214;VE Type");

         // Write functions
         foreach($t->love_functions as $f)
         {
           if($f !== false)
           $this->put_string($f->getUrl(), $f->getFull(), "Function");
         }

        }
        
        
        // Write objects
        foreach($this->love_objects as $t)
        {

         // Write type
         $this->put_string($t->type.$t->name.".html", $t->getFull(), "L&#214;VE Object");

         // Write functions
         foreach($t->love_functions as $f)
         {
           if($f !== false)
           $this->put_string($f->getUrl(), $f->getFull(), "Function");
         }

        }
        
        // Write callbacks
        foreach($this->love_callbacks as $t)
        {

         // Write type
         $this->put_string($t->type.$t->name.".html", $t->getFull(), "L&#214;VE Callback");

        }
        
        // Write lists
        $this->put_string("loveTypes.html", $this->getTypesList(), "L&#214;VE Types");
        $this->put_string("loveObjects.html", $this->getObjectsList(), "L&#214;VE Devices");
        $this->put_string("callbacks.html", $this->getCallbacksList(), "L&#214;VE Callbacks");

      }

      function getTypeMenu()
      {

        $html = "";

        foreach($this->love_types as $t)
        {
         $html .= $t->getMenuItem();
        }
        
        return $html;
      }
      
      function getObjectMenu()
      {
      
        $html = "";

        foreach($this->love_objects as $t)
        {
         $html .= $t->getMenuItem();
        }
        
        return $html;
      }
      
      function getCallbacksMenu()
      {
      
        $html = "";

        foreach($this->love_callbacks as $t)
        {
         $html .= $t->getMenuItem();
        }
        
        return $html;
      }

}
?>