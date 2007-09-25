
nekochan  = "";

main = {
	
	init = function()

		-- variables
		font = { big = love.objects:newDefaultFont(20), small = love.objects:newDefaultFont(7) };
		color = { black = love.objects:newColor(0x000000), white = love.objects:newColor(0xFFFFFF), shiznet = love.objects:newColor(0xF60968) };
		
		love.graphics:setBackground(color["white"]);
		love.graphics:setColor(color["black"]);
		
		horseshit = 0;
		
		
		-- music / sound
		game:addSound("phaser", "phaser.wav");
		phazr = game:getSound("phaser");
		mus = game:addMusic("so cold", "test.mp3");
		--mus:play(1);
		
	end,
	update = function(dt)
	
		horseshit = horseshit + 5 * dt;
		game:setRotation(horseshit);
		
	end,
	render = function()

		love.graphics:setColor(color["black"]);
		love.graphics:setFont(font["big"]);
		love.graphics:drawText("Truly the best game ever. Because: it has a lot of shapes (loel)\nPress S to shoot and M to start/stop the music\n(arrow keys for valuum desu)!", 10, 35);
			  
		love.graphics:setColor(color["shiznet"]);
		--gl:enable("MULTISAMPLE");
		
		love.graphics:drawLine(50,200,150,200,horseshit);
		love.graphics:drawTriangle(260, 200, 100, 100, horseshit, 5);
		love.graphics:drawRectangle(470, 200, 100, 100, horseshit, 5);
		love.graphics:drawCircle(680, 200, 60, 10, horseshit);
		
		love.graphics:fillTriangle(260, 400, 100, 100, horseshit);
		love.graphics:fillRectangle(470, 400, 100, 100, horseshit);
		love.graphics:fillCircle(680, 400, 60, 60);
		--gl:disable("MULTISAMPLE");
		
		love.graphics:setColor(color["black"]);
		love.graphics:setFont(font["small"]);
		love.graphics:drawText("drawLine(50,200,150,200,horseshit)", 10, 300);
		love.graphics:drawText("drawTriangle(260, 200, 100, 100, horseshit, 5)", 175, 300);
		love.graphics:drawText("drawRect(470,200,100,100, horseshit, 5)", 400, 300);
		love.graphics:drawText("drawCircle(680,200, 60, 10, horseshit)", 615, 300);
		
		love.graphics:drawText("drawTriangle(260, 200, 100, 100, horseshit, 5)", 175, 500);
		love.graphics:drawText("drawRect(470,200,100,100, horseshit, 5)", 400, 500);
		love.graphics:drawText("drawCircle(680,200, 60, 60)", 615, 500);
	end,
	
	keypressed = function(key)

		if key == LOVE_KEY_s then phazr:play(); end
		if key == LOVE_KEY_m then
			if game:pausedMusic() then game:resumeMusic();
			else game:pauseMusic(1); end
		end
		if key == LOVE_KEY_x then game:stopMusic(); end
		
		if key == LOVE_KEY_UP then
			game:setVolumeMusic(game:getVolumeMusic() + 10);
		elseif key == LOVE_KEY_DOWN then
			game:setVolumeMusic(game:getVolumeMusic() - 10);
		end
		
	end,

} -- main


horseshit = 0;