<?php

include_once("lovedoc2_init.php");

/**
* LOVEDOC v.2
* LOVE Documentation Generator.
* @author Anders Ruud
* @date 2007-11-18
**/

class LoveDoc2
{
  // The element stack.
  private $stack = array();
  
  // The completed document.
  private $document;

  private $verbose = false;
  
  // The HTML menu. Is generated once, 
  // then ramains static.
  public static $html_menu;
  
  // Static list of URL symbols.
  // This acts as the symbol table for
  // "see also" commands.
  private static $url_symbols = array();
  private static $url_symbols_count = array();

  public static function force_url_symbol($key, $value)
  {
    self::$url_symbols[$key] = $value;
  }

  // Gets the URL symbol for an identifier.
  // For methods: $key is the full name without parameters, 
  // for instance: love.audio:play, and $signature would then be
  // love.audio:play( loops ). For most other types $key and $signature is
  // the same thing.
  public static function add_url_symbol($key, $signature)
  {


    // Increment this symbol.
    if(!isset(self::$url_symbols_count[$key]))
      self::$url_symbols_count[$key] = 0;
    else
      self::$url_symbols_count[$key]++;

    // String representation of $url_symbols_count[$partial].
    $string_app = ( self::$url_symbols_count[$key] == 0 ) ? "" : self::$url_symbols_count[$key];

    // Alphanumeric only, plz.
    //$key_url = str_replace(array(".", ":", " "), "_", $key);
    $key_url = preg_replace('/[\WÃ]/', '_', $key);

    // Add the URL symbol.
    self::$url_symbols[$signature] = $key_url . $string_app;


    
    return self::$url_symbols[$signature];
  }
  
  // Use FULL signature!
  public static function get_url_symbol($key, $signature = "")
  {

    $signature = ($signature == "") ? $key : $signature;
    if(!isset(self::$url_symbols[$signature]))
      return self::add_url_symbol($key, $signature);
    else
      return self::$url_symbols[$signature];
  }
  
  public static function urlsym($signature)
  {
    if(!isset(self::$url_symbols[$signature]))
      return "";
    else
      return self::$url_symbols[$signature];
  }

  public static function write_html_sym($html, $title, $key, $signature = "")
  {
    $signature = ($signature == "") ? $key : $signature;
    $url = LoveDoc2::get_url_symbol($key, $signature) . ".html";
    self::write_html($url, $html, $title);
    return $url;
  }

  public static function write_html($file, $html, $title)
  {

    global $HTML_PRE;
    global $HTML_MIDDLE;
    global $HTML_CHAPTER_START;
    global $HTML_CHAPTER_MIDDLE;
    global $HTML_CHAPTER_END;
    global $HTML_POST;

    $out = $HTML_PRE . self::$html_menu . $HTML_MIDDLE .
           $HTML_CHAPTER_START . $title . $HTML_CHAPTER_MIDDLE . $html .
           $HTML_CHAPTER_END . $HTML_POST;

    file_put_contents("docs/".$file, $out);
  }

  public static function to_html($string)
  {
    // Replace brackets with html tags.
    $html = trim(str_replace(array("[", "]"), array("<", ">"),$string));

    // Replace text with symbols.
    foreach(self::$url_symbols as $signature => $url)
    {
      $signature = str_replace(array("(",")"),array("\(","\)"), $signature);

      $pattern = '/(\W)('.$signature.')([^\w^:])/';
      //' <a href="' . $url . '.html" class="symbol"/>' . $signature . "</a> "
      $replacement = '$1<a href="'.$url.'.html" class="symbol">$2</a>$3';

      $html = preg_replace($pattern, $replacement, $html);
    }

    return $html;
  }

