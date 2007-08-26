player_alive = {

	init = function(this)
		this:setSprite("player");
		this:setPosition(500,300);
	end,
	
	update = function(this, dt)
		this:setOrientation(getangle(this:getX(), mouse:getX(), this:getY(), mouse:getY()) - 90);
		
		if keyboard:isDown(LOVE_KEY_LEFT) or keyboard:isDown(LOVE_KEY_a) then
			this:setXPosition(this:getXPosition() - (200 * dt));
		elseif keyboard:isDown(LOVE_KEY_RIGHT) or keyboard:isDown(LOVE_KEY_d) then
			this:setXPosition(this:getXPosition() + (200 * dt));
		end
		
		if keyboard:isDown(LOVE_KEY_UP) or keyboard:isDown(LOVE_KEY_w) then
			this:setYPosition(this:getYPosition() - (200 * dt));
		elseif keyboard:isDown(LOVE_KEY_DOWN) or keyboard:isDown(LOVE_KEY_s) then
			this:setYPosition(this:getYPosition() + (200 * dt));
		end
	end

}

enemy_alive = {
	
	init = function(this)
		
		this:setSprite("enemy");
		this:setPosition(math.random(50,974),math.random(50,718));
		this:setVelocity(math.random(-20,20),math.random(-20,20));
		
	end

}