-- Example: Mini Physics

function load()

	-- Create a world with size 2000 in every direction.
	world = love.physics.newWorld(2000, 2000)
	world:setGravity(0, 50)

	-- Create the ground body at (0, 0) with mass 0.
	ground = love.physics.newBody(world, 0, 0, 0)
	
	-- Create the ground shape at (400,500) with size (600,10).
	ground_shape = love.physics.newRectangleShape(ground, 400, 500, 600, 10)

	-- Load the image of the ball.
	ball = love.graphics.newImage("images/love-ball.png")

	-- Create a Body for the circle.
	body = love.physics.newBody(world, 400, 200)
	
	-- Attatch a shape to the body.
	circle_shape = love.physics.newCircleShape(body, 28)
	
	-- Calculate the mass of the body based on attatched shapes.
	-- This gives realistic simulations.
	body:setMassFromShapes()

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
end

function keypressed(k)
	if k == love.key_space then
		-- Apply a random impulse
		body:applyImpulse(100000-math.random(0, 200000), 0)
	end
end