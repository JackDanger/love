-- clears all the variables
clearvars = function()
	gridsize = setgridsize;
	offset = setoffset;
	
	begx = 512 - ((50*gridsize) / 2);
	begy = 424 - ((50*gridsize) / 2);
	
	for i = 1,gridsize do
		horizontal[i] = "";
		vertical[i] = "";
	end
		
	solution = getboard(0); --the default action is a random board
	player = getemptyboard();
	notit = getemptyboard();
	
	won = false;
end

-- sets the text lines that you see above and to the right of the puzzle board
settextlines = function()		
	local count = 0;
	for x = 1,gridsize do
		count = 0;
		for y = 1,gridsize do
			if solution[x][y] == 1 then
				count = count + 1;
			elseif count ~= 0 then
				vertical[x] = vertical[x] .. count .. "\n";
				count = 0;
			end
		end
		if count~= 0 then vertical[x] = vertical[x] .. count .. "\n"; end
	end
		
	for y = 1,gridsize do
		count = 0;
		for x = 1,gridsize do
			if solution[x][y] == 1 then
				count = count + 1;
			elseif count ~= 0 then
				horizontal[y] = horizontal[y] .. count .. " ";
				count = 0;
			end
		end
		if count~= 0 then horizontal[y] = horizontal[y] .. count .. " "; end
	end
end

-- gets a board (if the preset is 0 then gets a random board)
getboard = function(preset)
	
	if preset == 0 then
		local board = {};
		for x = 1,gridsize do
			board[x] = {};
			for y = 1,gridsize do
				board[x][y] = math.random(0,1);
			end
		end
		
		return board;
	end
	
	gridsize = presets[preset].gridsize;
	offset = presets[preset].offset;
	
	begx = 512 - ((50*gridsize) / 2);
	begy = 424 - ((50*gridsize) / 2);
	
	return presets[preset].board;
end

-- gets an empty board (just initializes an empty 2d-array)
getemptyboard = function()
	local board = {};
	for x = 1,gridsize do
		board[x] = {};
		for y = 1,gridsize do
			board[x][y] = 0;
		end
	end
	return board;
end

-- toggle the player's solution
toggleplayer = function(x,y)
	if x > begx and x < begx + (gridsize * 50) and y > begy and y < begy + (gridsize * 50) then
		x = math.ceil((x - begx) / 50);
		y = math.ceil((y - begy) / 50);
		if player[x][y] == 1 then
			player[x][y] = 0;
		else
			player[x][y] = 1;
			if notit[x][y] == 1 then notit[x][y] = 0; end -- mutually exclusive
		end
	end
end

-- toggle the hints
togglenotit = function(x,y)
	if x > begx and x < begx + (gridsize * 50) and y > begy and y < begy + (gridsize * 50) then
		x = math.ceil((x - begx) / 50);
		y = math.ceil((y - begy) / 50);
		if notit[x][y] == 1 then
			notit[x][y] = 0;
		else
			notit[x][y] = 1;
			if player[x][y] == 1 then player[x][y] = 0; end -- mutually exclusive
		end
	end
end

-- check to see if the player solution is the same as the actual solution
checksolution = function()
	for x = 1,gridsize do
		for y = 1,gridsize do
			if player[x][y] ~= solution[x][y] then return false; end
		end
	end
	
	return true;
end
