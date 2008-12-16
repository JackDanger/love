
-- Make sure love table exists.
if not love then love = {} end

function love.insmod(name, provides)
	if love.__mod[provides] and love.__mod[provides][name] then
		love.__mod[provides][name].open()
		print("Opened " .. provides .. " module " .. name .. ".")
	end
end

function love.init()

	if love.__args then
		for i,v in pairs(love.__args) do
			print(i,v)
		end
	end
	
	love.insmod("sdltimer", "timer")
	love.insmod("devil", "image")
	love.insmod("opengl", "graphics")
	love.insmod("sdlsystem", "system")

	if love.graphics.checkMode(800, 600, false) then
		print("800x600 is supported")
		love.graphics.setMode(800, 600, false, false)
	end

	formats = love.image.getFormats()
	print(formats)
	data = love.image.newImageData(128, 128)

	up = function (x, y, r, g, b, a)
		local g = (x/128)*255
		return g, g, g, 255
	end

	data:mapPixel(up)

	image = love.graphics.newImage(data)

	love.run()
end

function love.run()

	-- Main loop time.
	while true do

		--love.timer.step()
		--if update then update(love.timer.getDelta()) end

		love.graphics.clear()

		love.graphics.draw(image, 200, 200)

		-- Process events.
		for e,a,b,c in love.system.events() do
			if e == love.event_quit then return end
			print(e, a, b, c)
			--love.handlers[e](a,b,c)
		end

		love.graphics.present()

	end

end

local result = xpcall(love.init,
	function (msg)
		print(msg, debug.traceback())
	end)


print("Done.")
