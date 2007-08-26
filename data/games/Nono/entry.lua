
--
-- Nono
-- Created: 26.07.07
--

-- now with skin support!
skins = {
	
	default = {
		name = "default",
		box = "darkgray",
		grid = "lightgray",
		yes = game:addImage("default_yes", "graphics/skins/default/yes.png"),
		no = game:addImage("default_no", "graphics/skins/default/no.png"),
		bgimage = 0,
		bg = "white",
		textcolor = "black",
		wincolor = "green"
	}, 
	
	hawking = {
		name = "hawking",
		box = "white",
		grid = "white",
		yes = game:addImage("hawking_yes", "graphics/skins/hawking/yes.png"),
		no = game:addImage("hawkign_no", "graphics/skins/hawking/no.png"),
		bgimage = game:addImage("hawkign_bgimage", "graphics/skins/hawking/background.png"),
		bg = "yoga", 
		textcolor = "white",
		wincolor = "yogi"
	}	
}

-- the skin that will be used.
skin = skins.hawking

main = {

	init = function()
		
		-- include files
		game:include("functions.lua");
		game:include("states.lua");
		game:include("puzzles.lua");
		
		-- font and color
		game:addFont("main", 12);
		text:setFont("main");
		
		game:addColor("white", 0xFFFFFF);
		game:addColor("black", 0x000000);
		game:addColor("red", 0xdd0000);
		game:addColor("green", 0x00dd00);
		game:addColor("yoga", 0x1a84d5);
		game:addColor("yogi", 0x22e139);
		game:addColor("darkgray", 0x989898);
		game:addColor("lightgray", 0xcfcfcf);
		game:addColor("selector", 255,255,255,140);
		
		game:setBackground(skin.bg);
		
		-- states
		game:addState("maingame");
		game:addState("newrandom");
		game:addState("choosepuzzle");
		game:addState("options");
		
		-- variables
		setgridsize = 8;
		setoffset = 4;
		selected = 1;
		puzzlechoice = 1;
		horizontal = {};
		vertical = {};
		
		-- let's go  ^.^)/
		game:setState("newrandom");
	end
}