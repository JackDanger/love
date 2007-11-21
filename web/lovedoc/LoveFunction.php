<?php

include_once("init.php");

include("LoveFunctionParameter.php");

class LoveFunction
{
      public $parent = "";
      public $parent_type = "t";
      public $name = "";
      public $description = "";
      public $brief = "";
      public $love_parameters = array();
      public $returns;
      public $examples = array();
      public $see_also = array();

      function __construct($name, $brief, $description = "", $parent = "", $returns = "") {
          $this->name = $name;
          $this->brief = $brief;
          $this->description = $description;
          $this->parent = $parent;
          $this->returns = $returns == "" ? new LoveFunctionParameter("Nothing", "") : $returns;
      }
      
      function add($name, $brief)
      {
       $this->love_parameters[] = new LoveFunctionParameter($name, $brief);
      }

      function getFull()
      {
               $html = '<div class="subchapter">';

               $html .= '<div class="title">';
               $html .= $this->getFullSignature();
               $html .= '</div>';
               $html .= '<div class="text">';
               $html .= nl2br(trim($this->description));
               $html .= '</div>';


               $html .= '<div class="section">';
               $html .= '<div class="title">Usage</div>';
               $html .= '<code>';

               $html .= $this->getFullSignature();

               $html .= '</code>';
               $html .= '</div>';
               

               $html .= '<div class="section">';
               $html .= '<div class="arguments">';
               $html .= '<div class="title">Arguments</div>';

                     if(sizeof($this->love_parameters) == 0)
                        $html .= '<div class="entry">None</div>';

                     foreach($this->love_parameters as $p)
                     {
                      $html .= $p->getFull();
                     }

               $html .= '</div>';
               $html .= '</div>';

               $html .= '<div class="section">';
               $html .= '<div class="arguments">';
               $html .= '<div class="title">Returns</div>';

               $html .=  $this->returns->getFull();

               $html .= '</div>';
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
      
      function getListItem()
      {
        return '<tr><td class="signature"><a href="'.$this->getUrl().'">'.$this->getSignature().'</a></td><td class="brief">'.$this->brief.'</td></tr>';
      }
      
      function getMenuItem()
      {
       return '<a href="'.$this->name.'.html" class="element">'.$this->name.'</a>';
      }
      
      function getSignature()
      {
               $html = $this->name . "( ";

              foreach($this->love_parameters as $p)
              {
                $html .= $p->name . ", ";
              }
              
              if(sizeof($this->love_parameters))
              $html = substr($html,0, strlen($html) - 2);


              $html .= " )";

              return $html;
      }
      
      function getFullSignature()
      {
              return  '<a href="'.$this->getUrl().'">' . $this->parent . "</a>" . (strlen($this->parent) == 0 ? "" : ":") . "" . $this->getSignature();
      }

      function getCompactSignature()
      {
               $html = $this->name;

              foreach($this->love_parameters as $p)
              {
                $html .= $p->name;
              }

              return $html;
      }
      
      function getUrl()
      {
               return 'function'.$this->parent_type.$this->parent . $this->getCompactSignature() . '.html';
      }

}

?>