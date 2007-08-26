<?php

class LoveFunctionParameter
{
      public $name = "";
      public $description = "";

      function __construct($name, $description) {
          $this->name = $name;
          $this->description = $description;
      }

      function getFull()
      {
               $html = '<div class="entry"><span class="name">'.$this->name.'</span>'.$this->description.'</div>';
               return $html;

      }


}

?>