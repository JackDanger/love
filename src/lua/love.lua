

setup = {}

setup.options = {
	["--game"] = {
		description = "The love file or directory to load.",
		narg = 1,
	},
	["--help"] = {
		description = "Prints this message.",
		narg = 0,
	},
	["--version"] = {
		description = "Prints the version of the program.",
		narg = 0,
	},
	["--verbose"] = {
		description = "Prints extra information to standard out.",
		narg = 0,
	},
	["--width"] = {
		description = "Sets the window width.",
		narg = 1,
	},
	["--height"] = {
		description = "Sets the window width.",
		narg = 1,
	},
	["--disable-system"] = {
		description = "Loads without a system module.",
		narg = 0,
	},
	["--disable-filesystem"] = {
		description = "Loads without a filesystem module.",
		narg = 0,
	},
	["--disable-graphics"] = {
		description = "Loads without a graphics module.",
		narg = 0,
	},
	["--disable-keyboard"] = {
		description = "Loads without a keyboard module.",
		narg = 0,
	},
	["--disable-timer"] = {
		description = "Loads without a timer module.",
		narg = 0,
	},
	["--disable-mouse"] = {
		description = "Loads without a mouse module.",
		narg = 0,
	},
	["--disable-joystick"] = {
		description = "Loads without a joystick module.",
		narg = 0,
	},
	["--disable-audio"] = {
		description = "Loads without a audio module.",
		narg = 0,
	},
	["--disable-physics"] = {
		description = "Loads without a physics module.",
		narg = 0,
	},
}

function setup.getsource()

	if not arg[0] then return nil end

	-- Get the working directory.
	local wd = string.gsub(love.filesystem.getWorkingDirectory(), "\\", "/")

	-- Get the argument.
	local a = string.gsub(arg[0], "\\", "/")

	local absolute = string.sub(a,1,1) == "/" or string.find(string.sub(a,1,3), "%a:/")

	if absolute then
		return a
	else
		return wd .. "/" .. a
	end

end

function setup.parseoptions()

	local t = {}

	for i,v in pairs(arg) do
		
		local s, e, o = string.find(v, "(%-%-[%w%-]+)")
		if s then

			-- Is this a valid option?
			if not setup.options[o] then
				return error("Invalid option: " .. o)
			end
			
			-- The option is valid. Create it.
			t[o] = { args = {} }

			-- Get arguments.
			for j=(i+1),(i+setup.options[o].narg) do
				if not arg[j] then return error(setup.options[o].narg.." parameter(s) expected for option " .. o .. ".") end
				table.insert(t[o].args, arg[j])
			end

		end

	end
	
	return t
end

function love.init()

	-- Get the full path to the game source.
	local success, options = xpcall(setup.parseoptions,
		function (msg)
			print(msg, debug.traceback())
		end)

	--[[
	if options then
		for i,v in pairs(options) do
			print(i,unpack(v.args))
		end
	end
	--]]

	local opt = function(q)
		return options[q]
	end

	local creq = function(n,m)
		if not opt("--disable-"..n) then
			require(m)
		end
	end

	if opt("--help") then

		local atleast = function(str, min)
			local size = #str
			if size < min then 
				return str .. str.rep(" ", min-size)
			end
			return str
		end

		local pad = "  "
		print("\nWant to learn how to LOVE?")
		print("--------------------------\n")
		print("Usage:")
		print("------\n")
		print(pad.."love [options] game\n")
		print("Examples:")
		print("---------\n")
		print(pad.."love mygame.love")
		print(pad.."love /path/to/game")
		print(pad.."love ../game")
		print(pad.."love --disable-audio game.love")
		print()
		print("Options:")
		print("--------\n")
		
		for i,v in pairs(setup.options) do
			local args = ""
			for j=1,v.narg do args = " arg"..j end
			print(atleast(pad..i..args, 25) .. v.description)
		end

		return true
	end

	-- Let's require some modules.
	creq("system", "love_sdlsystem")
	creq("filesystem", "love_physfs")
	creq("graphics", "love_opengl")
	creq("keyboard", "love_sdlkeyboard")
	creq("timer", "love_sdltimer")
	creq("mouse", "love_sdlmouse")
	creq("joystick", "love_sdljoystick")
	creq("luasocket", "love_luasocket")
	creq("box2d", "love_box2d")

	if not false then return true end

	love.graphics.setMode(800, 600, false, true, 0)
	love.filesystem.setIdentity("test9000")


	
	if true then return false end
	
	if source then
		print("Source is: " .. source)
		love.filesystem.setSource(source)
	else
		print("There is no source: load nogame.")
		return false
	end

	-- Parse main file.
	if love.filesystem.exists("main.lua") then
		require("main.lua")
	end

	setup = nil
	collectgarbage()

	-- Call love.run.
	local result = xpcall(love.run,
		function (msg)
			print(msg, debug.traceback())
		end)

	return result
end

function love.run()

	if load then load() end

	-- Main loop time.
	while true do

		love.timer.step()
		if update then update(love.timer.getDelta()) end
		love.graphics.clear()
		if draw then draw() end

		-- Process events.
		for e,a,b,c in love.system.events() do
			if e == love.event_quit then return end
			love.handlers[e](a,b,c)
		end
		
		love.graphics.present()

	end

end

-- Standard callback handlers.
love.handlers = {
	[love.event_keypressed] = function (b)
		if keypressed then keypressed(b) end
	end,
	[love.event_keyreleased] = function (b)
		if keyreleased then keyreleased(b) end
	end,
	[love.event_mousepressed] = function (x,y,b)
		if mousepressed then mousepressed(x,y,b) end
	end,
	[love.event_mousereleased] = function (x,y,b)
		if mousereleased then mousereleased(x,y,b) end
	end,
	[love.event_joystickpressed] = function (j,b)
		if joystickpressed then joystickpressed(j,b) end
	end,
	[love.event_joystickreleased] = function (j,b)
		if joystickreleased then joystickreleased(j,b) end
	end,
	[love.event_quit] = function ()
		return
	end,
}

function keypressed(key)
	print("getWorkingDirectory", love.filesystem.getWorkingDirectory())
	print("getUserDirectory", love.filesystem.getUserDirectory())
	print("getAppdataDirectory", love.filesystem.getAppdataDirectory())
	print("getSaveDirectory", love.filesystem.getSaveDirectory())
	for i,v in pairs(arg) do
		print(i,v)
	end
end