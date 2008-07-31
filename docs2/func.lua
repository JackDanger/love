
function lovedoc.parser.func(t, p)
	
	local o = lovedoc.newtag()
	o._name = t.attr.name or "nofunc"
	o._brief = t.attr.brief or "(No description.)"
        o._separator = t.attr.separator
	o._parent = p:name()
	o._text = ""
	o._type = p._type
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
	
	b:div("page")
		b:div("title")
			b:write("Function")
		b:pop()
		b:div("description")
			b:div("title")
				b:write(t:fullname())
			b:pop()
			b:div("text")
				b:write(t:text())
			b:pop()
		b:pop()
		
		b:div("section")
			b:div("title")
				b:write("Variants")
			b:pop()
			b:div("content")
				b:push("table", "data")
					for oi,o in ipairs(t.overload) do
						b:push("tr")
							b:push("td", "name")
								b:write("<a href=\""..o:url().."\">"..o:shortsignature() .."</a>")
							b:pop()
							b:push("td", "desc")
								b:write(o._brief)
							b:pop()
						b:pop()
					end
				b:pop()
			b:pop()
		b:pop()
				
	b:pop()	
	b:tofile(t:url())
end