<?php

include_once("init.php");

include("LoveFunction.php");

class LoveType
{
      public $name = "";
      public $description = "";
      public $brief = "";
      public $love_functions = array();
      public $examples = array();
      public $see_also = array();
      public $type = "type";

      function __construct($name, $brief, $description = "") {
          $this->name = $name;
          $this->description = $description;
          $this->brief = $brief;
      }

      function add($f)
      {
       $this->love_functions[] = $f;
      }

      function getMenuItem()
      {
       return '<a href="'.$this->type.$this->name.'.html" class="element">'.$this->name.'</a>';
      }

      function getFull()
      {
      
               global $geshi;

               $html = '<div class="subchapter">';

               $html .= '<div class="title">';
               $html .= $this->name;
               $html .= '</div>';
               $html .= '<div class="text">';
               $html .= str_replace(array("[", "]"), array("<", ">"),$this->description);
               $html .= '</div>';


               $html .= '<div class="section">';
               $html .= '<div class="title">Functions</div>';
               $html .= '<table cellspacing="0" class="functions">';

                     foreach($this->love_functions as $k=>$f)
                     {
                      if($f === false)
                            $html .= '<tr><td class="sep"></td><td class="sep"></td><tr>';
                      else
                          $html .= $f->getListItem();

                     }

               $html .= '</table>';
               $html .= '</div>';

               if(sizeof($this->see_also))
               {
                 $html .= '<div class="section">';
                 $html .= '<div class="title">See also</div>';
                 $html .= '<div class="text">';
                       foreach($this->see_also as $k=>$v)
                       {
                           $html .= '<a href="'.$v.'.html">' . $k . "</a> &nbsp; ";
                       }
                 $html .= '</div>';
                 $html .= '</div>';
               }

               if(sizeof($this->examples))
               {

                 $html .= '<div class="section">';
                 $html .= '<div class="title">Examples</div>';
                 $html .= '<div class="text">';
                 
                 
                 $num = 1;

                       foreach($this->examples as $k=>$v)
                       {
                           $html .= "Example $num: $k<br />" . toCode($v);
                           $num++;
                       }
                 $html .= '</div>';
                 $html .= '</div>';
               
               }



               $html .= '</div>';


               return $html;

      }
}

?>