local t = {}

function t.example_html(filename)
	local b = lovedoc.newbuffer()
	b:header()
	b:menu("Example List")

	local file = io.open("examples/"..filename)
	local s, e, id, title
	local contents = ""

	if file then

		s, e, id = string.find(filename, "(%d%d%d%d)")
		contents = file:read("*a")
		s, e, title = string.find(contents, "%-%- Example: (.-)\n")
		io.close(file)
	end

	title = title or "Untitled"

	page_begin(b, "Example", title, "")

	b:div("content")

                b:div("example")
                b:div("title")
                b:write("Example " .. id .. ": " .. title)
                b:pop()
                b:div("code")
                b:write(syx.dostring(contents))
                b:pop()
                b:pop()

	b:pop()
	page_end(b)
	b:tofile("e"..id..".html")
end

function t.write(b, o)

	print("Generating example list ...")

	-- Generate a file with list of all examples.
	os.execute("dir examples > elist.txt")

	local file = io.open("elist.txt")
	
	local elist = {}

	if file then
		local contents = file:read("*a")
		io.close(file)
		for e in string.gmatch(contents, "e%d%d%d%d%.lua") do
			table.insert(elist, e)
		end
	end

	page_begin(b, "Miscellaneous", o:name(), o:text() .. "<br /><br />Number of examples: " .. #elist .. ".")
	list_section_begin(b, "Examples")

	for i,v in ipairs(elist) do
	
		-- Generate example html.
		t.example_html(v)

		local title

		do
			local file = io.open("examples/"..v)
			if file then
				local s,e
			    s, e, title = string.find(file:read("*l"), "%-%- Example: (.*)")
				io.close(file)
			end
		end

		title = title or "Untitled"

		local s, e, id = string.find(v, "(e%d%d%d%d)")

		b:push("tr")
	    b:push("td", "name"); b:write('<a href="'..id..'.html">'..id..'</a>'); b:pop()
	    b:push("td", "desc"); b:write(title); b:pop()
	    b:pop()
	end

	list_section_end(b)
	page_end(b)
end

return t