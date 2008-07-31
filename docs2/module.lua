

function lovedoc.parser.module(t, p)
	local o = lovedoc.newtag()
	o._name = t.attr.name or "noname"
	o._text = ""
	o.func = {}
	o.type = {}
        o.example = {}
        o.see = {}
	lovedoc.insert(t, p, o)
end

function lovedoc.docwriter.module(m)
	lovedoc.docwrite(m)
	local b = lovedoc.newbuffer()
	b:header()
	b:menu(m:name())
        
	page_begin(b, "Module", m:name(), m:text())	
        type_section(b, m.type)
        func_section(b, m.func)       
        example_section(b, m.example)		
	page_end(b)
        
	b:tofile(m:url())
end