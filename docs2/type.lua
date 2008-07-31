

----------------------------------------------------
-- Parser
----------------------------------------------------
function lovedoc.parser.type(t, p)
	local o = lovedoc.newtypetag()
	o._name = t.attr.name or "notype"
	o._plural = t.attr.plural or o._name .. "s"
	o._parent = p:name()
	o._brief = t.attr.brief or "(No description.)"
	o._type = true
        o.example = {}
	o.func = {}
        o.see = {}
	lovedoc.insert(t, p, o)
end

----------------------------------------------------
-- Writer
----------------------------------------------------
function lovedoc.docwriter.type(m)
	lovedoc.docwrite(m)
	local b = lovedoc.newbuffer()
	b:header()
	b:menu(m._parent)
        
	page_begin(b, "Type", m:name(), m:text())	
        func_section(b, m.func)       
        example_section(b, m.example)		
	page_end(b)
        
	b:tofile(m:url())
end
