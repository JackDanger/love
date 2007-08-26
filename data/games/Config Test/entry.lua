

hamster_ai = {

	deg = 0,
	speed = 0,
	

	init = function(this)
		this:setSprite("image-hamster");
		this:setPosition(200,200);
	end, 
	
	update =  function(this, dt)
	
		hamster_ai.deg = hamster_ai.deg + hamster_ai.speed * dt;
		this:setOrientation(hamster_ai.deg);
	
	end

}

time = 0;
max_time = 2;

main = {
	
	init = function()
	
	
		-- Include section
		game:include("state1.lua");
		--game:include("state2.lua");
	
		img = game:addImage("image-hamster", "mega-sun.png");
		
		aham = game:addActor("actor-hamster");
		local alive = aham:addState("alive", "hamster_ai");
		aham:setState(alive);

		game:addColor("yoga", 0x59bbfa);
		game:setBackground("yoga");
		
		-- Add some states
		game:addState("state1");
		game:addState("state2");
		
		
			
	end, 
	
	update = function(dt)
	
		hamster_ai.speed = 20;
	
		time = time + dt;
		if time > max_time then 
			game:setState("state1"); 
			time = time - max_time;
		end
	
	end,
	
	render = function()
	
		game:drawString(150, 50, "Sun dimensions: " .. img:getWidth() .. " x " .. img:getHeight() .. ".");
	
	end

} -- main
