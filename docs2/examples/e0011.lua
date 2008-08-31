-- Example: Create and use an Animation

function load()
	-- Set a lovely pink background color.
	love.graphics.setBackgroundColor(246, 198, 222)
	
	-- Load the source of the animation.
	local img = love.graphics.newImage("images/anim-boogie.png")
	
	-- Create an animation with a frame size of 32x32 and
	-- 0.1s delay betwen each frame.
	anim = love.graphics.newAnimation(img, 32, 32, 0.1)
end

function update(dt)
	-- The animation must be updated so it 
	-- knows when to change frames.
	anim:update(dt)
end

function draw()
	-- Draw the animation the center of the screen.
	love.graphics.draw(anim, 400, 300, 0, 1, 1)
end