
nekochan  = "";

main = {
	
	init = function()

		game:addFont("big", 20);
		game:addFont("small", 10);
		
        game:addColor("black", 0, 0, 0);
		game:addColor("shiznet", 0xF60968);
	    game:setColor("shiznet");
	    game:setBackground(game:addColor("white", 255, 255, 255));
		text:setColor("black");

		vec1 = love.new_Vextor(500, 600);
		vec2 = love.new_Vextor(13, 37);
		
		vec3 = vec1 + vec2;
		dot = vec1 * vec2;
		vec3:normalize();
		
		print("\nVec3: " .. vec3:getLength() .. "\n");
		horseshit = 0;
		

		game:addSound("phaser", "phaser.wav");
		phazr = game:getSound("phaser");
		mus = game:addMusic("so cold", "test.mp3");

		mus:play(1);
		
	end,
	update = function(dt)
	
		horseshit = horseshit + 5 * dt;
	
	    --local fag = game:getActor("test");
	    --fag:setPosition(horseshit,100);
	    --fag:setOrientation(horseshit);
		
		game:setRotation(horseshit);
		
	end,
	render = function()


	
		text:setFont("big");
        text:print(10,35, "Truly the best game ever. Because: it has a lot of shapes (loel)\nPress S to shoot and M to start/stop the music (arrow keys for valuum desu)!");
			  
		gl:enable("MULTISAMPLE");
		game:drawLine(50,200,150,200);
		game:drawTriangle(260, 200, 100, 100, 5);
		--game:drawRect(260,200,100,100,5);
		game:fillTriangle(470,200,100,100);
		--game:fillRect(470,200,100,100);
		game:drawCircle(680,200,60);
		game:fillCircle(890,200,60,36);
		gl:disable("MULTISAMPLE");
			   
		game:setColor("shiznet");
		text:setFont("small");
        text:print(10,300, "drawLine(50,200,150,200)");
		text:print(175,300, "drawTriangle(260,200,100,100,5)");
		text:print(400,300, "fillTriangle(470,200,100,100)");
		text:print(615,300, "drawCircle(680,200,60)");
		text:print(820,300, "fillCircle(890,200,60,36)");
               
        --game:getImage("zero"):render(300,300);
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