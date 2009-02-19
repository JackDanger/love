
-- Make sure love table exists.
if not love then love = {} end

function love.insmod(name, provides)
	if love.__mod[provides] and love.__mod[provides][name] then
		love.__mod[provides][name].open()
		print("Opened " .. provides .. " module " .. name .. ".")
	end
end

-- Standard callback handlers.
love.handlers = {
	[love.event_keypressed] = function (b)
		if love.keypressed then love.keypressed(b) end
	end,
	[love.event_keyreleased] = function (b)
		if love.keyreleased then love.keyreleased(b) end
	end,
	[love.event_mousepressed] = function (x,y,b)
		if love.mousepressed then love.mousepressed(x,y,b) end
	end,
	[love.event_mousereleased] = function (x,y,b)
		if love.mousereleased then love.mousereleased(x,y,b) end
	end,
	[love.event_joystickpressed] = function (j,b)
		if love.joystickpressed then love.joystickpressed(j,b) end
	end,
	[love.event_joystickreleased] = function (j,b)
		if love.joystickreleased then love.joystickreleased(j,b) end
	end,
	[love.event_quit] = function ()
		return
	end,
}

function love.init()

	if love.__args then
		for i,v in pairs(love.__args) do
			print(i,v)
		end
	end
	
	love.insmod("physfs", "filesystem")
	love.insmod("opengl", "graphics")
	love.insmod("devil", "image")
	love.insmod("sdljoystick", "joystick")
	love.insmod("sdlkeyboard", "keyboard")
	love.insmod("sdlmouse", "mouse")
	love.insmod("sdlsound", "sound")
	love.insmod("sdltimer", "timer")
	love.insmod("sdlsystem", "system")
	love.insmod("openal", "audio")
	love.insmod("box2d", "physics")

	if love.graphics.checkMode(800, 600, false) then
		love.graphics.setMode(800, 600, false, false)
	end

	love.run()
end

function love.run()

	if love.load then love.load() end

	-- Main loop time.
	while true do
		love.timer.step()
		if love.update then love.update(love.timer.getDelta()) end
		love.graphics.clear()
		if love.draw then love.draw() end

		-- Process events.
		for e,a,b,c in love.system.events() do
			if e == love.event_quit then return end
			love.handlers[e](a,b,c)
		end

		--love.timer.sleep(10)
		love.graphics.present()

	end

end

-----------------------------------------------------------
-- Regular code ends.
-----------------------------------------------------------

local result = xpcall(love.init,
	function (msg)
		print(msg, debug.traceback())
	end)


print("Done.")