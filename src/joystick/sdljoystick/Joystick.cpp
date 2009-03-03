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

#include "Joystick.h"

// STD
#include <cmath>

// LOVE
#include "wrap_Joystick.h"

namespace love
{
namespace joystick
{
namespace sdljoystick
{
	Joystick * Joystick::_instance = 0;

	Joystick::Joystick()
		: joysticks(0)
	{
	}

	Joystick::~Joystick()
	{
		// Closes any open joysticks.
		for(int i = 0; i != getNumJoysticks(); i++)
		{
			if(isOpen(i))
				close(i);
		}

		free(joysticks);

		SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	}

	Joystick * Joystick::__getinstance()
	{
		if(_instance == 0)
			_instance = new Joystick();
		return _instance;
	}

	int Joystick::__advertise(lua_State * L)
	{
		love::luax_register_info(L,
			"sdljoystick",
			"joystick",
			"SDL Joystick Module",
			"LOVE Development Team",
			&__open);
		return 0;
	}

	int Joystick::__open(lua_State * L)
	{
		// Init the SDL joystick system.
		if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
			return luaL_error(L, SDL_GetError());

		// Start joystick event watching.
		SDL_JoystickEventState(SDL_ENABLE);

		// Open all connected joysticks.
		int numjoysticks = Joystick::__getinstance()->getNumJoysticks();
		Joystick::__getinstance()->joysticks = (SDL_Joystick **)calloc(numjoysticks, sizeof(SDL_Joystick*));

		for(int i = 0;i<numjoysticks;i++)
			Joystick::__getinstance()->open(i);

		// Open stuff here.
		wrap_Joystick_open(L);
		luax_register_gc(L, "sdljoystick", &__garbagecollect);
		return 0;
	}

	int Joystick::__garbagecollect(lua_State * L)
	{
		Joystick * m = Joystick::__getinstance();
		if(m != 0)
			delete m;
		return 0;
	}

	bool Joystick::checkIndex(int index)
	{
		if(index < getNumJoysticks())
			return true;
		else
			return false;
	}

	int Joystick::getNumJoysticks()
	{
		return SDL_NumJoysticks();
	}

	const char * Joystick::getName(int index)
	{
		return SDL_JoystickName(index);
	}

	bool Joystick::open(int index)
	{
		if(isOpen(index))
			return true;

		if(!checkIndex(index))
			return false;

		if(!(joysticks[index] = SDL_JoystickOpen(index)) )
			return false;

		return true;
	}

	bool Joystick::isOpen(int index)
	{
		if(!checkIndex(index))
			return false;

		return joysticks[index] != 0 ? true : false;
	}

	bool Joystick::verifyJoystick(int index)
	{
		if(!checkIndex(index))
			return false;

		if(!isOpen(index))
			return false;

		return true;
	}

	int Joystick::getNumAxes(int index)
	{
		return verifyJoystick(index) ? SDL_JoystickNumAxes(joysticks[index]) : 0;
	}

	int Joystick::getNumBalls(int index)
	{
		return verifyJoystick(index) ? SDL_JoystickNumBalls(joysticks[index]) : 0;
	}

	int Joystick::getNumButtons(int index)
	{
		return verifyJoystick(index) ? SDL_JoystickNumButtons(joysticks[index]) : 0;
	}

	int Joystick::getNumHats(int index)
	{
		return verifyJoystick(index) ? SDL_JoystickNumHats(joysticks[index]) : 0;
	}

	float Joystick::clampval(float x)
	{
		if(fabs((double)x) < 0.01) return 0.0f;
		if(x < -0.99f) return -1.0f;
		if(x > 0.99f) return 1.0f;
		return x;
	}

	float Joystick::getAxis(int index, int axis)
	{
		if(!verifyJoystick(index))
			return 0;

		if(axis >= getNumAxes(index))
			return 0;
		
		return clampval(((float)SDL_JoystickGetAxis(joysticks[index], axis))/32768.0f);
	}

	int Joystick::getAxes(lua_State * L)
	{
		love::luax_assert_argc(L, 1, 1);
		int index = (int)lua_tointeger(L, 1);

		if(!verifyJoystick(index))
			return 0;

		int num = getNumAxes(index);

		for(int i = 0; i<num; i++)
			lua_pushnumber(L, clampval(((float)SDL_JoystickGetAxis(joysticks[index], i))/32768.0f));
		return num;
	}

	int Joystick::getBall(lua_State * L)
	{
		love::luax_assert_argc(L, 2, 2);
		int index = (int)lua_tointeger(L, 1);
		int ball = (int)lua_tointeger(L, 2);

		if(!verifyJoystick(index))
			return 0;

		if(ball >= getNumBalls(index))
			return 0;

		int dx, dy;
		SDL_JoystickGetBall(joysticks[index], ball, &dx, &dy);
		
		lua_pushnumber(L, dx);
		lua_pushnumber(L, dy);
		return 2;		
	}

	bool Joystick::isDown(int index, int button)
	{
		if(!verifyJoystick(index))
			return false;

		if(button >= getNumButtons(index))
			return false;

		return (SDL_JoystickGetButton(joysticks[index], button) == 1);
	}

	int Joystick::getHat(int index, int hat)
	{
		if(!verifyJoystick(index))
			return 0;

		if(hat >= getNumHats(index))
			return 0;

		return SDL_JoystickGetHat(joysticks[index], hat);
	}

	void Joystick::close(int index)
	{
		if(!checkIndex(index))
			return;

		if(joysticks[index]!=0)
		{
			SDL_JoystickClose(joysticks[index]);
			joysticks[index] = 0;
		}
	}

} // sdljoystick
} // joystick
} // love