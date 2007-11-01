
nekochan  = "";

main = {
	
	load = function()

		-- variables
		font = { standard = love.objects:newDefaultFont(12), big = love.objects:newDefaultFont(20), small = love.objects:newDefaultFont(7), image = love.objects:newImageFont(love.objects:newImage("letters.png"), 15, 15, "ABCDEFGHIJKLMNOPQRSTUVWXYZ.,!?") };
		color = { black = love.objects:newColor(0x000000), white = love.objects:newColor(0xFFFFFF), shiznet = love.objects:newColor(0xF60968), halfshiz = love.objects:newColor(0xF60968) };
		color["halfshiz"]:setAlpha(200);
		
		anim = love.objects:newAnimatedColor(love.mode_loop);
		anim:addColor(color["black"], 0.1);
		anim:addColor(color["white"], 0.1);
		anim:play();
		
		love.graphics:setBackground(color["white"]);
		love.graphics:setColor(color["black"]);
		
		menux = -1;
		menuy = -1;
		
		horseshit = 0;
		
		menu = love.objects:newMenu();
		menu:setFont(font["standard"]);
		menu:setColor(color["black"]);
		menu:setBorderColor(color["black"]);
		menu:setBorderSize(2);
		menu:align(love.align_left);
		--menu:setBackgroundColor(color["halfshiz"]);
		menu:setBackgroundColor(anim);
		--menu:setBackground(love.objects:newImage("zero.png"));
		--menu:setFont(font["small"]);
		menu:setSize(650,200);
		menu:setPosition(100,80);
		menu:setPadding(10);
		menu:setSpacing(5);
		
		local label = menu:addLabel("THIS IS A MENU (SIEZURE ED.)");
		label:setColor(color["shiznet"]);
		
		button = menu:addButton("BUTTON", "Click me to change the menu label!");
		button:setBorderSize(1);
		button:setBackgroundColor(color["halfshiz"]);
		button:setHoverBackgroundColor(color["shiznet"]);
		--button:setPressedBackgroundColor(color["white"]);
		
		local nested = menu:addMenu(love.menu_horizontal);
		nested:setFont(font["small"]);
		spartbutton =nested:addButton("SPAR_BUTTON", "Sparta!");
		-- spartbutton:setFont(font["small"]) -- TODO
		spartbutton:setDefaultImage(love.objects:newImage("button_default.png"));
		spartbutton:setHoverImage(love.objects:newImage("button_hover.png"));
		spartbutton:setPressedImage(love.objects:newImage("button_press.png"));
		spartbutton:adjustSize();
		nested:adjustSize();
		
		textfield = menu:addTextField("TEXT_FIELD", "Or press <enter> here.", 200);
		
		drop = menu:addDropDown("DROP YOUR PANTS");
		--drop:setButton(love.objects:newImage("dropdown.png"));
		--drop:setButtonPressed(love.objects:newImage("dropdown_pressed.png"));
		drop:add("one");
		drop:add("two");
		drop:add("four");
		drop:setBackgroundColor(color["shiznet"]);
		
		nested = menu:addMenu(love.menu_horizontal);
		--nested:setFont(font["image"]);
		nested:addLabel("NESTED MENU:  ");
		rad_sparta = nested:addRadioButton("RAD_SPARTA", "SPARTA");
		rad_sparta:setMarked(true);
		rad_sparta:setDefaultImage(love.objects:newImage("default.png"));
		rad_sparta:setMarkedImage(love.objects:newImage("marked.png"));
		rad_not = nested:addRadioButton("RAD_NOT", "NOT SPARTA");
		nested:adjustSize();
		nested:adjustContent();
		
		nested = menu:addMenu(love.menu_horizontal);
		--nested:setFont(font["image"]);
		nested:addLabel("ANOTHER NESTED MENU:  ");
		check_sparta = nested:addCheckBox("CHECK_SPARTA", "SPARTA");
		check_sparta:setMarked(true);
		check_sparta:setDefaultImage(love.objects:newImage("unchecked.png"));
		check_sparta:setMarkedImage(love.objects:newImage("checked.png"));
		check_not = nested:addCheckBox("CHECK_NOT", "NOT SPARTA");
		nested:adjustSize();
		nested:adjustContent();
		
		menu:addMultilineLabel("Just wanted to let you know that the previous example (the one with the radio buttons) uses the event system. GUIchan has a built-in group-system for dealing with radio buttons (seeing as you are only supposed to be able to select one at a time), but I thought that it would just add one more value to keep track of and doing it manually yields more control. ^-^\n(ps: you can click and drag this menu around [REMOVED])");
		
		nested = menu:addMenu(love.menu_horizontal);
		nested:setSpacing(5);
		nested:addLabel("Sparta:");
		slider_sparta = nested:addSlider("SLIDER_SPARTA", love.slider_horizontal, 0, 10);
		slider_sparta:setMarkerImage(love.objects:newImage("slider_marker.png"));
		slider_sparta:setBackgroundImage(love.objects:newImage("slider_back.png"));
		slider_sparta:setBorderSize(0);
		slider_sparta:adjustSize();
		slider_sparta_label = nested:addLabel(slider_sparta:getValue(), 20);
		nested:adjustSize();
		nested:adjustContent();
		
		nested = menu:addMenu(love.menu_horizontal);
		nested:setSpacing(5);
		nested:addLabel("Non-Sparta:");
		slider_notsparta = nested:addSlider("SLIDER_NOTSPARTA", love.slider_horizontal, 0, 10, 200, 15);
		--slider_notsparta:setBackgroundColor(color["white"]);
		slider_notsparta:setColor(color["shiznet"]);
		slider_notsparta_label = nested:addLabel(slider_sparta:getValue(), 50);
		nested:adjustSize();
		nested:adjustContent();
		
		list = menu:addListBox("THEY SEE ME LISTING!");
		list:add("this");
		list:add("is");
		list:add("a");
		list:add("list");
		list:add("(also: sparta)");
		list:adjustSize();
		list:setBackgroundColor(color["shiznet"]);
		list:setSelectionColor(color["white"]);
		list:setSelectionBackgroundColor(list:getBackgroundColor());
		
		
		menu:adjustSize();
		
		love.gui:add(menu);
		
	end,
	update = function(dt)
		
		-- update animated colors
		anim:update(dt);
		
		horseshit = horseshit + 5 * dt;
		--game:setRotation(horseshit);
		
		if love.mouse:isDown(love.mouse_left) and menux ~= -1 and menuy ~= -1 and false then
			menu:setX(menu:getX() - (menux - love.mouse:getX()));
			menux = love.mouse:getX();
			
			menu:setY(menu:getY() - (menuy - love.mouse:getY()));
			menuy = love.mouse:getY();
		end
		
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
		--love.graphics:drawText("THIS IS TEST: " .. test:getRed() .. "." .. test:getGreen() .. "." .. test:getBlue(), 10, 500);
	end,
	
	keypressed = function(key)
		
	end,
	
	mousepressed = function(x, y, button)
		
		if button == love.mouse_left and x > menu:getX() and x < menu:getX() + menu:getWidth() and y > menu:getY() and y < menu:getY() + menu:getHeight() then
			menux = x;
			menuy = y;
		end
		
	end,
	
	mousereleased = function(x, y, button)
	
		if button == love.mouse_left then
			menux = -1;
			menuy = -1;
		end
	
	end,
	
	event = function(e)
		
		if e:getType() == love.event_message then
			--print("This baby just recieved a MessageEvent (tm). Message reads: " .. e:getMessage() .. "\n")
		elseif e:getType() == love.event_gui then
			if e:getName() == "RAD_SPARTA" then rad_not:setMarked(false);
			elseif e:getName() == "RAD_NOT" then rad_sparta:setMarked(false);
			elseif e:getName() == "BUTTON" or e:getName() == "TEXT_FIELD" then
				label:setCaption(textfield:getText());
				label:adjustSize();
			elseif e:getName() == "SLIDER_SPARTA" then
				slider_sparta_label:setCaption(math.floor(slider_sparta:getValue()));
			elseif e:getName() == "SLIDER_NOTSPARTA" then
				slider_notsparta_label:setCaption(slider_notsparta:getValue());
			end
			--print("This baby just received a GUIEvent (bn). GUIname is: " .. e:getName())
		end
	end

} -- main


horseshit = 0;