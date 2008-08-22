
function lovedoc.parser.func(t, p)
	
	local o = lovedoc.newtag()
	o._name = t.attr.name or "nofunc"
	o._brief = t.attr.brief or "(No description.)"
   if p._type then o._separator = ":" else o._separator = "." end
	o._parent = p:name()
	o._text = ""
	o._type = p._type
	o._space = t.attr.space
	o.overload = {}
	o.param = {}
	o.ret = {}
   o.see = {}
	lovedoc.insert(t, p, o)
end

function lovedoc.docwriter.func(t)

	if #t.overload <= 0 then
		return lovedoc.docwriter.overload(t)
	end

	lovedoc.docwrite(t)

	local b = lovedoc.newbuffer()
	b:header()
	b:menu(t._parent or "")
	
	page_begin(b, "Function", t:fullname(), t:text())
	list_section_begin(b, "Variants")
	for oi,o in ipairs(t.overload) do
		list_item(b, '<a href="'..o:url()..'">'..o:shortsignature()..'</a>', o._brief)
	end
	list_section_end(b)
	page_end(b)
	
	b:tofile(t:url())
end