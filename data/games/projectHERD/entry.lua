
--
-- projectHERD
-- Created: 19.01.07 (progress is slow...)
--



main = {
	init = function()
	
		--files
		game:addFile("states.lua");
		
		--variables
		score = 0;
		showfan = false;
		
		--resources
		game:addColor("black", 0, 0, 0);
		game:addColor("pink", 0xF60968);
		game:addFont("verdana", 12);
		game:addImage("player", "graphics/player.png");
		game:addImage("enemy", "graphics/enemy.png");
		target = game:addImage("target", "graphics/target.png");
		fan = game:addImage("fan", "graphics/fan.png");
		
		--actors
		ship = game:addActor("ship", "player_alive");

		math.randomseed(os.time());
		enemies = {};
		for count = 1,5 do		
			enemies[count] = game:addActor("enemy" .. count, "enemy_alive");
		end
		
		--init (true init etc etc)
		game:setBackground(game:addColor("white", 255, 255, 255));
		text:setColor("pink");
		text:setFont("verdana");
		
	end,
	
	update = function(dt)
		
		if showfan then
		end
		
	end,
	
	render = function()
		
		target:render(mouse:getX() - (target:getWidth() / 2), mouse:getY() - (target:getHeight() / 2));
		if showfan then fan:render(ship:getX(), ship:getY()); end
		
		text:align(2); --align right
		text:print(ship:getX(), ship:getY(), score);
		
		text:print(500,300,"X");
	
	end,
	
	mousepressed = function(x, y, button)
		if button == LOVE_MOUSE_LEFT then showfan = true; end
	end,
	
	mousereleased = function(x, y, button)
		if button == LOVE_MOUSE_LEFT then showfan = false; end
	end

}




--gets the angle between two points
getangle = function(x1, x2, y1, y2)
	dx = x1 - x2;
	dy = y1 - y2;
	angle = 0;
	
	if dx == 0.0 then
		if dy == 0 then angle = 0;
		elseif dy > 0 then angle = math.pi / 2;
		else angle = math.pi * 3 / 2; end
	elseif dy == 0 then
		if dx > 0 then angle = 0;
		else angle = math.pi; end
	else
		if dx < 0 then angle = math.atan(dy/dx) + math.pi;
        elseif dy < 0 then angle = math.atan(dy/dx) + (2 * math.pi);
        else angle = math.atan(dy/dx); end
	end
	
	--convert to degrees
    angle = angle * 180 / math.pi;
    
    return angle;
end