  public function push($name, $attributes)
  {
    if($this->verbose) echo "push " . $name . "\n";

    switch($name)
    {
      case "document":
           array_push($this->stack, new Document($name, $attributes));
           break;
      case "section":
           array_push($this->stack, new Section($name, $attributes));
           break;
      case "type":
           array_push($this->stack, new Type($name, $attributes));
           break;
      case "device":
           array_push($this->stack, new Device($name, $attributes));
           break;
      case "function":
           array_push($this->stack, new Method($name, $attributes));
           break;
      case "param":
           array_push($this->stack, new Parameter($name, $attributes));
           break;
      case "separator":
           array_push($this->stack, new Separator($name, $attributes));
           break;
      case "see":
           array_push($this->stack, new See($name, $attributes));
           break;
      case "returns":
           array_push($this->stack, new Returns($name, $attributes));
           break;
      case "example":
           array_push($this->stack, new Example($name, $attributes));
           break;
      case "page":
           array_push($this->stack, new Page($name, $attributes));
           break;
	  case "constants":
	       array_push($this->stack, new Constants($name, $attributes));
		   break;
	  case "constant":
	       array_push($this->stack, new Constant($name, $attributes));
		   break;
    }
  }

  public function data($data)
  {
   // Add data to the current element.
   end($this->stack)->data($data);

  }

  public function pop($name)
  {
    if($this->verbose) echo "pop " . $name . "\n";
    
    // Verify that we are popping the correct item.
    if(!end($this->stack)->typeof($name))
      die("CRITICAL: PUSH/POP BALANCE FAIL: ".$name.".\n");
      
    // Pop it.
    $popped = array_pop($this->stack);
    
    if(sizeof($this->stack) > 0)
      end($this->stack)->add($popped);
    else
      $this->document = $popped;
      
    $popped->popped();

  }
  
  public function write()
  {
    
    // Get the menu HTML.
    self::$html_menu = '<div class="version">'.$this->document->atr("version").'</div>'  . $this->document->html_menu();

    $this->document->write();
  }
  


}

abstract class Element
{

  // Element name.
  protected $name;
  
  // Element attributes.
  protected $attributes;
  
  // Element character data.
  protected $data;
  
  // The children elements.
  protected $children = array();

  // The list of "see also" symbols.
  protected $see = array();

  // Constructor.
  public function __construct($name, $attributes)
  {
    $this->name = $name;
    $this->attributes = $attributes;
  }

  // Generates menu HTML.
  public function html_menu()
  {
    $tmp = "";
    foreach ($this->children as $c)
      $tmp .= $c->html_menu();
    return $tmp;
  }
  
  // Gets full HTML content.
  public function html()
  {
    $tmp = "";
    foreach ($this->children as $c)
      $tmp .= $c->html();
    return $tmp;
  }
  
  public function html_listitem()
  {
    return "";
  }

  // Writes related HTML document.
  public function write()
  {
    foreach ($this->children as $c)
      $c->write();
  }

  // Adds children to this element.
  public function add($element)
  {
    array_push($this->children, $element);
  }
  
  // Appends data to this element.
  public function data($data)
  {
    $this->data .= $data;
    //echo "data ".$this->name."\n";
  }

  public function typeof($name)
  {
    return (strcmp($this->name,$name) == 0);
  }
  
  public function haschildren($name)
  {
    $num = 0;
    foreach($this->children as $c) {
      if($c->typeof($name)) {
        $num++;
      }
    }
    return $num;
  }
  
  // Returns the value of an attribute, 
  // or an empty string if not set.
  public function atr($name)
  {
    if(!isset($this->attributes[$name]))
      return "";
    else
      return $this->attributes[$name];
  }
  
  // Adds an attribute.
  public function add_atr($key, $value)
  {
    $this->attributes[$key] = $value;
  }

  //  Returns the element signature for list use.
  public function signature()
  {
    return "";
  }
  
  // Called when this element is popped.
  public function popped()
  {
  }
}

class Document extends Element
{

  public function html()
  {
  }

  public function write()
  {
    // Create the doc folder.
    if(!is_dir("docs"))
      mkdir("docs");

    parent::write();
  }

}

class Section extends Element
{

  public function html_menu()
  {

    $sym = ($this->atr("refer") == "") ? LoveDoc2::get_url_symbol($this->atr("name")) : $this->atr("refer");

    $tmp = '<div class="horizontal"></div>';
    $tmp .= '<a href="'.$sym.'.html" class="element_title">'.$this->atr("name").'</a>';
    $tmp .= '<div class="horizontal"></div>';
    
    $tmp .= parent::html_menu();

    return $tmp;
  }

