
function lovedoc.parser.callback(t, p)
	local o = lovedoc.newoverloadtag()
	o._name = t.attr.name or "noname"
	o._brief = t.attr.brief or p._brief or "(No description.)"
	o._text = ""
	o.param = {}
        o.see = {}
        o.example = {}
	lovedoc.insert(t, p, o)	
end

function lovedoc.docwriter.callback(t)

	local b = lovedoc.newbuffer()
	b:header()
	b:menu(t:name())
	
        page_begin(b, "Callback", t:signature(), t:text())
		  synopsis_callback_section(b, t:signature(), {})
        param_section(b, t.param)
        see_section(b, t.see)
		  ret_section(b, {})
		  
        example_section(b, t.example)
        page_end(b)
        
	b:tofile(t:url())
end
