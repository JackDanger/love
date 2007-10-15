
var saved_font_color = "#000000";
var saved_bg_color = "#ffffff";

function chft(t, clr)
{
 t.style.color = clr;
}

function chbg(t, clr)
{
 t.style.backgroundColor = clr;
}

function overMenu(t, bg)
{
    saved_font_color = t.style.color;
    saved_bg_color =  t.style.backgroundColor;
    chft(t, "#ffffff");
    chbg(t, bg);
}

function outMenu(t)
{
    chft(t, saved_font_color);
    chbg(t, saved_bg_color);
}

function toggleVisible(id)
{
  var e = document.getElementById(id);
  if(e.style.display == "block")
    e.style.display = "none";
  else
    e.style.display = "block";
}

/** images **/

function viewImage(filepath, width, height)
{
	if(navigator.appName == "Microsoft Internet Explorer")
	{
		window.open(filepath,'mywin','left=20,top=20,width=' + width + ',height=' + (height+20) + ',toolbar=0,resizable=0,scrollbars=0');
	}
	e = document.getElementById("imageview");
	//e.innerHTML = "<img src=\"" + filepath + "\" alt=\"image\" />";
	e.innerHTML = '<br /><br />Loading...';
	var temp = Math.floor( (window.innerHeight / 2) - (height / 2) ) - 50;
	if (temp < 5)
		temp = 5;
	temp = temp + document.documentElement.scrollTop;
	e.style.top = temp + "px";
	e.style.left = Math.floor( (window.innerWidth / 2) - (width / 2) ) + "px";
	e.style.width = width + "px";
	e.style.height = (height + 30) + "px";
	e.style.display = "block";
	new Ajax.Updater("imageview", "php/view_image.php?img=" + filepath, { method: 'get' });
}

function closeImage()
{
	document.getElementById("imageview").style.display = "none";
}


/** Screenshot **/

function ssOver(t)
{
  t.className = "image_info_active";
}

function ssOut(t)
{
  t.className = "image_info_inactive";
}