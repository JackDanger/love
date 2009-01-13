
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
		print("800x600 is supported")
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

a = 0
playsound = false
frames = 0

function love.load()

	--[[

	formats = love.image.getFormats()
	print(formats)
	data = love.image.newImageData(128, 128)

	up = function (x, y, r, g, b, a)
		local g = (x/128)*255
		return g, g, g, 255
	end

	data:mapPixel(up)
	image = love.graphics.newImage(data)
	--]]

	imageData = love.image.newImageData("planet1.png")
	planet = love.graphics.newImage(imageData)

	if playsound then
		soundData = love.sound.newSoundData("startup.wav")
		sound = love.audio.newSound(soundData)
		
		soundData2 = love.sound.newSoundData("jazz.flac")
		music = love.audio.newMusic(soundData2)
		
		soundData3 = love.sound.newSoundData("paradox1.xm")
		chip = love.audio.newMusic(soundData3)
	
		channel = love.audio.newChannel()
	
		love.audio.play(music, channel)
	end
	
	num_planets = 300
	max_frames = 1000
	planets = {}
	for i=1,num_planets do
		table.insert(planets, {x = math.random(0, 800), y = math.random(0, 600), a = math.random(0, 6)})
	end

end

--[[

love.graphics.draw(image, x, y, a, sx, sy, ox, oy)
love.graphics.draws(image, x, y, a, sx, sy, ox, oy, xs, ys, ws, hw)

sb:draw(image, x, y, a, sx, sy, ox, oy)

--]]

function love.update(dt)
	a = a + math.pi*dt
	
	if first_draw and frames < max_frames then
		if (frames % 60) == 0 then
			print("Planets: " .. num_planets .. " FRAMES: " .. frames)
		end
	end
	
	if frames == max_frames then
		print("TIME PER FRAME: " .. ((love.timer.getTime()-first_draw)/frames))
	end
end

function love.draw()
	--love.graphics.draw(image, 200, 200, a)
	--love.graphics.print("fist", 400, 200)

	if not first_draw then first_draw = love.timer.getTime() end

	for i,v in ipairs(planets) do
		love.graphics.draw(planet, v.x, v.y, v.a)
	end
	
	frames = frames + 1
end

function love.keypressed(k)

	if playsound then

		if k == love.key_c then
			love.audio.play(chip)
		end
	
		if k == love.key_s then
			love.audio.stop(channel)
		end
		
		if k == love.key_q then
			love.audio.pause(channel)
		end
	
		if k == love.key_p then
			love.audio.play(sound, channel)
		end
		
		if k == love.key_r then
			love.audio.rewind(channel)
		end
		
		if k == love.key_up then
			channel:setPitch(channel:getPitch() + 0.1)
		end
		
		if k == love.key_down then
			channel:setPitch(channel:getPitch() - 0.1)
		end
	
		if k == love.key_left then
			channel:setVolume(channel:getVolume() - 0.1)
		end
	
		if k == love.key_right then
			channel:setVolume(channel:getVolume() + 0.1)
		end
		
		if k == love.key_8 then
			love.audio.setVolume(love.audio.getVolume() - 0.1)
		end
		
		if k == love.key_9 then
			love.audio.setVolume(love.audio.getVolume() + 0.1)
		end
		
		if k == love.key_m then
			if love.audio.getVolume() > 0.1 then
				stvol = love.audio.getVolume()
				love.audio.setVolume(0)
			else
				love.audio.setVolume(stvol or 1)
			end
		end
		
		if k == love.key_i then
			love.audio.play(music)
		end
	
	
		print("( "..love.audio.getNumChannels()..") Master: " .. love.audio.getVolume() .. ", Volume: " ..channel:getVolume()..", Pitch: " .. channel:getPitch())
	end -- playsound
end

-----------------------------------------------------------
-- Regular code ends.
-----------------------------------------------------------

local result = xpcall(love.init,
	function (msg)
		print(msg, debug.traceback())
	end)


print("Done.")
