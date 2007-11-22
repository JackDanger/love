-- Tutorial 1: Hamster Ball
-- Add an image to the game and move it around using the arrow keys.

main = {
	
	load = function()
	
		ham = love.objects:newImage("hamster.gif");
		
		x = 50;
		y = 50;
		speed = 200;
	
	end,
	
	update = function(dt)
	
		if love.keyboard:isDown(love.key_right) then
			x = x + (speed * dt);
		elseif love.keyboard:isDown(love.key_left) then
			x = x - (speed * dt);
		end
		
		if love.keyboard:isDown(love.key_down) then
			y = y + (speed * dt);
		elseif love.keyboard:isDown(love.key_up) then
			y = y - (speed * dt);
		end
	
	end,
	
	render = function()
	
		love.graphics:draw(ham, x, y);
	
	end

} -- main
