
-- LOVE 0.x Test Game

player = {

	x = 500, 
	y = 350,
	xspeed = 0, 
	yspeed = 0
}

lastkey = "None";
lastmouse = "None";

main = {
	
	load = function()

		--game:queueDisplayMode(1024,768,32,true);
		love.graphics:setFont(love.objects:newDefaultFont(20));

		-- Images
		img = love.objects:newImage('pig.gif');
		eiffel = love.objects:newImage('img/eiffel.jpg');
		hamster = love.objects:newImage('hamster.gif');
		mortis = love.objects:newImage('mortis.gif');
			
		-- Sound
		-- This works, but is annoying when restarting all the time.
		--local s = game:addSound("intermission", "data/intermission.mp3");
		--s:play();
			
	end, 
	
	update = function(dt)

		local thrust = 500;

		if love.keyboard:isDown(love.key_right) then
			player.xspeed = player.xspeed + (thrust * dt);
		end
		
		if love.keyboard:isDown(love.key_left) then		
			player.xspeed = player.xspeed - (thrust * dt);
		end
		
		if love.keyboard:isDown(love.key_up) then		
			player.yspeed = player.yspeed - (thrust * dt);
		end
		
		if love.keyboard:isDown(love.key_down) then		
			player.yspeed = player.yspeed + (thrust * dt);
		end
		
		-- Move player
		player.x = player.x + (dt * player.xspeed);
		player.y = player.y + (dt * player.yspeed);
		
		-- Update color
	
		
	end,
	
	render = function()

		eiffel:render(0,0);

		img:render(math.floor(player.x), math.floor(player.y));
		
		mortis:render(love.mouse:getX(), love.mouse:getY());
		
		love.graphics:setColor(0xff0668);
		love.graphics:drawText("Lua makes french pig fly @ (" .. math.floor(player.x) .. "," .. math.floor(player.y) .. ")", 20, 40);
				
		love.graphics:setColor(255,255,0);
		love.graphics:drawText("Last keypress: " .. lastkey, 20, 70);
		
		love.graphics:setColor(255,0,0);
		love.graphics:drawText("Mouse @ (" .. love.mouse:getX() .. "," .. love.mouse:getY() .. ")", 20, 100);
		
		love.graphics:setColor(255,0,255);
		love.graphics:drawText("Last mousepress: " .. lastmouse, 20, 130);
		
	end, 
	
	keypressed = function(key)
		
		lastkey = "some key with code " .. key;
		
		if key == love.key_left then lastkey = "left" end
		if key == love.key_right then lastkey = "right" end
		if key == love.key_up then lastkey = "up" end
		if key == love.key_down then lastkey = "down" end
		
			
	end,
	
	keyreleased = function(key)

	end,
	
	mousepressed = function(x, y, button)
		lastmouse = "("..x..","..y..")";
		
		
		if button == love.mouse_left then
			lastmouse = lastmouse .. " LEFT";
		elseif button == love.mouse_middle then 
			lastmouse = lastmouse .. " MIDDLE";
		elseif button == love.mouse_right then 
			lastmouse = lastmouse .. " RIGHT";
		elseif button == love.mouse_wheelup then 
			lastmouse = lastmouse .. " WHEELUP";
		elseif button == love.mouse_wheeldown then 
			lastmouse = lastmouse .. " WHEELDOWN";
		end
		
	end,

	mousereleased = function(x, y, button)

	end
	
} -- main

defimage = {

	init = function(this)
		print("RED: " .. this:getY() .. " \n");
	end
}