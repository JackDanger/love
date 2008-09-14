-- Hackulent (as usual), but it at least it works.


syx = {}

syx.modes = {
	normal = 1, 
	single_string = 2, 
	double_string = 3, 
	multi_string = 4, 
	number = 5, 
	comment = 6,
	multi_comment = 7,
}

syx.mode = syx.modes.normal

syx.types = {
	char = 1, -- Accepted in variable names.
	digit = 2,
}

syx.buffer = {}
syx.final = ""

function syx.reset()
	syx.buffer = {}
	syx.final = ""
end

function syx.write(...)
	for i,v in ipairs(arg) do
		table.insert(syx.buffer, v)
	end
end

function syx.raw(str)
	syx.final = syx.final .. str
end

function syx.out(file, data)
	local f = io.open(file, "w")
	f:write(data)
	io.close(f)
end

function syx.concat(f)
	local str = table.concat(syx.buffer, "")
	str = "<ol><li>" .. str
	str = string.gsub(str, "\r", "")
	str = string.gsub(str, "\n", "&nbsp;</li><li>")
	str = string.gsub(str, "\t", "&nbsp;&nbsp;&nbsp;")
	str = str .. "&nbsp;</li></ol>"
	return str
end

-- Build some lookup tables.

function syx.ltab(str)
	local t = {}
	for v in string.gmatch(str, ".") do
		t[v] = true
	end
	return t
end

local numbers_str = "1234567890"
local chars_str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
local allchars_str = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890"

syx.numbers = syx.ltab(numbers_str)
syx.allchars = syx.ltab(allchars_str)
syx.chars = syx.ltab(chars_str)

-- Amazing keyword table:
syx.keywords = {
	["and"] = true,
	["break"] = true,
	["do"] = true,
	["else"] = true,
	["elseif"] = true,
	["end"] = true,
	["for"] = true,
	["function"] = true,
	["if"] = true,
	["local"] = true,
	["nil"] = true,
	["not"] = true,
	["or"] = true,
	["repeat"] = true,
	["return"] = true,
	["then"] = true,
	["until"] = true,
	["while"] = true,
	["true"] = true,
	["false"] = true,
}

syx.operators_single = {
	["+"] = true,
	["-"] = true,
	["*"] = true,
	["/"] = true,
	["^"] = true,
	["%"] = true,
	["<"] = true,
	[">"] = true,
	["#"] = true,
	["="] = true,
}

syx.operators_double = {
	["."] = { ["."] = true },
	["<"] = { ["="] = true },
	[">"] = { ["="] = true },
	["="] = { ["="] = true },
	["~"] = { ["="] = true },
}

syx.fieldsep = {
	[","] = true,
	[";"] = true,
}

syx.max_keyword = 8

function syx.explode(text)
	local t = {}
	for w in string.gmatch(text, ".") do
		table.insert(t, w)
	end
	return t
end

function syx.cstring(t, i)

	local mark = nil

	if t[i] == "\"" and (syx.mode == syx.modes.normal or syx.mode == syx.modes.double_string) then
		mark = syx.modes.double_string
	elseif t[i] == "'" and (syx.mode == syx.modes.normal or syx.mode == syx.modes.single_string) then
		mark = syx.modes.single_string
	end

	-- Check for escape char.
	if t[i-1] == "\\" then mark = nil end

	if mark and syx.mode == syx.modes.normal then
		syx.mode = mark
		syx.write('<span class="string">', t[i])
		return i+1
	elseif mark and syx.mode ~= syx.modes.normal then
		syx.mode = syx.modes.normal
		syx.write(t[i], "</span>")
		return i+1
	end
end

function syx.cmultistring(t, i)
	if t[i-1] ~= "-" and t[i] == "[" and t[i+1] == "[" and syx.mode == syx.modes.normal then
		syx.mode = syx.modes.multi_string
		syx.write('<span class="string">', t[i])
		return i+1
	elseif t[i-2] ~= "-" and t[i-1] == "]" and t[i] == "]" and syx.mode == syx.modes.multi_string then
		syx.mode = syx.modes.normal
		syx.write(t[i], "</span>")
		return i+1
	end
end


