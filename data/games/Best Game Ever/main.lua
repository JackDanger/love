
nekochan  = "";

main = {
	
	load = function()

		-- variables
		font = { standard = love.objects:newDefaultFont(12), big = love.objects:newDefaultFont(20), small = love.objects:newDefaultFont(7), image = love.objects:newImageFont(love.objects:newImage("letters.png"), 15, 15, "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?") };
		color = { black = love.objects:newColor(0x000000), white = love.objects:newColor(0xFFFFFF), shiznet = love.objects:newColor(0xF60968) };
		
		love.graphics:setBackground(color["white"]);
		love.graphics:setColor(color["black"]);
		
		horseshit = 0;
		
		menu = love.objects:newMenu();
		menu:setFont(font["standard"]);
		menu:setColor(color["black"]);
		menu:setBorderColor(color["black"]);
		menu:setBorderSize(2);
		menu:align(love.align_left);
		menu:setBackgroundColor(color["shiznet"]);
		--menu:setBackground(love.objects:newImage("zero.png"));
		--menu:setFont(font["small"]);
		menu:setSize(550,200);
		menu:setPosition(200,200);
		menu:setPadding(10);
		menu:setSpacing(3);
		menu:addLabel("THIS IS A MENU");		
		menu:addButton("BUNNY_BUTT", "Click Me!");
		menu:addTextField("TEXT_FILD", "Edit this text, plx!", 200);
		drop = menu:addDropDown("DROP YOUR PANTS");
		drop:add("one");
		drop:add("two");
		drop:add("four");
		nested = menu:addMenu(love.menu_horizontal);
		nested:addLabel("Nested menu:  ");
		rad_sparta = nested:addRadioButton("RAD_SPARTA", "Sparta (custom image)");
		rad_sparta:setMarked(true);
		rad_sparta:setDefaultImage(love.objects:newImage("default.png"));
		rad_sparta:setMarkedImage(love.objects:newImage("marked.png"));
		rad_not = nested:addRadioButton("RAD_NOT", "No Sparta (default ugly thing)");
		nested:adjustSize();
		nested:adjustContent();
		menu:addMultilineLabel("Just wanted to let you know that the previous example (the one with the radio buttons) uses the event system. GUIchan has a built-in group-system for dealing with radio buttons (seeing as you are only supposed to be able to select one at a time), but I thought that it would just add one more value to keep track of and doing it manually yields more control. ^-^");
		menu:adjustSize();
		
		love.gui:add(menu);
		
	end,
	update = function(dt)
	
		horseshit = horseshit + 5 * dt;
		--game:setRotation(horseshit);
		
	end,
	render = function()

		love.graphics:setColor(color["black"]);
		--love.graphics:setFont(font["big"]);
		--love.graphics:drawText("Truly the best game ever. Because: it has a lot of shapes (loel)\nPress S to shoot and M to start/stop the music\n(arrow keys for valuum desu)!", 10, 35);
		--love.graphics:setColor(color["white"]);
		love.graphics:setFont(font["image"]);
		love.graphics:drawText("TRULY THE BEST GAME EVER.\nBECAUSE: IT HAS A LOT OF SHAPES (LOEL)\nTHIS IS AN IMAGE FONT, BTW!", 10, 35);
			  
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
		
		love.graphics:setFont(font["big"]);
		love.graphics:setColor(color["shiznet"]);
		test = love.graphics:getColor();
		love.graphics:drawText("THIS IS TEST: " .. test:getRed() .. "." .. test:getGreen() .. "." .. test:getBlue(), 10, 500);
	end,
	
	keypressed = function(key)
		
	end,
	
	event = function(e)
		
		if e:getType() == love.event_message then
			print("This baby just recieved a MessageEvent (tm). Message reads: " .. e:getMessage() .. "\n")
		elseif e:getType() == love.event_gui then
			if e:getName() == "RAD_SPARTA" then rad_not:setMarked(false);
			elseif e:getName() == "RAD_NOT" then rad_sparta:setMarked(false); end
			print("This baby just received a GUIEvent (bn). GUIname is: " .. e:getName() .. "\n")
		end
	end

} -- main


horseshit = 0;