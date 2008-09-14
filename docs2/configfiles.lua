local t = {}

function t.write(b, o)
	page_begin(b, "Miscellaneous", o:name(), o:text())
	item_section(b, o.item, o._title)
	example_section(b, o.example)
	page_end(b)
end

return t