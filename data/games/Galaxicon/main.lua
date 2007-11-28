
-- Galaxicon
player = {

	new = function(self)
		o = {}
		setmetatable(o, self)
		self.__index = self
		return o
	end,

	x = 500, 
	y = 350,
	xspeed = 0, 
	yspeed = 0, 
	image = nil, 
	
	render = function(self)
		love.graphics:draw(self.image, self.x, self.y);
	end
}



enemy = {

	new = function(self)
		o = {}
		setmetatable(o, self)
		self.__index = self
		return o
	end,

	x = 500, 
	y = 350,
	xspeed = 0, 
	yspeed = 0, 
	image = nil, 
	
	render = function(self)
		love.graphics:draw(self.image, self.x, self.y);
	end
}

player1 = player:new();
enemies = {};

num_enemies = 100;

main = {
	
	load = function()
	
		-- Images
		player.image = love.objects:newImage("img/player.gif");
		enemy.image = love.objects:newImage("img/enemy.gif");
		
		for i=1, num_enemies do
			enemies[i] = enemy:new();
			enemies[i].y = -math.random(5000) - 200;
			enemies[i].x = math.random(1000) + 100;
		end
		
	end,
	
	update = function(dt)
	
		local thrust = 500;

		if love.keyboard:isDown(love.key_right) then
			player1.xspeed = player1.xspeed + (thrust * dt);
		end
		
		if love.keyboard:isDown(love.key_left) then		
			player1.xspeed = player1.xspeed - (thrust * dt);
		end
		
		if love.keyboard:isDown(love.key_up) then		
			player1.yspeed = player1.yspeed - (thrust * dt);
		end
		
		if love.keyboard:isDown(love.key_down) then		
			player1.yspeed = player1.yspeed + (thrust * dt);
		end
		
		-- Move player
		player1.x = player1.x + (dt * player1.xspeed);
		player1.y = player1.y + (dt * player1.yspeed);	
		
		for i=1, num_enemies do
		
			if enemies[i].y < 1200 then
				enemies[i].y = enemies[i].y + 200 * dt;
			else
				enemies[i].y = -200;
			end
		end
	
	end,
	
	render = function()
	
		player1:render();

		for i=1, num_enemies do
			enemies[i]:render();
		end

	
	end

}