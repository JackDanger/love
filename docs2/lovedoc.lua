--
-- LOVEDOC III
--
-- Warning: this is extremely hacky and
-- could've been done better.
--
-- So sue me.
--

require "lxp.lom"

dofile("exgen.lua")

function table_print (tt, indent, done)
  done = done or {}
  indent = indent or 0
  if type(tt) == "table" then
    for key, value in pairs (tt) do
      io.write(string.rep (" ", indent)) -- indent it
      if type (value) == "table" and not done [value] then
        done [value] = true
        io.write(string.format("[%s] => table\n", tostring (key)));
        io.write(string.rep (" ", indent+4)) -- indent it
        io.write("(\n");
        table_print (value, indent + 7, done)
        io.write(string.rep (" ", indent+4)) -- indent it
        io.write(")\n");
      else
        io.write(string.format("[%s] => %s\n",
            tostring (key), tostring(value)))
      end
    end
  else
    io.write(tt .. "\n")
  end
end

function trim (s)
	return (string.gsub(s, "^%s*(.-)%s*$", "%1"))
end


lovedoc = {}

lovedoc.data = {
	page = {},
	module = {},
        callback = {},
	misc = {},
        ghost = {},
}

lovedoc.menudef =
{
	{ t = lovedoc.data.page,	name = "Documentation"},
	{ t = lovedoc.data.module,      name = "Modules"},
        { t = lovedoc.data.callback,    name = "Callbacks"},
	{ t = lovedoc.data.misc, 	name = "Miscellaneous"},
}

lovedoc.symdef =
{
	"module",
	
	"type",
	
	"func",
	"overload",
        "callback",
        "ghost",
	
	"page",
	"misc",
}

lovedoc.url = { data = {}, count = {}, sorted = {}, gsub = {} }
lovedoc.parser = {}
lovedoc.docwriter = {}
lovedoc.menuwriter = {}
lovedoc.sig = {}
lovedoc.fullsig = {}
lovedoc.html = {}
lovedoc.html.buffer = {}
lovedoc.html.header = [[
<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
<head>
    <title>L&Ouml;VE Documentation 0.4.0</title>
    <link rel="stylesheet" type="text/css" href="css/default.css" />
    <meta http-equiv="content-type" content="text/html; charset=utf-8" />
</head>
<body>
    <table class="master" cellspacing="0">
        <tr>
            <td class="cell bar">
			<div class="header">
			</div>
			<div class="content">
<!----------------- GENERATED MENU BEGIN ----------------->
]]

lovedoc.html.middle = [[
<!----------------- GENERATED MENU END ----------------->
			</div>
		</td>
		<td class="cell">
<!----------------- GENERATED CONTENT BEGIN ----------------->
]]
		

lovedoc.html.footer = [[
<!----------------- GENERATED CONTENT  END ----------------->
		</td>
        </tr>
    </table>
</body>
</html>

]]

----------------------------------------------------
-- lovedoc
----------------------------------------------------

function lovedoc.strclean(s)
	local t = string.gsub(s, " ", "")
	t = string.gsub(t, "%.", "_")
	t = string.gsub(t, ":", "_")
	return t
end

function lovedoc.insert(t, p, e)
	if p[t.tag] then
		table.insert(p[t.tag], e)
		lovedoc.parse(t, e)
	else
		print("Warning: skipped incorrectly nested <"..t.tag..">. (Parent table must have appropriate field).")
	end	
end

function lovedoc.parse(t, p)
	p = p or lovedoc.data
	for i,v in pairs(t) do		
		if type(v) ~= "table" and v ~= t.tag and trim(v) ~= "" then
			if p._text then
				p._text = p._text .. trim(v) .. " "
			end
		end
		if v.tag then
			if lovedoc.parser[v.tag] then
				--print("Parsing: " .. v.tag)
				lovedoc.parser[v.tag](v, p)
			else
				print("!!! Skipped parsing: " .. v.tag)
			end
		end
	end
end

function lovedoc.docwrite(t)
	t = t or lovedoc.data
	for k,v in pairs(t) do
		if type(v) == "table"  and lovedoc.contains(lovedoc.symdef, k) then
			-- Write docs.
			if lovedoc.docwriter[k] then
				for j,e in ipairs(v) do
					lovedoc.docwriter[k](e)
				end
			else
				print("!!! Skipped docwrite: <" .. k .. "> (No docwriter)")
			end
		end		
	end
end

function lovedoc.contains(t, v)
	for i,value in ipairs(t) do
		if v == value then return true end
	end
	return false
