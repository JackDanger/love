
print("File is done")

love.temp = {}

function love.temp.getSource()

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

function love.init()
	print("Init called")

	-- Let's require some modules.
	require("love_sdlsystem")
	require("love_physfs")
	require("love_opengl")
	require("love_sdlkeyboard")
	require("love_sdltimer")
	require("love_sdlmouse")
	require("love_sdljoystick")
	require("love_luasocket")
	require("love_box2d")

	love.graphics.setMode(800, 600, false, true, 0)
	love.filesystem.setIdentity("test9000")

	-- Get the full path to the game source.
	local source = love.temp.getSource()
	print("Source is: " .. source)
	love.filesystem.setSource(source)

	-- Parse main file.
	if love.filesystem.exists("main.lua") then
		require("main.lua")
	end

	love.temp = nil
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