/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* Joystick module using the SDL's input abstraction.
* 
* @author Anders Ruud
* @date 2008-11-06
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
		static Joystick * _instance;
		SDL_Joystick ** joysticks;
	protected:
		Joystick();
	public:
		~Joystick();

		static Joystick * __getinstance();
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