
--
-- Jetpack
-- Created: 12.06.07
--

actorscript = {

	init = function(this)
		this:setSprite("jetpack");
		this:setPosition(500,240);
	end
	
	-- i have no intention of overwriting the built-in update function
}

--this doesn't work right now, but I'm working on it

particlescript = {

	init = function(this)
		this:setLife(0.3);
		this:setVelocity(0,200);
		this:setSprite("particle");
		this:setPosition(50,50);
	end

}

main = {

	init = function()
		
		-- font and color
		game:addColor("white", 0xFFFFFF);
		text:setColor("white");
		
		-- images
		game:addImage("jetpack", "jetpack.png");
		game:addImage("particle", "particle.png");
		
		-- particle emitter
		emitter = game:addParticleEmitter("emitter", 0.05);
		emitter:setPosition(50,50);
		blue = emitter:addParticle("blue", "particlescript");
		--blue:setLife(0.3);
		--blue:setVelocity(0,200);
		--blue:setSprite("particle");
		
		-- actors
		actor = game:addActor("actor", "actorscript");
	
	end,
	
	update = function(dt)
	
		emitter:setPosition(actor:getX(), actor:getY() + 20);
		
		if actor:getXAcceleration() == 0 then
			if actor:getXVelocity() > 0 then
				actor:setXVelocity(actor:getXVelocity() - (200 * dt));
				if actor:getXVelocity() < 0 then actor:setXVelocity(0); end
			elseif actor:getXVelocity() < 0 then
				actor:setXVelocity(actor:getXVelocity() + (200 * dt));
				if actor:getXVelocity() > 0 then actor:setXVelocity(0); end
			end
		end
		
		if actor:getYAcceleration() >= 0 then
			actor:setYAcceleration(98);
		end
	
	end,
	
	render = function()
		text:align(1);
		text:print(10,30,"x: " .. actor:getX() .. "\ny: " .. actor:getY());
		
		text:align(2);
		text:print(1010,30,"use arrow keys\nto move");
	end,
	
	keypressed = function(key)
		
		if key == LOVE_KEY_LEFT then actor:setXAcceleration(-400); end
		if key == LOVE_KEY_RIGHT then actor:setXAcceleration(400); end
		if key == LOVE_KEY_UP then
			actor:setYAcceleration(-200);
			emitter:play();
		end
			
	end,
	
	keyreleased = function(key)
		
		if key == LOVE_KEY_LEFT and actor:getXAcceleration() < 0 then actor:setXAcceleration(0); end
		if key == LOVE_KEY_RIGHT and actor:getXAcceleration() > 0 then actor:setXAcceleration(0); end
		if key == LOVE_KEY_UP then
			actor:setYAcceleration(0);
			emitter:stop();
		end

	end,
}