
systems = {}

current = 1;

main = 
{
	init = function()
	
		local part1 = love.objects:newImage("part1.png");
		local nyu = love.objects:newImage("nyu.png");
		local cloud = love.objects:newImage("cloud.png");
		local square = love.objects:newImage("square.png");
		local c = love.objects:newImage("c.png");
		local arrow = love.objects:newImage("arrow.png");
		local thing = love.objects:newImage("thing.png");
		
	
	
		clr = game:addColor("clr", 80, 80, 80);
		game:setColor(clr);
	
		-- System start
		local p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(100);
		p:setStartSpeed(300, 400);
		p:setParticleSize(2, 1);
		p:addColor(255, 255, 255, 255);
		p:addColor(58, 128, 255, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(1);
		p:setParticleLifetime(1);
		p:setDirection(0, 360);
		p:setTangentialAcc(1000);
		p:setAutostart(false);
		p:setRadialAcc(-2000);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(nyu);
		p:setParticlesPerSecond(300);
		p:setStartSpeed(200, 300);
		p:setParticleSize(1, 2);
		p:addColor(255, 255, 255, 255);
		p:addColor(255, 0, 126, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(1);
		p:setParticleLifetime(3);
		p:setDirection(0, 360);
		p:setAutostart(false);
		p:setParticleSpin(90, 180);
		table.insert(systems, p);
		p:setRadialAcc(-200, -300);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(cloud);
		p:setParticlesPerSecond(300);
		p:setStartSpeed(200, 250);
		p:setParticleSize(1, 1);
		p:addColor(16, 81, 229, 255);
		p:addColor(176, 16, 229, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(1);
		p:setParticleLifetime(2);
		p:setDirection(170, 190);
		p:setAutostart(false);
		p:setParticleSpin(300, 800);
		p:setGravity(100, 200);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(square);
		p:setParticlesPerSecond(300);
		p:setStartSpeed(200, 350);
		p:setParticleSize(1, 2);
		p:addColor(240, 3, 176, 255);
		p:addColor(204, 240, 3, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(1);
		p:setParticleLifetime(2);
		p:setDirection(90);
		p:setAutostart(false);
		p:setParticleSpin(300, 800);
		--p:setGravity(-100, -200);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(c);
		p:setParticlesPerSecond(500);
		p:setStartSpeed(200, 350);
		p:setParticleSize(0.5, 2);
		p:addColor(255, 255, 255, 255);
		p:addColor(58, 128, 255, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(1);
		p:setParticleLifetime(1);
		p:setDirection(270, 90);
		p:setAutostart(false);
		p:setParticleSpin(300, 800);
		--p:setGravity(-100, -200);
		p:setRadialAcc(-400, -500);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(1000);
		p:setStartSpeed(300, 400);
		p:setParticleSize(2, 1);
		p:addColor(220, 105, 20, 255);
		p:addColor(194, 30, 18, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(0.1);
		p:setParticleLifetime(0.2);
		p:setDirection(0, 360);
		p:setTangentialAcc(1000);
		p:setAutostart(false);
		p:setRadialAcc(-2000);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(1000);
		p:setStartSpeed(100, 700);
		p:setParticleSize(1, 2);
		p:addColor(220, 105, 20, 255);
		p:addColor(194, 30, 18, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(0.1);
		p:setParticleLifetime(0.2);
		p:setDirection(0, 360);
		p:setTangentialAcc(1000);
		p:setAutostart(false);
		--p:setRadialAcc(-2000);
		table.insert(systems, p);
		-- System end
	
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(2000);
		p:setStartSpeed(100, 700);
		p:setParticleSize(1, 2);
		p:addColor(220, 105, 20, 255);
		p:addColor(194, 30, 18, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(0.5);
		p:setParticleLifetime(0.5);
		p:setDirection(0, 360);
		p:setTangentialAcc(1000);
		p:setAutostart(false);
		--p:setRadialAcc(-2000);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(arrow);
		p:setParticlesPerSecond(500);
		p:setStartSpeed(200, 300);
		p:setParticleSize(0.5, 2);
		p:addColor(255, 255, 255, 255);
		p:addColor(58, 128, 255, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(1);
		p:setParticleLifetime(1);
		p:setDirection(0, 360);
		p:setAutostart(false);
		p:setParticleSpin(300, 800);
		p:setGravity(700, 800);
		p:setRadialAcc(100, 200);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(arrow);
		p:setParticlesPerSecond(100);
		p:setStartSpeed(200, 300);
		p:setParticleSize(1, 2.0);
		p:addColor(24, 19, 116, 255);
		p:addColor(58, 128, 255, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(1);
		p:setParticleLifetime(1.5);
		p:setDirection(180);
		p:setAutostart(false);
		p:setParticleSpin(800, 1000);
		--p:setGravity(700, 800);
		--p:setRadialAcc(100, 200);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(200);
		p:setStartSpeed(300, 400);
		p:setParticleSize(1, 2);
		p:addColor(255, 255, 255, 255);
		p:addColor(58, 128, 255, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(3);
		p:setParticleLifetime(2);
		p:setDirection(0, 360);
		p:setTangentialAcc(2000);
		p:setAutostart(false);
		p:setRadialAcc(-5000);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(thing);
		p:setParticlesPerSecond(20);
		p:setStartSpeed(50, 100);
		p:setParticleSize(1, 0);
		p:addColor(255, 255, 255, 255);
		p:addColor(58, 128, 255, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(5);
		p:setParticleLifetime(4);
		p:setDirection(0, 360);
		--p:setTangentialAcc(2000);
		p:setAutostart(false);
		p:setParticleSpin(-1000, 1000);
		--p:setRadialAcc(-5000);
		table.insert(systems, p);
		-- System end
		
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(100);
		p:setStartSpeed(50, 100);
		p:setParticleSize(1, 1);
		p:addColor(255, 255, 255, 255);
		p:addColor(58, 128, 255, 255, 1);
		p:addColor(194, 30, 18, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(5);
		p:setParticleLifetime(4);
		p:setDirection(0, 360);
		--p:setTangentialAcc(2000);
		p:setAutostart(false);
		p:setParticleSpin(-1000, 1000);
		p:setRadialAcc(-30);
		table.insert(systems, p);
		-- System end
		
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(300);
		p:setStartSpeed(300, 400);
		p:setParticleSize(2, 1);
		p:addColor(220, 105, 20, 0, 1);
		p:addColor(58, 128, 255, 255, 1);
		p:addColor(194, 30, 18, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(2);
		p:setParticleLifetime(2);
		p:setDirection(0, 360);
		p:setTangentialAcc(1000);
		p:setAutostart(false);
		p:setRadialAcc(-2000);
		table.insert(systems, p);
		-- System end
		
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(300);
		p:setStartSpeed(300, 400);
		p:setParticleSize(2, 1);
		p:addColor(220, 105, 20, 0, 1);
		p:addColor(58, 128, 255, 255, 1);
		p:addColor(194, 30, 18, 0, 0);
		p:setPosition(400, 300);
		p:setLifetime(2);
		p:setParticleLifetime(2);
		p:setDirection(270);
		p:setTangentialAcc(1000);
		p:setAutostart(false);
		p:setRadialAcc(-2000);
		table.insert(systems, p);
		-- System end
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(100);
		p:setStartSpeed(30);
		p:setParticleSize(2, 1);
		p:addColor(220, 105, 20, 0, 1);
		p:addColor(58, 128, 255, 255, 1);
		p:addColor(194, 30, 18, 0, 1);
		p:addColor(255, 255, 255, 255, 1)
		p:addColor(207, 20, 108, 0, 0);	
		p:setPosition(400, 300);
		p:setLifetime(5);
		p:setParticleLifetime(5);
		p:setDirection(0, 360);
		--p:setTangentialAcc(10);
		p:setAutostart(false);
		--p:setRadialAcc(-20);
		table.insert(systems, p);
		-- System end
		
		
		-- System start
		p = love.objects:newParticleSystem();
		p:setSprite(part1);
		p:setParticlesPerSecond(3000);
		p:setStartSpeed(200);
		p:setParticleSize(2, 1);
		p:addColor(220, 105, 20, 0, 1);
		p:addColor(58, 128, 255, 0, 1);
		p:addColor(255, 255, 255, 255, 1)
		p:addColor(207, 20, 108, 0, 0);	
		p:setPosition(400, 300);
		p:setLifetime(0.1);
		p:setParticleLifetime(1);
		p:setDirection(0, 360);
		--p:setTangentialAcc(200);
		p:setAutostart(false);
		--p:setRadialAcc(-150);
		table.insert(systems, p);
		-- System end
					
	end, 
	
	update = function(dt)
		
		if mouse:isDown(LOVE_MOUSE_LEFT) then 
			if systems[current]:isDead() then
				systems[current]:reset();
			end
			systems[current]:setPosition(mouse:getX(), mouse:getY());
		end
		
		systems[current]:update(dt);

	end, 
	
	render = function()
		systems[current]:render();
		
		game:drawString(30, 570, "System: [" .. current .. "/"..table.getn(systems).."] - " .. systems[current]:getNumParticles() .. " particles.");
		game:drawString(30, 540, "Click: spawn particles. Mousewheel: change system.");
		
	end, 
	
	mousepressed = function(x, y, button)

		if button == love.mouse_left then 
			systems[current]:reset();
		end
		
		if button == love.mouse_wheelup then
			current = current + 1;
			if current > table.getn(systems) then current = table.getn(systems) end;
		end
		
		if button == love.mouse_wheeldown then
			current = current - 1;
			if current < 1 then current = 1 end;
		end
		
	end
}