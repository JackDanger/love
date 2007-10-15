
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

		-- Images
		game:addImage('image01', 'pig.gif');
		game:addImage('eiffel', 'img/eiffel.jpg');
		game:addImage('hamster', 'hamster.gif');
		game:addImage('mortis', 'mortis.gif');
			
		-- Sound
		-- This works, but is annoying when restarting all the time.
		--local s = game:addSound("intermission", "data/intermission.mp3");
		--s:play();
			
	end, 
	
	update = function(dt)

		local thrust = 500;

		if keyboard:isDown(LOVE_KEY_RIGHT) then
			player.xspeed = player.xspeed + (thrust * dt);
		end
		
		if keyboard:isDown(LOVE_KEY_LEFT) then		
			player.xspeed = player.xspeed - (thrust * dt);
		end
		
		if keyboard:isDown(LOVE_KEY_UP) then		
			player.yspeed = player.yspeed - (thrust * dt);
		end
		
		if keyboard:isDown(LOVE_KEY_DOWN) then		
			player.yspeed = player.yspeed + (thrust * dt);
		end
		
		-- Move player
		player.x = player.x + (dt * player.xspeed);
		player.y = player.y + (dt * player.yspeed);
		
		-- Update color
	
		
	end,
	
	render = function()

		local eiffel = game:getImage('eiffel');
		eiffel:render(0,0);

		local img = game:getImage('image01');
		img:render(math.floor(player.x), math.floor(player.y));
		
		game:getImage('mortis'):render(mouse:getX(), mouse:getY());
		
		--game:setColor(0xff0668);
		game:print(20, 40, "Lua makes french pig fly @ (" .. math.floor(player.x) .. "," .. math.floor(player.y) .. ")");
				
		--game:setColor(255,255,0);
		game:print(20,70, "Last keypress: " .. lastkey);
		
		--game:setColor(255,0,0);
		game:print(20,100, "Mouse @ (" .. mouse:getX() .. "," .. mouse:getY() .. ")");
		
		--game:setColor(255,0,255);
		game:print(20,130, "Last mousepress: " .. lastmouse);
		
	end, 
	
	keypressed = function(key)
		
		lastkey = "some key with code " .. key;
		
		if key == LOVE_KEY_LEFT then lastkey = "left" end
		if key == LOVE_KEY_RIGHT then lastkey = "right" end
		if key == LOVE_KEY_UP then lastkey = "up" end
		if key == LOVE_KEY_DOWN then lastkey = "down" end
		
			
	end,
	
	keyreleased = function(key)

	end,
	
	mousepressed = function(x, y, button)
		lastmouse = "("..x..","..y..")";
		
		
		if button == LOVE_MOUSE_LEFT then
			lastmouse = lastmouse .. " LEFT";
		elseif button == LOVE_MOUSE_MIDDLE then 
			lastmouse = lastmouse .. " MIDDLE";
		elseif button == LOVE_MOUSE_RIGHT then 
			lastmouse = lastmouse .. " RIGHT";
		elseif button == LOVE_MOUSE_WHEELUP then 
			lastmouse = lastmouse .. " WHEELUP";
		elseif button == LOVE_MOUSE_WHEELDOWN then 
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