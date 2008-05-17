/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* This is the executable. It does the following:
*
* - Inits SDL. 
* - Creates a love::Core.
* - Inserts all the modules into the core.
* - And finally enters update/render loop.
* 
* @author Anders Ruud
* @date 2008-03-15
*/

// Module configuration goes here, for now.
#ifdef WIN32
#	define LOVE_WINDOWS
#	define LOVE_MOD_FILESYSTEM "love_physfs.dll"
#	define LOVE_MOD_PHYSICS	"love_chipmunk.dll"
#	define LOVE_MOD_GRAPHICS "love_opengl.dll"
#	define LOVE_MOD_TIMER "love_sdltimer.dll"
#	define LOVE_MOD_KEYBOARD "love_sdlkeyboard.dll"
#	define LOVE_MOD_MOUSE "love_sdlmouse.dll"
#	define LOVE_MOD_AUDIO "love_sdlmixer.dll"
#	define LOVE_MOD_SYSTEM "love_system.dll"
#else
#	define LOVE_LINUX
#	define LOVE_MOD_PATH "/usr/lib/love/"
#	define LOVE_MOD_FILESYSTEM "./love_physfs.so"
#	define LOVE_MOD_PHYSICS	"./love_chipmunk.so"
#	define LOVE_MOD_GRAPHICS "./love_opengl.so"
#	define LOVE_MOD_TIMER "./love_sdltimer.so"
#	define LOVE_MOD_KEYBOARD "./love_sdlkeyboard.so"
#	define LOVE_MOD_MOUSE "./love_sdlmouse.so"
#	define LOVE_MOD_AUDIO "./love_sdlmixer.so"
#	define LOVE_MOD_SYSTEM "./love_system.so"
#endif

// STD
#include <iostream>
#include <fstream>

// SDL
#include <SDL.h>

// LOVE
#include <love/Core.h>
#include <love/Game.h>
#include <love/Exception.h>
#include <love/version.h>

using namespace love;

// Some typedefs.
typedef const pGame & (*fptr_game)();

int main(int argc, char* argv[])
{	
	// Redirect output to files.
#ifdef _DEBUG
	std::ofstream cout; 
	std::ofstream cerr; 
	cout.open ("cout.txt");
	cerr.open ("cerr.txt");
	std::cout.rdbuf(cout.rdbuf());
	std::cerr.rdbuf(cerr.rdbuf());
#endif

	// Create a core.
	pCore core(new Core());

	// Init SDL.
	if(SDL_Init(0))
	{
		std::cerr << "Could not init SDL. " << SDL_GetError() << std::endl;
		return false;
	}

	// Print welcome message.
	std::cout << "This is LOVE " << LOVE_VERSION_FULL_STR << "." << std::endl << std::endl;

	if(!core->insmod(argc, argv, LOVE_MOD_TIMER, Module::TIMER)) return 1;
	// Add modules. (Modules are immediately inited, so the order is important).
	if(!core->insmod(argc, argv, LOVE_MOD_FILESYSTEM, Module::FILESYSTEM)) return 1;
	if(!core->insmod(argc, argv, LOVE_MOD_GRAPHICS, Module::GRAPHICS)) return 1;
	//if(!core->insmod(argc, argv, LOVE_MOD_PHYSICS, Module::PHYSICS)) return 1;
	
	if(!core->insmod(argc, argv, LOVE_MOD_KEYBOARD, Module::KEYBOARD)) return 1;
	if(!core->insmod(argc, argv, LOVE_MOD_MOUSE, Module::MOUSE)) return 1;
	if(!core->insmod(argc, argv, LOVE_MOD_AUDIO, Module::AUDIO)) return 1;
	if(!core->insmod(argc, argv, LOVE_MOD_SYSTEM, Module::SYSTEM)) return 1;

	/**
	* Main loop section.
	**/
	
	// Enable UNICODE. This is needed for input to work properly.
	SDL_EnableUNICODE(1);

	// The union used to get SDL events. 
	SDL_Event e;

	bool running = true;

	// Function pointers.
	fptr_void timer_step = 0;
	fptr_float timer_getDelta = 0;
	fptr_void graphics_clear = 0;
	fptr_void graphics_present = 0;
	fptr_game system_getGame = 0;

	// Get function pointers.
	try
	{
		timer_step = (fptr_void)core->getf(Module::TIMER, "step");
		timer_getDelta = (fptr_float)core->getf(Module::TIMER, "getDelta");
		graphics_clear = (fptr_void)core->getf(Module::GRAPHICS, "clear");
		graphics_present = (fptr_void)core->getf(Module::GRAPHICS, "present");
		system_getGame = (fptr_game)core->getf(Module::SYSTEM, "getGame");
	}
	catch(Exception ex)
	{
		std::cerr << ex.msg() << std::endl;
		return 1;
	}

	while(running)
	{
		const pGame & game = system_getGame();
		if(!game)
		{
			std::cerr << "ERROR! No game." << std::endl;
			return 1;
		}

		timer_step();
		game->update(timer_getDelta());
		graphics_clear();
		game->draw();		

		while(SDL_PollEvent(&e))
		{
			// Do events.
			switch(e.type)
			{
				case SDL_KEYDOWN:			
					game->keyPressed(e.key.keysym.sym);
					break;
				case SDL_KEYUP:
					game->keyReleased(e.key.keysym.sym);
					break;
				case SDL_MOUSEBUTTONDOWN:
					game->mousePressed(e.button.x, e.button.y, e.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					game->mouseReleased(e.button.x, e.button.y, e.button.button);
					break;
				case SDL_MOUSEMOTION:
					game->mouseMoved(e.button.x, e.button.y);
					break;
				case SDL_QUIT:
					running = false; // Bye bye.
					break;
				default:
					break;
			}
		}

		graphics_present();
	}
	return 0;
} // main
