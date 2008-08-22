
function lovedoc.parser.overload(t, p)
	local o = lovedoc.newoverloadtag()
	o._name = p:name()
	o._brief = t.attr.brief or p._brief or "(No description.)"
	o._parent = p._parent or "FAILFAILFAIL"
	o._text = ""
	if p._type then o._separator = ":" else o._separator = "." end
	o.param = {}
	o.ret = {}
	o._space = t.attr.space
    o.see = {}
    o.example = {}
	lovedoc.insert(t, p, o)	
end

function lovedoc.docwriter.overload(t)

	local b = lovedoc.newbuffer()
	b:header()
	b:menu(t._parent or "")
	
	 page_begin(b, "Function", t:signature(), t:text())
	 synopsis_section(b, t:signature(), t.ret)
	 param_section(b, t.param)
	 ret_section(b, t.ret)
	 see_section(b, t.see)
	 example_section(b, t.example)
	 page_end(b)
	 
	b:tofile(t:url())
end