  public function write()
  {

         $html = '<div class="subchapter">';
         $html .= '<div class="title">';
         $html .= $this->atr("name");
         $html .= '</div>';
         $html .= '<div class="text">';
         $html .= LoveDoc2::to_html($this->data);
         $html .= '</div>';
  
  
         $html .= '<div class="section">';
         $html .= '<div class="title">'.$this->atr("has").'</div>';
         $html .= '<table cellspacing="0" class="functions">';

         foreach($this->children as $c)
             $html .= $c->html_listitem();

         $html .= '</table>';
         $html .= '</div>';
         $html .= '</div>';
         $html .= '</div>';

    // Create html.
    LoveDoc2::write_html_sym($html, "Summary", $this->atr("name"));

    parent::write();
  }
}

class Separator extends Element
{
  public function html_listitem()
  {
      return '<tr><td class="sep"></td><td class="sep"></td><tr>';
  }
}

class Type extends Element
{

  public function write()
  {
    // Create html.
    LoveDoc2::write_html_sym($this->html(), "Type", $this->atr("name"));

    parent::write();
  }

  public function html_listitem()
  {
    return '<tr><td class="signature"><a href="'.LoveDoc2::get_url_symbol($this->atr("name")).'.html" class="element">'.$this->atr("name").'</a></td><td class="brief">'.$this->atr("brief").'</td></tr>';
  }

  public function html_menu()
  {
    return '<a href="'.LoveDoc2::get_url_symbol($this->atr("name")).'.html" class="element">'.$this->atr("name").'</a>';
  }

  public function html()
  {
    // Generate HTML.

     $html = '<div class="subchapter">';

     $html .= '<div class="title">';
     $html .= $this->atr("name");
     $html .= '</div>';
     $html .= '<div class="text">';
     $html .= LoveDoc2::to_html($this->data);
     $html .= '</div>';


     $html .= '<div class="section">';
     $html .= '<div class="title">Functions</div>';
     $html .= '<table cellspacing="0" class="functions">';

     foreach($this->children as $c)
       if($c->typeof("function") || $c->typeof("separator"))
         $html .= $c->html_listitem();

     $html .= '</table>';
     $html .= '</div>';

     if($this->haschildren("see"))
     {

       $html .= '<div class="section">';
       $html .= '<div class="title">See also</div>';
       $html .= '<div class="text">';


     foreach($this->children as $c)
       if($c->typeof("see"))
         $html .= $c->html_listitem();

       $html .= '</div>';
       $html .= '</div>';
       
     }

      if($this->haschildren("example"))
     {

       $html .= '<div class="section">';
       $html .= '<div class="title">Examples</div>';
       $html .= '<div class="text">';

     $num = 1;
     foreach($this->children as $c) {
       if($c->typeof("example")) {
         $html .= "Example $num: ";
         $html .= $c->html();
         $num++;
       }
     }

       $html .= '</div>';
       $html .= '</div>';
     }
	 
	 $html .= '</div>';
     
     return $html;
  }

  public function add($element)
  {
    // Add a parent attribute.
    $element->add_atr("parent", $this->atr("name"));
    
    parent::add($element);
  }
  
  public function popped()
  {
    // Add symbol.
    LoveDoc2::add_url_symbol($this->atr("name"), $this->atr("name"));
  }
}

