/**
* @file main.cpp
* @author Anders Ruud
* @date 2006-11-06
* @version 1.0
* @brief LOVE entry point.
**/

#include "love.h"
#include "platform.h"

// We need this if we are using love::core.
#include "Core.h"

#include "physfs.h"

// Define love::core here.
love::Core * love::core;

int main(int argc, char* argv[])
{

	// Create the love Core.
	love::core = new love::Core();

	// Platform init
	if(love::platform_init(argc, argv) != love::LOVE_OK)
		return 1;

	// Init core.
	love::core->init();

	// Enter main loop
	love::platform_loop();


	return 0;
}
