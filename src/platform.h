/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_PLATFORM_H
#define LOVE_PLATFORM_H

namespace love
{

	/**
	* Readies devices, libraries, etc. (Assigns all needed "modules").
	* @param argc Number of command like arguments.
	* @param argv A pointer to the array of command line arguments.
	**/
	extern int platform_init(int argc, char* argv[]);

	/**
	* This method contains the main program loop.
	* Once called, it will not finish before the end of the program.
	**/
	extern int platform_loop();

	/**
	* Causes the program to exit.
	**/
	extern void platform_quit();

} // love

#endif // LOVE_PLATFORM_H