end

function lovedoc.gensym(t)
	t = t or lovedoc.data
	
	for i,v in pairs(t) do
		if type(v) == "table" and lovedoc.contains(lovedoc.symdef, i) then
			for j,e in pairs(v) do
				local sig = e:signature()			
				if lovedoc.url.data[sig] then return lovedoc.url.data[sig] end
				if not lovedoc.url.count[e:fullname()] then lovedoc.url.count[e:fullname()] = 0 end
				local s = e:fullname()
				if lovedoc.url.count[e:fullname()] ~= 0 then
					s = s .. "_" .. lovedoc.url.count[e:fullname()]
				end
				s = lovedoc.strclean(s) .. ".html"
                                
				lovedoc.url.data[sig] = s
				table.insert(lovedoc.url.data, sig) -- Insert at next numerical.
				lovedoc.url.count[e:fullname()] = lovedoc.url.count[e:fullname()] + 1
                                
                                -- Insert plural, unless already present.
                                if e._plural and not lovedoc.url.data[e._plural] then
                                        lovedoc.url.data[e._plural] = s
                                        table.insert(lovedoc.url.data, e._plural)
                                        if not lovedoc.url.count[e._plural] then lovedoc.url.count[e._plural] = 0 end
                                        lovedoc.url.count[e._plural] = lovedoc.url.count[e._plural] + 1
                                end
				lovedoc.gensym(e)
			end
		end
	end
end

function lovedoc.sortsym()
	table.sort(lovedoc.url.data,
		function (a,b)
			return string.len(a) > string.len(b)
		end
		)
end

function lovedoc.urlsym()
		  for i,v in pairs(lovedoc.url.data) do
					 lovedoc.url.gsub[i] = '<a href="'..v..'">'..i..'</a>'
		  end
end

function lovedoc.symbolize(text)
	text = string.gsub(text, "([%a%.:]+)",
		function (c)
			if lovedoc.url.gsub[c] then 
				return lovedoc.url.gsub[c]
			elseif string.len(c) >= 1 then
				local last = string.sub(c, -1)
				if string.find(last, "%p") then
					local first = string.sub(c, 1, string.len(c)-1)
					if lovedoc.url.gsub[first] then
						return lovedoc.url.gsub[first] .. last
					end
				end
			end
			return c
		end
	)
	--text = string.gsub(text, "{(.-)}", lovedoc.url.gsub)
	text = string.gsub(text, "%[(.-)%]", '<%1>')
	return text
end
----------------------------------------------------
-- Buffer
----------------------------------------------------

lovedoc.Buffer = {}

