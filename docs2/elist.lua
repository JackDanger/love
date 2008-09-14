local t = {}

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

		b:push("tr")
	    b:push("td", "name"); b:write('<a href="../examples/'..v..'">'..v..'</a>'); b:pop()
	    b:push("td", "desc"); b:write(title); b:pop()
	    b:pop()
	end

	list_section_end(b)
	page_end(b)
end

return t