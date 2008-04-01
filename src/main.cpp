/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

// LOVE
#include "love.h"

// SDL needs to be included here to 
// rename the entry point.
#include <SDL.h>

int main(int argc, char* argv[])
{	
	// Init everything.
	love::init(argc, argv);

	// Main loop.
	love::loop();

	return 0;
}