function lovedoc.Buffer:tab()
	return string.rep("   ", #self._tagstack)
end

function lovedoc.Buffer:write(text)
	table.insert(self._data, self:tab()..text)
end

function lovedoc.Buffer:tofile(filename, selected)
	
	self:footer()
	
	if #self._tagstack > 0 then
		local s = ""
		for i,t in pairs(self._tagstack) do s = s .. t .. "," end
		error("Tag stack is not empty. Are you missing a pop? Stack: " .. s)
	end

	local f = io.open("docs/"..filename, "w")
	f:write(table.concat(self._data, "\n"))
	f:close()
end

function lovedoc.Buffer:html()
	return table.concat(self._data, "\n")
end

function lovedoc.Buffer:push( tag, class, attr)
	if class then class = " class=\"" .. class .. "\"" else class = "" end
	if attr then attr = " " .. attr else attr = "" end
	self:write("<"..tag..class..attr..">")
	table.insert(self._tagstack, tag)
end

function lovedoc.Buffer:div( class, attr)
	self:push("div", class, attr)
end

function lovedoc.Buffer:pop()
	local tag = table.remove(self._tagstack)
	self:write("</"..tag..">")
end

function lovedoc.Buffer:header()
	self:write('<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "DTD/xhtml1-strict.dtd\">')
	self:push('html', nil, 'xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en"')
		self:push('head')
			self:push('title')
				self:write('L&Ouml;VE Documentation 0.4.0')
			self:pop()
			self:write('<link rel="stylesheet" type="text/css" href="css/default.css" />')
			self:write('<meta http-equiv="content-type" content="text/html; charset=utf-8" />')
		self:pop()
		self:push('body')
			self:push('table', 'master', 'cellspacing="0"')
				self:push('tr')
					self:push('td', 'cell bar')
						self:div('header')
						self:pop()
						self:div('content')
end

function lovedoc.Buffer:menu(selected)
	
	local class =
		function(n)
			if selected == n then
				return 'class="selected"'
			end
			return ""
		end
	
	for k,v in pairs(lovedoc.menudef) do
		self:div('menu')
			self:div('title')
				self:write(v.name)
			self:pop()
			for i,m in ipairs(v.t) do
				self:write('<a '..class(m:name())..' href="'..m:url()..'">'..m:name()..'</a>')
			end
		self:pop()		
	end
	
	self:middle()
end

function lovedoc.Buffer:middle()
						self:pop()
					self:pop()
					self:push('td', 'cell')
end

function lovedoc.Buffer:footer()
					self:pop()
				self:pop()
			self:pop()
		self:pop()
	self:pop()
end

function lovedoc.newbuffer()
	local o = {}
	setmetatable(o, lovedoc.Buffer)
	lovedoc.Buffer.__index = lovedoc.Buffer
	o._tagstack = {}
	o._data = {}
	return o
end

----------------------------------------------------
-- Tag
----------------------------------------------------

lovedoc.Tag = {}
lovedoc.Tag._name = ""
lovedoc.Tag._parent = nil

function lovedoc.Tag:name()
	return self._name
end

function lovedoc.Tag:fullname()
	if not self._parent then return self:name() end
	return self._parent .. self._separator .. self:name()	
end

function lovedoc.Tag:signature()
	return self:fullname()
end

function lovedoc.Tag:shortsignature()
	return self:signature()
end

function lovedoc.Tag:url()
	assert(lovedoc.url.data[self:signature()], "Attempt to get nil-URL on " .. self:signature())
	return 	lovedoc.url.data[self:signature()]
end

function lovedoc.Tag:text()
	if not self._text then return "" end
	return self._text
end

function lovedoc.newtag()
	local o = {}
	setmetatable(o, lovedoc.Tag)
	lovedoc.Tag.__index = lovedoc.Tag
	o._name = ""
	o._parent = nil
	o._separator = "."
	return o
end

----------------------------------------------------
-- OverloadTag
----------------------------------------------------

lovedoc.OverloadTag = lovedoc.newtag()

function lovedoc.OverloadTag:shortsignature()
	local sig = self:name() .. "( "
	for i, p in ipairs(self.param) do
		sig = sig .. p:name()
		if i < #self.param then 
			sig = sig .. ", " 
		else 
			sig = sig .. " " 
		end
	end
	sig = sig .. ")"
	return sig
end

function lovedoc.OverloadTag:signature()
	if not self._parent then return self:shortsignature() end
	return self._parent .. self._separator .. self:shortsignature()
end


function lovedoc.newoverloadtag()
	local o = {}
	setmetatable(o, lovedoc.OverloadTag)
	lovedoc.OverloadTag.__index = lovedoc.OverloadTag
	o._name = ""
	o._parent = nil
	o._separator = "."
	return o
end


----------------------------------------------------
-- TypeTag
----------------------------------------------------

lovedoc.TypeTag = lovedoc.newtag()

function lovedoc.TypeTag:fullname()
	return self:name()
end

function lovedoc.TypeTag:shortsignature()
	return self:name()
end

function lovedoc.TypeTag:signature()
	return self:name()
end

function lovedoc.newtypetag()
	local o = {}
	setmetatable(o, lovedoc.TypeTag)
	lovedoc.TypeTag.__index = lovedoc.TypeTag
	o._name = ""
	o._parent = nil
	return o
end

----------------------------------------------------
-- Parsers
----------------------------------------------------

function lovedoc.parser.param(t, p)
	local o = lovedoc.newtag()
	o._name = t.attr.name or "noparam"
	o._brief = t.attr.brief or "(No description.)"
	lovedoc.insert(t, p, o)
end

function lovedoc.parser.ret(t, p)
	local o = lovedoc.newtag()
	o._name = t.attr.name or "var"
	o._type = t.attr.type or "noparam"
	o._brief = t.attr.brief or "(No description.)"
	lovedoc.insert(t, p, o)
end

function lovedoc.parser.section(t, p)
	local o = lovedoc.newtag()
	o._name = t.attr.name or "No Name"
	o._text = ""
	lovedoc.insert(t, p, o)
end

function lovedoc.parser.example(t, p)
	local o = lovedoc.newtag()
        o._id = t.attr.id or error("Missing required attribute \"id\".")
        o._name = "Example "..exnum(o._id)
        o._data = exget(o._id)
        lovedoc.insert(t, p, o)
end

function lovedoc.parser.see(t, p)
	local o = lovedoc.newtag()
        o._text = ""
        lovedoc.insert(t, p, o)
end

function lovedoc.parser.item(t, p)
	local o = lovedoc.newtag()
      o._name = t.attr.name or "noname"
	o._brief = t.attr.brief or "(No description)"
	o._type = t.attr.name
	o._space = t.attr.space
        lovedoc.insert(t, p, o)
end

function lovedoc.parser.misc(t, p)
	local o = lovedoc.newtag()
	o._name = t.attr.name or "No Name"
	o._text = ""
	o._title = t.attr.title or o._name
	o.item = {}
	lovedoc.insert(t, p, o)
end


----------------------------------------------------
-- Common Docwriter Operations
----------------------------------------------------

function page_begin(b, header, title, description)
        b:div("page")
        b:div("title")
        b:write(header)
        b:pop()
		  
		  b:div("chapter")
			b:div("title")
			b:write(title)
			b:pop()
        b:div("text")
        b:write(lovedoc.symbolize(description))
        b:pop()
        
end

function page_begin_lite(b, header)
        b:div("page")
        b:div("title")
        b:write(header)
        b:pop()
end

function page_end(b)
		  b:pop()
        page_end_lite(b)
end

function page_end_lite(b, header)
        b:div("foot")
                b:write("Copyright &copy; 2006-2008 L&Ouml;VE Development Team")      
                b:div("links")
                b:write('<a href="http://love2d.org">Visit homepage</a> - <a href="ManualImprovements.html">Help improve the manual</a>')
                b:pop()
        b:pop()
        b:pop()
end

function attr_begin(b, title)
        b:div("attr")
        b:div("title")
        b:write(title)
        b:pop()
        b:div("content")   
end

function attr_end(b)
        b:pop()
        b:pop()
end

function section_begin(b, title)
        b:div("section")
        b:div("title")
        b:write(title)
        b:pop()
        b:div("content")        
end

function section_end(b)
        b:pop()
        b:pop()
end

function cluster_section_begin(b, title)
   section_begin(b, title)
   b:div("cluster")
end

function cluster_section_end(b, title)
	b:pop()
	section_end(b)	
end

function cluster_item(b, name, desc)
	local n = lovedoc.url.gsub[name] or name
	b:div("item")
	b:push("span", "name"); b:write(n); b:pop()
	b:push("span", "desc"); b:write(lovedoc.symbolize(desc)); b:pop()
	b:pop()
end


function list_section_begin(b, title)
        section_begin(b, title)
        b:div("list")
        b:push("table", "data")       
end

function list_section_end(b)
        b:pop()
        b:pop()
        section_end(b)
end

function list_item(b, name, desc)
        b:push("tr")
        b:push("td", "name"); b:write(name); b:pop()
        b:push("td", "desc"); b:write(lovedoc.symbolize(desc)); b:pop()
        b:pop()
end

function space_list_item(b)
        b:push("tr")
        b:push("td", "space"); b:pop()
        b:push("td", "desc"); b:pop()
        b:pop()
end

function func_section(b, list)
        if #list <= 0 then return end
        list_section_begin(b, "Functions")
	for fi,f in ipairs(list) do
		for oi, o in ipairs(f.overload) do
			list_item(b,"<a href=\""..o:url().."\">"..o:shortsignature() .."</a>", o._brief)
			if o._space then space_list_item(b) end
		end
		if f._space then space_list_item(b) end
	end
        list_section_end(b)

end

function type_section(b, list)
   if #list <= 0 then return end
   list_section_begin(b, "Types")
	for i, t in ipairs(list) do
		list_item(b, "<a href=\""..t:url().."\">"..t:shortsignature() .."</a>", t._brief)
		if t._space then space_list_item(b) end
	end
   list_section_end(b)
end

function param_section(b, list)
        cluster_section_begin(b, "Arguments")
	if #list > 0 then
		for i, v in ipairs(list) do
			cluster_item(b, v:shortsignature(), v._brief)
		end
	else
		cluster_item(b, "(None)", "")
	end
        cluster_section_end(b)
end

function synopsis_section(b, name, ret)
	section_begin(b, "Synopsis")
	b:div("synopsis")
	
	local retvals = ""
	if ret and #ret > 0 then
		for i=1,(#ret-1) do
			local r = ret[i]._name or ret[i]._type
			retvals = retvals .. string.lower(r) .. ", "
		end
		local r = ret[#ret]._name or ret[#ret]._type
		retvals = retvals .. string.lower(r) .. " = "
	end
	
	
	b:write(retvals..name)
	b:pop()
	section_end(b)
end

function synopsis_callback_section(b, name, ret)
	section_begin(b, "Synopsis")
	b:div("synopsis")
	
	local retvals = ""
	if ret and #ret > 0 then
		for i=1,(#ret-1) do
			local r = ret[i]._name or ret[i]._type
			retvals = retvals .. string.lower(r) .. ", "
		end
		local r = ret[#ret]._name or ret[#ret]._type
		retvals = retvals .. string.lower(r) .. " = "
	end
	
	
	b:write(retvals.. "function " .. name .. " ... end")
	b:pop()
	section_end(b)
end

function ret_section(b, list)
	cluster_section_begin(b, "Returns")
	if #list > 0 then
		for i, v in ipairs(list) do
		cluster_item(b, v._type, v._brief)
		end
	else
		cluster_item(b, "(Nothing)", "")
	end
	cluster_section_end(b)
end

function item_section(b, list, name)
	if #list <= 0 then return end
        list_section_begin(b, name)
	for i, v in ipairs(list) do
		list_item(b, v._name, v._brief)
		if v._space then space_list_item(b) end
	end
        list_section_end(b)
end

function attr_section(b, list, title, nothing, _name, _brief)
	_name = _name or "_name"
	_brief = _brief or "_brief"
	--nothing = nothing or "(Nothing)"
	attr_begin(b, title)
	
	if #list > 0 then
		for i, v in ipairs(list) do
			attr_item(b, v[_name], v[_brief])
		end
	else
		--attr_item(b, nothing)
	end
	attr_end(b)
end

function attr_item(b, name, brief)
        b:push("div", "item")
        b:push("span", "name"); b:write(lovedoc.symbolize(name)); b:pop()
        b:push("span", "desc"); b:write(lovedoc.symbolize(brief)); b:pop()
        b:pop()	
end

function example_section(b, list)
        if #list <= 0 then return end
        b:div("section")
        b:div("title")
        b:write("Examples")
        b:pop()
        b:div("content")
        for ei,e in ipairs(list) do
                local code, title, id = exgen(e._data)
                code = code or error("No code")
                title = title or error("No title")
                b:div("example")
                b:div("title")
                b:write("Example " .. e._id .. ": " .. title)
                b:pop()
                b:div("code")
                b:write(code)
                b:pop()
                b:pop()
        end
        b:pop()
        b:pop()
end

function see_section(b, list)
        if #list <= 0 then return end
        b:div("section")
        b:div("title")
        b:write("See Also")
        b:pop()
        b:div("content")
        for si,s in ipairs(list) do
				local text = string.gsub(s:text(), "([%w%p]-)([, ])",
					function(s,e)
						if lovedoc.url.gsub[s] then return lovedoc.url.gsub[s]..e end
						return s..e
					end)
		  
                b:write(text)
        end
        b:pop()
        b:pop()
end

function section_section(b, list)
        if #list <= 0 then return end
        for si,s in ipairs(list) do
					 b:div("chapter")
						b:div("title")
								  b:write(s:name())
						b:pop()
						b:div("content")
								  b:write(lovedoc.symbolize(s:text()))
						b:pop()
					 b:pop()
        end
end

----------------------------------------------------
-- Docwriters
----------------------------------------------------

function lovedoc.docwriter.misc(m)

		local b = lovedoc.newbuffer()
		b:header()
		b:menu(m:name())
			
		page_begin(b, "Miscellaneous", m:name(), m:text())
		item_section(b, m.item, m._title)
		page_end(b)
		
		b:tofile(m:url())
end

----------------------------------------------------
-- Includes
----------------------------------------------------

dofile("module.lua")
dofile("type.lua")
dofile("func.lua")
dofile("overload.lua")
dofile("callback.lua")
dofile("page.lua")
dofile("ghost.lua")

----------------------------------------------------
-- Testdata
----------------------------------------------------

local xml = io.open("data.xml")

tab, emsg, eline = lxp.lom.parse (xml:read("*all"))
if not tab then 
	error(emsg .. " at line " .. eline)
end
lovedoc.parse(tab)

lovedoc.gensym()
lovedoc.sortsym()
lovedoc.urlsym()
--table_print(lovedoc.url.data)
--table_print(lovedoc.data)
lovedoc.docwrite()

io.close(xml)