-- the main game (where the action happens)
maingame = {

	init = function()
	
	end,
	
	render = function()
	
		if skin.bgimage ~= 0 then skin.bgimage:render(512-(skin.bgimage:getWidth() / 2),424-(skin.bgimage:getHeight() / 2));	end
		
		game:setColor(skin.grid);
		-- vertical lines		
		for i = 1,gridsize-1 do
			if i % offset == 0 then game:setColor(skin.box); end
			game:drawLine(begx + (50*i), begy, begx + (50*i), begy + (50*gridsize));
			if i % offset == 0 then game:setColor(skin.grid); end
		end
		-- horizontal lines		
		for i = 1,gridsize-1 do
			if i % offset == 0 then game:setColor(skin.box); end
			game:drawLine(begx, begy + (50*i), begx + (50*gridsize), begy + (50*i));
			if i % offset == 0 then game:setColor(skin.grid); end
		end
		
		game:setColor(skin.box);
		game:drawRect(512,424,(50*gridsize),(50*gridsize), 1);
		
		for x = 1,gridsize do
			for y = 1,gridsize do
				if player[x][y] == 1 then
					skin.yes:render(begx + (x*50) - 50 + 1, begy + (y*50) - 50);
				end
				
				if notit[x][y] == 1 then
					skin.no:render(begx + (x*50) - 50 + 1, begy + (y*50) - 50);
				end
			end
		end
		
		if won == true then
			text:setColor(skin.wincolor);
			text:align("center");
			text:print(512,begy + (50*gridsize) + 20,"You won!");
			text:setColor(skin.textcolor);
		end
		
		text:align("center");
		for i = 1,gridsize do
			text:print(begx + (i*50) - 25,begy - (vertical[i]:len()*9),vertical[i]);
		end
		text:align("right");
		for i = 1,gridsize do
			text:print(begx - 10,begy + (i*50) - 18,horizontal[i]);
		end
		
		-- right-side menu
		text:align("right");
		text:setColor(skin.textcolor);
		text:print(1010,40,"NoNo\n\nRandom Game\nPuzzle Game\nOptions\nClear\n\n\n\nExit");
		
		game:setColor("selector");
		game:fillRect(955,53 + (selected * 18),text:getLineWidth("Random Game") + 10,18);
	
	end,
	
	update = function(dt)
	
		if mouse:getX() > 900 and mouse:getX() < 1100 then
			if mouse:getY() > 62 and mouse:getY() < 80 then selected = 1; end
			if mouse:getY() > 80 and mouse:getY() < 98 then selected = 2; end
			if mouse:getY() > 98 and mouse:getY() < 116 then selected = 3; end
			if mouse:getY() > 116 and mouse:getY() < 134 then selected = 4; end
			if mouse:getY() > 188 and mouse:getY() < 206 then selected = 8; end
		end
	
	end,
	
	mousepressed = function(x, y, button)
	
		if button == LOVE_MOUSE_LEFT then
			if x > 900 and x < 1100 then
				if y > 62 and y < 80 then selected = 1; game:setState("newrandom"); end
				if y > 80 and y < 98 then selected = 2; game:setState("choosepuzzle"); end
				if y > 98 and y < 116 then selected = 3; game:setState("options"); end
				if y > 116 and y < 134 then selected = 4; player = getemptyboard(); notit = getemptyboard(); won = false; end
				if y > 188 and y < 206 then selected = 8; end
			elseif won == false then
				toggleplayer(x,y);
				won = checksolution();
			end
		end
		if button == LOVE_MOUSE_RIGHT and won == false then
			togglenotit(x,y);
		end
		
	end

}

-- creating a new random game
-- (not really enough to merrit a gamestate of its own, but it makes it separates it from the other things)
newrandom = {

	init = function()
	end,
	
	update = function(dt)
		clearvars();
		settextlines();
		
		game:setState("maingame");
	end

}

