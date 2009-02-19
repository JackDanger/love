/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
**/

#include "Timer.h"

namespace love
{
namespace timer
{
namespace sdltimer
{
	// Wrapper loaders.
	extern int wrap_Timer_open(lua_State * L);

	Timer * Timer::_instance = 0;

	Timer::Timer()
		: time_init(0), currTime(0), prevFpsUpdate(0), fps(0), fpsUpdateFrequency(1), 
		frames(0), dt(0)
	{
	}

	Timer * Timer::__getinstance()
	{
		if(_instance == 0)
			_instance = new Timer();
		return _instance;
	}

	int Timer::__advertise(lua_State * L)
	{
		luax_register_info(L,
			"sdltimer",
			"timer",
			"SDL Timer Module",
			"LOVE Development Team",
			&__open);
		return 0;
	}

	int Timer::__open(lua_State * L)
	{
		// Init the SDL timer system.
		if(SDL_InitSubSystem(SDL_INIT_TIMER) < 0)
			return luaL_error(L, SDL_GetError());
		wrap_Timer_open(L);
		luax_register_gc(L, "sdltimer", &__garbagecollect);
		return 0;
	}

	int Timer::__garbagecollect(lua_State * L)
	{
		// Quit SDL timer.
		SDL_QuitSubSystem(SDL_INIT_TIMER);

		// Delete the instance.
		Timer * m = Timer::__getinstance();
		if(m != 0)
			delete m;

		return 0;
	}

	void Timer::step()
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
	}

	void Timer::sleep(unsigned int ms)
	{
		SDL_Delay(ms);
	}

	float Timer::getDelta() const
	{
		return dt;
	}

	float Timer::getFPS() const
	{
		return fps;
	}

	float Timer::getTime() const
	{
		return (SDL_GetTicks() - time_init)/1000.0f;
	}

} // sdltimer
} // timer
} // love
