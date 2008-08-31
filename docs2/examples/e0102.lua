-- Example: Mini Physics Contacts

text = "No collision yet."

function load()

	-- Set a font.
	local font = love.graphics.newFont(love.default_font, 12)
	love.graphics.setFont(font)

	-- Create a world with size 2000 in every direction.
	world = love.physics.newWorld(2000, 2000)
	world:setGravity(0, 50)

	-- Create the ground body at (0, 0) with mass 0.
	ground = love.physics.newBody(world, 0, 0, 0)

	-- Create the ground shape at (400,500) with size (600,10).
	ground_shape = love.physics.newRectangleShape(ground, 400, 500, 600, 10)
	ground_shape:setData("Ground") -- Set a string userdata

	-- Load the image of the ball.
	ball = love.graphics.newImage("images/love-ball.png")

	-- Create a Body for the circle.
	body = love.physics.newBody(world, 400, 200)
	
	-- Attatch a shape to the body.
	circle_shape = love.physics.newCircleShape(body, 28)
	circle_shape:setRestitution(0.3) -- More bounce
	circle_shape:setData("Ball") -- Set a string userdata
	
	-- Calculate the mass of the body based on attatched shapes.
	-- This gives realistic simulations.
	body:setMassFromShapes()
	
	-- Set the collision callback.
	world:setCallback(collision)

end

function update(dt)
	-- Update the world.
	world:update(dt)
end

function draw()
	-- Draws the ground.
	love.graphics.polygon(love.draw_line, ground_shape:getPoints())

	-- Draw the circle.
	love.graphics.draw(ball,body:getX(), body:getY(), body:getAngle())

	-- Draw text.
	love.graphics.draw(text, 50, 50)
end

function keypressed(k)
	if k == love.key_space then
		-- Apply a random impulse
		body:applyImpulse(100000-math.random(0, 200000), 0)
	end
end

-- This is called every time a collision occurs.
function collision(a, b, c)
	
	local f, r = c:getFriction(), c:getRestitution()
	local s = c:getSeparation()
	local px, py = c:getPosition()
	local vx, vy = c:getVelocity()
	local nx, ny = c:getNormal()

	text = "Last Collision:\n"
	text = text .. "Shapes: " .. a .. " and " .. b .. "\n"
	text = text .. "Position: " .. px .. "," .. py .. "\n"
	text = text .. "Velocity: " .. vx .. "," .. vy .. "\n"
	text = text .. "Normal: " .. nx .. "," .. ny .. "\n"
	text = text .. "Friction: " .. f .. "\n"
	text = text .. "Restitution: " .. r .. "\n"
	text = text .. "Separation: " .. s .. "\n"

end