function syx.cnumber(t, i)

	-- A dot followed by a number is accepted as a decimal separator.
	--local mark =  or (t[i] == "." and numbers[t[i+1]])

	if syx.numbers[t[i]] and not syx.allchars[t[i-1]] and not syx.allchars[t[i+1]] and syx.mode == syx.modes.normal then
		syx.write('<span class="number">', t[i], "</span>")
		return i+1
	elseif (syx.numbers[t[i]] and not syx.allchars[t[i-1]]) and syx.mode == syx.modes.normal then
		syx.mode = syx.modes.number
		syx.write('<span class="number">', t[i])
		return i+1
	elseif (syx.numbers[t[i]] or t[i] == ".") and (not syx.numbers[t[i+1]] and t[i+1] ~= ".") and syx.mode == syx.modes.number then
		syx.mode = syx.modes.normal
		syx.write(t[i], "</span>")
		return i+1
	end

end

function syx.ckeyword(t, i)

	-- Normal mode only.
	if syx.mode ~= syx.modes.normal then return end

	if syx.chars[t[i]] and not syx.allchars[t[i-1]] then

		local str_t = { }

		-- Read until a non-var letter is found.
		local idx = i

		while syx.allchars[t[idx]] and (idx-i < syx.max_keyword) do
			table.insert(str_t,t[idx])
			idx = idx + 1
		end

		local str = table.concat(str_t, "")
		
		if syx.keywords[str] then
			syx.write('<span class="keyword">', str ,"</span>")
			return i+#str
		end

	end

end

function syx.ccomment(t, i)

	if t[i] == "-" and t[i+1] == "-" and (t[i+2] ~= "[" and t[i+2] ~= "]") and syx.mode == syx.modes.normal then
		syx.mode = syx.modes.comment
		syx.write('<span class="comment">', t[i])
		return i+1
	end
	
	if t[i] == "\n" and syx.mode == syx.modes.comment then
		syx.mode = syx.modes.normal
		syx.write("</span>", t[i])
		return i+1
	end

end

function syx.cmulticomment(t, i)
	if t[i-1] ~= "-" and t[i] == "-" and t[i+1] == "-" and t[i+2] == "[" and t[i+3] == "[" and syx.mode == syx.modes.normal then
		syx.mode = syx.modes.multi_comment
		syx.write('<span class="comment">', t[i])
		return i+1
	elseif t[i-4] ~= "-" and t[i-3] == "-" and t[i-2] == "-" and t[i-1] == "]" and t[i] == "]" and syx.mode == syx.modes.multi_comment then
		syx.mode = syx.modes.normal
		syx.write(t[i], "</span>")
		return i+1
	end
end

function syx.coperators(t, i)

	if syx.mode ~= syx.modes.normal then return end
	
	-- Check for double.
	do
		local o = syx.operators_double[t[i]]
		if o then
			if o[t[i+1]] then
				syx.write('<span class="operator">', t[i], t[i+1], "</span>")
				return i+2
			end
		end
	end
	
	-- Single.
	local o = syx.operators_single[t[i]]
	if o then
		syx.write('<span class="operator">', t[i], "</span>")
		return i+1
	end

end

function syx.cspace(t,i)
	if t[i] == " " then
		syx.write("&nbsp;")
		return i+1
	end
end

function syx.cmark(t, i)
	local pos = nil
	if not pos then pos = syx.cstring(t, i) end
	if not pos then pos = syx.cnumber(t, i) end
	if not pos then pos = syx.ckeyword(t, i) end
	if not pos then pos = syx.ccomment(t, i) end
	if not pos then pos = syx.cmulticomment(t, i) end
	if not pos then pos = syx.cmultistring(t, i) end
	if not pos then pos = syx.coperators(t, i) end
	if not pos then pos = syx.cspace(t, i) end
	if not pos then syx.write(t[i]); pos = i+1; end
	return pos
end

function syx.dostring(s)
	local t = syx.explode(s)
	local pos = 1
	syx.reset()
	syx.raw('<span class="syx">')
	while pos < #t do
		pos = syx.cmark(t, pos)
	end
	syx.raw(syx.concat())
	syx.raw('</span>')
	return syx.final
end


