function lovedoc.parser.page(t, p)
	local o = lovedoc.newtag()
	o._name = t.attr.name or "No Name"
	o._text = ""
	if t.attr.file then
		o.url = function () return t.attr.file end
	end
	o.section = {}
	lovedoc.insert(t, p, o)
end

function lovedoc.docwriter.page(m)
	local b = lovedoc.newbuffer()
	b:header()
	b:menu(m:name())

   page_begin_lite(b, m:name())
   section_section(b, m.section)       
   page_end_lite(b)
	
	b:tofile(m:url())
end