class Method extends Element
{
  public function write()
  {

    $parent = $this->atr("parent") == "" ? "" : $this->atr("parent").":";
    $partial = $parent . $this->atr("name");
    $full = $parent . $this->signature();
    


     $html = '<div class="subchapter">';
  
     $html .= '<div class="title">';
     $html .= $full;
     $html .= '</div>';
     $html .= '<div class="text">';
     $html .= LoveDoc2::to_html($this->data);
     $html .= '</div>';
  
  
     $html .= '<div class="section">';
     $html .= '<div class="title">Usage</div>';
     $html .= '<code>';
  
     $html .= $full;
  
     $html .= '</code>';
     $html .= '</div>';
     

     $html .= '<div class="section">';
     $html .= '<div class="arguments">';
     $html .= '<div class="title">Arguments</div>';
  
     if(!$this->haschildren("param"))
       $html .= '<div class="entry">None</div>';
  
     foreach($this->children as $c)
       if($c->typeof("param") || $c->typeof("separator"))
         $html .= $c->html_listitem();
  
     $html .= '</div>';
     $html .= '</div>';
  
     $html .= '<div class="section">';
     $html .= '<div class="arguments">';
     $html .= '<div class="title">Returns</div>';
  
     if(!$this->haschildren("returns"))
       $html .= '<div class="entry">Nothing</div>';

     foreach($this->children as $c)
       if($c->typeof("returns"))
         $html .= $c->html_listitem();
  
     $html .= '</div>';
     $html .= '</div>';
     
  
     if($this->haschildren("see"))
     {

       $html .= '<div class="section">';
       $html .= '<div class="title">See also</div>';
       $html .= '<div class="text">';


     foreach($this->children as $c)
       if($c->typeof("see"))
         $html .= $c->html_listitem();

       $html .= '</div>';
       $html .= '</div>';
       
     }

      if($this->haschildren("example"))
     {

       $html .= '<div class="section">';
       $html .= '<div class="title">Examples</div>';
       $html .= '<div class="text">';

     $num = 1;
     foreach($this->children as $c) {
       if($c->typeof("example")) {
         $html .= "Example $num: ";
         $html .= $c->html();
         $num++;
       }
     }

       $html .= '</div>';
       $html .= '</div>';

     $html .= '</div>';
     
     }


     $html .= '</div>';
  




    // Create html.
    LoveDoc2::write_html_sym($html, "Function", $partial, $full);

  }

  public function html_listitem()
  {

    $parent = $this->atr("parent") == "" ? "" : $this->atr("parent").":";
    $partial = $parent . $this->atr("name");
    $full = $parent . $this->signature();
    $url = LoveDoc2::get_url_symbol($partial, $full);

    return '<tr><td class="signature"><a href="'.$url.'.html">' .
           $this->signature().'</a></td><td class="brief">'.$this->atr("brief").'</td></tr>';
  }

  public function html_menu()
  {
    
    $parent = $this->atr("parent") == "" ? "" : $this->atr("parent").":";
    $partial = $parent . $this->atr("name");
    $full = $parent . $this->signature();
    $url = LoveDoc2::get_url_symbol($partial, $full);

    return '<a href="'.$url.'.html" class="element">'.$partial.'</a>';
  }

  public function html()
  {
  }

  public function signature()
  {
    $s = $this->atr("name") . "( ";

    $num = 0;

    foreach($this->children as $p) {
     if($p->typeof("param")) {
      $s .= $p->atr("name") . ", ";
      $num++;
     }
    }

    if($num > 0) 
    {
      $s = substr($s,0, strlen($s) - 2);
      $s .= " )";
    }else
    {
      $s .= ")";
    }

    return $s;
  }

  public function popped()
  {
    
    $parent = $this->atr("parent") == "" ? "" : $this->atr("parent").":";
    $partial = $parent . $this->atr("name");
    $full = $parent . $this->signature();

    // Add symbol.
    LoveDoc2::add_url_symbol($partial, $full);
  }
}

class Parameter extends Element
{

  public function html_listitem()
  {
     $html = '<div class="entry"><span class="name">'.$this->atr("name").'</span>'.LoveDoc2::to_html($this->atr("brief")).'</div>';
     return $html;
  }

  public function html_menu()
  {
  }

  public function html()
  {
  }
}

class Returns extends Element
{
  public function html_listitem()
  {
	$sym = LoveDoc2::urlsym($this->atr("type"));
	if($sym == "")
	  $html = '<div class="entry"><span class="name">'.$this->atr("type").'</span>'.$this->atr("brief").'</div>';
	else
	  $html = '<div class="entry"><span class="name"><a href="'.$sym.'.html" class="symbol">'.$this->atr("type").'</a></span>'.$this->atr("brief").'</div>';
    return $html;
  }
}

class See extends Element
{
  public function html_listitem()
  {
    $sym = LoveDoc2::urlsym($this->atr("name"));

    if($sym == "")
      return '<a href="javascript:void(0)" style="color: red;">(Error: symbol "'.$this->atr("name").'" does not exist.)</a> &nbsp;';
    else
      return '<a href="'.$sym.'.html" class="symbol">'.$this->atr("name").'</a> &nbsp;';
  }
}