-- the menu where you choose a puzzle
-- (will hopefully be replaced by wonderous gui functions)
choosepuzzle = {

	init = function()
	end,
	
	render = function()
		text:align("left");
		for i,v in ipairs(presets) do
			text:print(100,100 + (i*18),v.gridsize .. "x" .. v.gridsize .. "      " .. v.name);
		end
		
		game:setColor("selector");
		game:fillRect(250,96 + (puzzlechoice * 18),300,18);
		
		-- right-side menu
		text:align("right");
		text:setColor(skin.textcolor);
		text:print(1010,40,"NoNo\n\nRandom Game\nPuzzle Game\nOptions\nClear\n\n\n\nExit");
		
		game:setColor("selector");
		game:fillRect(955,53 + (selected * 18),text:getLineWidth("Random Game") + 10,18);
	end,
	
	update = function(dt)
		
		if mouse:getX() > 100 and mouse:getX() < 900 then
			puzzlechoice = math.ceil((mouse:getY() - 100) / 18);
		end
	
		if mouse:getX() > 900 and mouse:getX() < 1100 then
			if mouse:getY() > 62 and mouse:getY() < 80 then selected = 1; end
			if mouse:getY() > 80 and mouse:getY() < 98 then selected = 2; end
			if mouse:getY() > 98 and mouse:getY() < 116 then selected = 3; end
			if mouse:getY() > 116 and mouse:getY() < 134 then selected = 4; end
			if mouse:getY() > 188 and mouse:getY() < 206 then selected = 8; end
		end
	
	end,
	
	mousepressed = function(x, y, button)
	
		if button == LOVE_MOUSE_LEFT then
			if x > 900 and x < 1100 then
				if y > 62 and y < 80 then selected = 1; game:setState("newrandom"); end
				if y > 80 and y < 98 then selected = 2; game:setState("choosepuzzle"); end
				if y > 98 and y < 116 then selected = 3; game:setState("options"); end
				if y > 116 and y < 134 then selected = 4; player = getemptyboard(); notit = getemptyboard(); won = false; end
				if y > 188 and y < 206 then selected = 8; end
			elseif puzzlechoice > 0 and puzzlechoice <= table.getn(presets) then
				clearvars();
				solution = getboard(puzzlechoice);
				settextlines();
		
				game:setState("maingame");
			end
		end
		
	end

}

-- the options menu
-- (also hopefully replaced by gui functions in the near future)
options = {

	init = function()
		choice = 0;
	end,
	
	render = function()
		text:align("left");
		text:print(50,50,mouse:getX() .. "x" .. mouse:getY() .. "  (" .. choice .. ")");
		text:align("right");
		text:print(400,100, "Grid Size:\nSkin:");
		text:align("left");
		text:print(420,100, setgridsize);
		text:print(500,100, "< >");
		local count = 1;
		for key,value in pairs(skins) do
			text:print(420,100 + (count*18), value.name);
			if value.name == skin.name then
				game:setColor("selector");
				local wid = text:getLineWidth(value.name) + 10;
				game:fillRect(420 + (wid / 2) - 5,100 + (count*18) - 5,wid,18);
			end
			count = count + 1;
		end
		
		-- right-side menu
		text:align("right");
		text:setColor(skin.textcolor);
		text:print(1010,40,"NoNo\n\nRandom Game\nPuzzle Game\nOptions\nClear\n\n\n\nExit");
		
		game:setColor("selector");
		game:fillRect(955,53 + (selected * 18),text:getLineWidth("Random Game") + 10,18);
	end,
	
	update = function(dt)
	
		if mouse:getX() > 900 and mouse:getX() < 1100 then
			if mouse:getY() > 62 and mouse:getY() < 80 then selected = 1; end
			if mouse:getY() > 80 and mouse:getY() < 98 then selected = 2; end
			if mouse:getY() > 98 and mouse:getY() < 116 then selected = 3; end
			if mouse:getY() > 116 and mouse:getY() < 134 then selected = 4; end
			if mouse:getY() > 188 and mouse:getY() < 206 then selected = 8; end
		end
	
	end,
	
	mousepressed = function(x, y, button)
	
		if button == LOVE_MOUSE_LEFT then
			if x > 900 and x < 1100 then
				if y > 62 and y < 80 then selected = 1; game:setState("newrandom"); end
				if y > 80 and y < 98 then selected = 2; game:setState("choosepuzzle"); end
				if y > 98 and y < 116 then selected = 3; game:setState("options"); end
				if y > 116 and y < 134 then selected = 4; player = getemptyboard(); notit = getemptyboard(); won = false; end
				if y > 188 and y < 206 then selected = 8; end
			elseif x > 500 and x < 510 and y > 90 and y < 100 then
				setgridsize = setgridsize - 1;
				if setgridsize < 5 then setgridsize = 12; end
				
				setoffset = setgridsize;
				if setgridsize == 6 or setgridsize == 9 then setoffset = 3;
				elseif setgridsize == 8 or setgridsize == 12 then setoffset = 4;
				elseif setgridsize == 10 then setoffset = 5; end
			elseif x > 510 and x < 520 and y > 90 and y < 100 then
				setgridsize = setgridsize + 1;
				if setgridsize > 12 then setgridsize = 5; end
					
				setoffset = setgridsize;
				if setgridsize == 6 or setgridsize == 9 then setoffset = 3;
				elseif setgridsize == 8 or setgridsize == 12 then setoffset = 4;
				elseif setgridsize == 10 then setoffset = 5; end
			elseif x > 420 and x < 900 and y > 100 then
				choice = math.ceil((y - 100) / 20);
				local count = 1;
				for key,value in pairs(skins) do
					if choice == count then
						skin = skins[key];
						game:setBackground(skin.bg);
					end
					count = count + 1;
				end
			end
		end
		
	end

}
