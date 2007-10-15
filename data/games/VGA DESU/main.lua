

cloud =
{
	new = function(self)
		o = {}
		setmetatable(o, self)
		self.__index = self
		return o
	end,
	image = nil, 
	a = 0, 
	x = 0, 
	y = 0,
	sin = 0, 
	
	update = function(self, dt)
	
		self.a = self.a + (3 * dt);
		self.sin = 5 * math.sin(self.a);
		
	end, 
	
	render = function(self)
		gl:pushMatrix();
		gl:translate(self.x, self.y);
		gl:pushMatrix();
		self.image:render(-256, -128 + self.sin);
		gl:popMatrix();	
		gl:popMatrix();	
	end
}

main = {
	
	load = function()
	
		game:queueDisplayMode(640, 480, 32, false);
	
		game:addColor("yoga-blue", 0x2ca9fa)
		game:setBackground("yoga-blue");
		
		cloud.image = game:addImage("cloud", "cloud.png");
		
		cloud.x = 640/2;
		cloud.y = 480/2;

		
	end, 
	
	update = function(dt)
		cloud:update(dt);
	end, 
	
	render = function()
		cloud:render();	
		
		game:drawString(50, 50, "VGA (" .. game:getDisplayWidth() .. "x" .. game:getDisplayHeight() .. ") Ne? ^-^)/");
	end

}