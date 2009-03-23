/**
* Copyright (c) 2006-2009 LOVE Development Team
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
* --> Visit http://love2d.org for more information! (^.^)/
**/

#ifndef LOVE_JOYSTICK_SDLJOYSTICK_JOYSTICK_H
#define LOVE_JOYSTICK_SDLJOYSTICK_JOYSTICK_H

// SDL
#include <SDL.h>

// LOVE
#include "../../luax.h"

namespace love
{
namespace joystick
{
namespace sdljoystick
{
	class Joystick
	{
	private:
		static Joystick * instance;
		SDL_Joystick ** joysticks;
	protected:
		Joystick();
	public:
		~Joystick();

		static Joystick * getInstance();
		static int __advertise(lua_State * L);
		static int __open(lua_State * L);
		static int __garbagecollect(lua_State * L);

		bool checkIndex(int index);
		int getNumJoysticks();
		const char * getName(int index);
		bool open(int index);
		bool isOpen(int index);
		bool verifyJoystick(int index);
		int getNumAxes(int index);
		int getNumBalls(int index);
		int getNumButtons(int index);
		int getNumHats(int index);
		float clampval(float x);
		float getAxis(int index, int axis);
		int getAxes(lua_State * L);
		int getBall(lua_State * L);
		bool isDown(int index, int button);
		int getHat(int index, int hat);
		void close(int index);

	}; // Joystick

} // sdljoystick
} // joystick
} // love

#endif // LOVE_JOYSTICK_SDLJOYSTICK_JOYSTICK_H