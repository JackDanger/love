
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




/** Screenshot **/

function ssOver(t)
{
  t.className = "image_info_active";
}

function ssOut(t)
{
  t.className = "image_info_inactive";
}