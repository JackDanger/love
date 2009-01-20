/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#include "love_sdltimer.h"

// SDL
#include <SDL.h>

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE sdltimer
#include "../liblove/timer/wtimer.h"

namespace love
{
namespace sdltimer
{

	// Timing vars for benchmarking.
	Uint32 time_init = 0;
	
	// Frame delta vars.
	Uint32 currTime = 0;
	Uint32 prevTime;
	Uint32 prevFpsUpdate = 0;

	// Updated with a certain frequency.
	float fps = 0;

	// The frequency by which to update the FPS.
	float fpsUpdateFrequency = 1;

	// Frames since last FPS update.
	int frames = 0;

	// The current timestep.
	float dt = 0;

	int luainfo(lua_State * L)
	{
		love::luax_register_info(L,
			"sdltimer",
			"timer",
			"SDL Timer Module",
			"LOVE Development Team",
			luaopen);

		return 0;
	}

	int luaopen(lua_State * L)
	{
		// Init the SDL timer system.
		if(SDL_InitSubSystem(SDL_INIT_TIMER) < 0)
			return luaL_error(L, SDL_GetError());

		luareg(L);
		luax_register_gc(L, "sdltimer", luagc);
		return 0;
	}

	int luagc(lua_State * L)
	{
		SDL_QuitSubSystem(SDL_INIT_TIMER);
		return 0;
	}

	void step()
	{
		// Frames rendered
		frames++;
			
		// "Current" time is previous time by now.
		prevTime = currTime;

		// Get ticks from SDL
		currTime = SDL_GetTicks();

		// Convert to number of seconds
		dt = (currTime - prevTime)/1000.0f;

		// Update FPS?
		if((currTime - prevFpsUpdate)/1000.0f > fpsUpdateFrequency)
		{
			fps = frames/fpsUpdateFrequency;
			prevFpsUpdate = currTime;
			frames = 0;
		}

		if(dt < 0)
			printf("Timer: WTF: %f: \n", dt);
	}

	float getDelta()
	{
		return dt;
	}

	float getFPS()
	{
		return fps;
	}

	void sleep(int ms)
	{		
		SDL_Delay((unsigned int)ms);
	}

	float getTime()
	{
		return (SDL_GetTicks() - time_init)/1000.0f;
	}

} // sdltimer
} // love