class Example extends Element
{
  public function html()
  {
    return " " . $this->atr("name") . " " . toCode($this->data);
  }
}

class Page extends Element
{
  public function html_listitem()
  {
    $sym = ($this->atr("sym") == "") ? $this->atr("name") : $this->atr("sym");
    return '<tr><td class="signature"><a href="'.LoveDoc2::get_url_symbol($sym, $this->atr("name")).'.html" class="element">'.$this->atr("name").'</a></td><td class="brief">'.$this->atr("brief").'</td></tr>';
  }

  public function html_menu()
  {
    $sym = ($this->atr("sym") == "") ? $this->atr("name") : $this->atr("sym");
    return '<a href="'.LoveDoc2::get_url_symbol($sym, $this->atr("name")).'.html" class="element">'.$this->atr("name").'</a>';
  }


 public function write()
 { 
   $html = LoveDoc2::to_html($this->data);
   $sym = ($this->atr("sym") == "") ? $this->atr("name") : $this->atr("sym");
   LoveDoc2::write_html_sym($html, $this->atr("name"), $this->atr("name"));
 }
}

class Device extends Type
{
  public function write()
  {
    // Create html.
    LoveDoc2::write_html_sym($this->html(), "Device", $this->atr("name"));

    foreach($this->children as $c)
      $c->write();
  }
}

class Constants extends Page
{

  public function html()
  {
    // Generate HTML.

     $html = '<div class="subchapter">';

     $html .= '<div class="title">';
     $html .= $this->atr("name");
     $html .= '</div>';
     $html .= '<div class="text">';
     $html .= LoveDoc2::to_html($this->data);
     $html .= '</div>';


     $html .= '<div class="section">';
     $html .= '<div class="title">'.$this->atr("has").'</div>';
     $html .= '<table cellspacing="0" class="functions">';

     foreach($this->children as $c) 
       if($c->typeof("constant") || $c->typeof("separator")) 
         $html .= $c->html_listitem();

     $html .= '</table>';
     $html .= '</div>';

     if($this->haschildren("see"))
     {

       $html .= '<div class="section">';
       $html .= '<div class="title">See also</div>';
       $html .= '<div class="text">';


     foreach($this->children as $c)
       if($c->typeof("see"))
         $html .= $c->html_listitem();

       $html .= '</div>';
       $html .= '</div>';
       
     }

      if($this->haschildren("example"))
     {

       $html .= '<div class="section">';
       $html .= '<div class="title">Examples</div>';
       $html .= '<div class="text">';

     $num = 1;
     foreach($this->children as $c) {
       if($c->typeof("example")) {
         $html .= "Example $num: ";
         $html .= $c->html();
         $num++;
       }
     }

       $html .= '</div>';
       $html .= '</div>';
     }
	 
	 $html .= '</div>';
     
     return $html;
  }


 public function write()
 { 
   $html = $this->html();
   $sym = ($this->atr("sym") == "") ? $this->atr("name") : $this->atr("sym");
   LoveDoc2::write_html_sym($html, $this->atr("name"), $this->atr("name"));
 } 
}

class Constant extends Element
{

  public function html_listitem()
  {
     return '<tr><td class="signature">' .$this->atr("name").'</a></td><td class="type">['.($this->atr("type") == "" ? "integer" : $this->atr("type")).']</td><td class="brief">' .$this->atr("brief").'</td></tr>';
  }

  public function html_menu()
  {
  }

  public function html()
  {
  }
}

/**
* Globals methods and actual parsing happens here.
**/

$love_doc = new LoveDoc2();

function lovedoc($file)
{
  // Import the global LoveDoc2 object.
  global $love_doc;

  // Create XML parser, and start parse.
  $xml_parser = xml_parser_create();
  xml_set_element_handler($xml_parser, "xml_start", "xml_end");
  xml_set_character_data_handler($xml_parser, "xml_data");
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
  
  
  // Ouput documentation.
  $love_doc->write();

}

function xml_start($parser, $name, $attributes)
{
  global $love_doc;
  $love_doc->push($name, $attributes);
}

function xml_end($parser, $name)
{
  global $love_doc;
  $love_doc->pop($name);
}

function xml_data($parser, $data)
{
  global $love_doc;
  $love_doc->data($data);
}

?>