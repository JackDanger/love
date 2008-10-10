

love.setup = {}

function love.setup.getSource()

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

-- Removes trailing and leading whitespace 
-- from a string.
function love.setup.trim(s)
  return (s:gsub("^%s*(.-)%s*$", "%1"))
end

function love.setup.getConf()

	local conf = {

		["width"] = 800, 
		["height"] = 600,
		["fullscreen"] = false,
		["vsync"] = true,
		["fsaa"] = 0,
		["display_auto"] = true,

		["title"] = "Untitled Game",
		["author"] = "Unknown Author",

		["disable_graphics"] = false,
		["disable_audio"] = false,
		["disable_physics"] = false,
		["disable_keyboard"] = false,
		["disable_mouse"] = false,
		["disable_timer"] = false,
		["disable_joystick"] = false,
		["disable_luasocket"] = false,
		
		["love_version"] = "0.6.0",
	}

	-- Read the file, if any.
	if love.filesystem.exists("game.conf") then
		for line in love.filesystem.lines("game.conf") do
			local u1, u2, key, value = string.find(line, "([%w_ ]+)=(.+)")
			
			-- Remove leading/trailing whitespace.
			key = love.setup.trim(key)
			value = love.setup.trim(value)
			
			-- Overwrite default values in conf table.
			conf[key] = value
		end
	end

	return conf
end

function love.setup.filesystem()

	local source = love.setup.getSource()

	if source then
		print("Source is: " .. source)
		love.filesystem.setSource(source)
		love.filesystem.setIdentity("test9000")
	else
		print("There is no source: load nogame.")
		return false
	end
	return true
end

function love.init()

	-- These are ALWAYS required.
	require("love_sdlsystem")
	require("love_physfs")

	-- Setup the filesystem folders.
	if not love.setup.filesystem() then
		return false
	end
	
	-- Read the config file.
	local conf = love.setup.getConf()

	-- These are all optional.
	require("love_opengl")
	require("love_sdlkeyboard")
	require("love_sdltimer")
	require("love_sdlmouse")
	require("love_sdljoystick")
	require("love_luasocket")
	require("love_box2d")

	-- Auto-configure display, unless otherwise specified.
	if conf["display_auto"] then
		love.graphics.setMode(
			conf["width"], 
			conf["height"], 
			conf["fullscreen"],
			conf["vsync"],
			conf["fsaa"])
	end

	-- Parse main file, unless a love.main has been preloaded.
	if not love.main and love.filesystem.exists("main.lua") then
		love.main = love.filesystem.load("main.lua")
	end
	
	-- Call love.main.
	if love.main then
		love.main()
	end


	love.setup = nil
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
