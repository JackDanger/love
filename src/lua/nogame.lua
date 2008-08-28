
flash = 0
display = true

function load()

	if not love.graphics.isCreated() then
		love.graphics.setMode(800, 600, false, true, 0)
	end

	love.graphics.setLineWidth(2)

	love.graphics.setCaption("LOVE " .. love.system.getVersion() .. " (" .. love.system.getCodename() .. ")")
	big = love.graphics.newFont(love.default_font, 24)
	small = love.graphics.newFont(love.default_font, 12)
	love.graphics.setBackgroundColor(54, 172, 248)

	-- Images.
	freechan = love.graphics.newImage(love.default_freechan)
	logo = love.graphics.newImage(love.default_logo_256)
	green_ball = love.graphics.newImage(love.default_green_ball)
	love_ball = love.graphics.newImage(love.default_big_love_ball)
	speak_cloud = love.graphics.newImage(love.default_speak_cloud)

	-- Create a physics world.
	world = love.physics.newWorld(-200, -200, 1000, 1000, 0, 0, true)

	-- Create walls.
	ground = love.physics.newBody(world, 0, 0, 0)
	wall_left = love.physics.newPolygonShape(ground, -50, -50, -50, 650, 0, 650, 0, -50)
	wall_right = love.physics.newPolygonShape(ground, 800, -50, 800, 650, 850, 650, 850, -50)
	wall_top = love.physics.newPolygonShape(ground, 0, 0, 800, 0, 800, -50, 0, -50)
	wall_bottom = love.physics.newPolygonShape(ground, 0, 650, 800, 650, 800, 600, 0, 600)

	balls = {}

	for i=1,7 do

		local b = love.physics.newBody(world, 100*i, 500, 50)
		local radius = 32
		local img = green_ball

		if i == 4 then
			radius = 45
			img =  love_ball
		end

		local b = love.physics.newBody(world, 100*i, 520, 100)
		local s = love.physics.newCircleShape(b, 0, 0, radius)
		b:setMassFromShapes()
		table.insert(balls, { b = b, s = s, img = img}) 

	end

end

r = 0 

function update(dt) 
	r = r + dt
	flash = flash + dt
	if flash > 0.8 then flash = 0; display = not display; end

	if joint then
		joint:setTarget(love.mouse.getPosition())
	end

	-- Update the world.
	world:update(dt)
end

function draw()

	-- Draw shapes.
	for i,v in ipairs(balls) do
		love.graphics.draw(v.img, v.b:getX(), v.b:getY(), v.b:getAngle())
	end
	
	if joint then
		local x1, y1, x2, y2 = joint:getAnchors()
		love.graphics.line(x1, y1, x2, y2)
	end
	
	love.graphics.setFont(small) 
	love.graphics.draw(logo, 400, 280) 
	love.graphics.draw(freechan, 325, 360)
	love.graphics.draw(speak_cloud, 430, 390 )
	
	love.graphics.drawf(love.system.getVersion() .. "\n" .. love.system.getCodename(), 480, 560, 300, love.align_right)     
	love.graphics.setFont(big) 
	if display then love.graphics.drawf("No Game", 345, 405, 200, love.align_center) end

end

function mousejoint(g, x, y)
	for i,v in ipairs(balls) do
		if v.s:testPoint(x, y) then
			joint = love.physics.newMouseJoint(v.b, x, y)
			break
		end
	end    
end

function keypressed(k)
	if k == love.key_r then
		love.system.restart()
	end
end

function mousepressed(x, y, b)
	mousejoint(balls, x, y)
end

function mousereleased(x, y, b)
	joint = nil
	collectgarbage()
end
