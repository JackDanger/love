--
-- game.lua
--
-- Description: Master game control file.
-- Author: 		Anders Ruud
-- Version:     1.0
-- Date:    	12-06-06
--

GSTATE_MENU 	= 0
GSTATE_LOAD     = 1
GSTATE_RUN      = 2

-- Our global game.
game = nil;

-- This is the entry point.

function main ( game )



	-- The name of the game.
	-- This will be displayed in the title bar of the application window.
	game:setName("Test Quest")

	-- The version of the game.
	game:setVersion("1.0")

	-- This is what I imagine go here:

	game:addState("gamestates/menu.lua", 	GSTATE_MENU)
	game:addState("gamestates/load.lua", 	GSTATE_LOAD)
	game:addState("gamestates/run.lua", 	GSTATE_RUN)
	
	game:setState(GSTATE_MENU)


end