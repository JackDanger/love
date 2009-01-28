/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* Timer module using the SDL's timer. Note that the
* the resolution is pretty poor (1 ms at best).
* 
* @author Anders Ruud
* @date 2008-10-28
**/

#ifndef LOVE_TIMER_SDLTIMER_TIMER_H
#define LOVE_TIMER_SDLTIMER_TIMER_H

// SDL
#include <SDL.h>

// LOVE
#include "../../luax.h"

namespace love
{
namespace timer
{
namespace sdltimer
{
	class Timer
	{
	private:

		// The single instance of this class.
		static Timer * _instance;

		// Timing vars for benchmarking.
		Uint32 time_init;
		
		// Frame delta vars.
		Uint32 currTime;
		Uint32 prevTime;
		Uint32 prevFpsUpdate;

		// Updated with a certain frequency.
		float fps;

		// The frequency by which to update the FPS.
		float fpsUpdateFrequency;

		// Frames since last FPS update.
		int frames;

		// The current timestep.
		float dt;

	protected:
		Timer();
	public:

		static Timer * __getinstance();
		static int __advertise(lua_State * L);
		static int __open(lua_State * L);
		static int __garbagecollect(lua_State * L);
		
		void step();
		void sleep(unsigned int ms);
		float getDelta() const;
		float getFPS() const;
		float getTime() const;

	}; // Timer

} // sdltimer
} // timer
} // love

#endif // LOVE_TIMER_SDLTIMER_TIMER_H