-- Tutorial 1: Hamster Ball
-- Add an image to the game and move it around using the arrow keys.

main = {
	
	load = function()
	
		ham = love.objects:newImage("hamster.gif");
		
		x = 50;
		y = 50;
		speed = 100;
		
	end,
	
	update = function(dt)
	
		if keyboard:isDown(LOVE_KEY_RIGHT) then
			x = x + (speed * dt);
		elseif keyboard:isDown(LOVE_KEY_LEFT) then
			x = x - (speed * dt);
		end
		
		if keyboard:isDown(LOVE_KEY_DOWN) then
			y = y + (speed * dt);
		elseif keyboard:isDown(LOVE_KEY_UP) then
			y = y - (speed * dt);
		end
	
	end,
	
	render = function()
	
		ham:render(x,y);
		
	end

} -- main
