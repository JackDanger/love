
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
	
	love.filesystem.setIdentity("love");
	love.filesystem.setSource("D:\\projects\\love\\src\\lua")

	love.insmod("sdltimer", "timer")
	love.insmod("devil", "image")
	love.insmod("opengl", "graphics")
	love.insmod("sdlsystem", "system")
	love.insmod("openal", "audio")
	love.insmod("sdlsound", "sound")

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

		love.timer.sleep(10)
		love.graphics.present()

	end

end

-----------------------------------------------------------
-- Regular code goes here.
-----------------------------------------------------------

function love.load()


	imageData = love.image.newImageData("planet1.png")
	planet = love.graphics.newImage(imageData)

	num = 300

	vb = love.graphics.newVertexBuffer(num, love.type_points, love.usage_array)

	for i=1,num do
		vb:add(math.random(0, 800),math.random(0, 600))
	end


	sb = love.graphics.newSpriteBatch(planet, num)

	planets = {}

	for i=1,num do
		table.insert(planets, { x = math.random(0, 800), y = math.random(0, 600), a = math.pi*200/math.random(1, 100) })
	end

end

a = 0

function love.update(dt)
	a = a + dt
end

function love.draw()

	sb:clear()
	for i,v in ipairs(planets) do
		sb:add(v.x + math.sin(a) * 100, v.y, v.a + a)
	end

	--love.graphics.draw(vb, 0, 0)
	love.graphics.draw(sb, 0, 0)

	love.graphics.setColor(255, 0, 0, 255)

	love.graphics.drawTest(planet, 200, 200, a, 2)
	love.graphics.draw(planet, 264, 200, a, 2)

end

function love.keypressed(k)
	

	if k == love.key_f then print(love.timer.getFPS()) end
	if k == love.key_t then if toggle then toggle = true else toggle = nil end end



end

-----------------------------------------------------------
-- Regular code ends.
-----------------------------------------------------------

local result = xpcall(love.init,
	function (msg)
		print(msg, debug.traceback())
	end)


print("Done.")
