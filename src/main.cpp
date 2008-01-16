/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#include "love.h"
#include "platform.h"

// @todo unacceptable?
// This is required for subsystem:WINDOWS (Release build).
#include <SDL.h>

int main(int argc, char* argv[])
{
	
	if(love::platform_init(argc, argv) != 0)
		return 1;

	int status = love::platform_loop();

	return status;
}
