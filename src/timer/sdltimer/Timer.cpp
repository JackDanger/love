/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2009-01-21
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
