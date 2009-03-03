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