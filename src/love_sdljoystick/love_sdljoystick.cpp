/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-11-06
**/

#include "love_sdljoystick.h"

// STD
#include <cmath>

// SDL
#include <SDL.h>

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE sdljoystick
#include "../liblove/wjoystick.h"

namespace love
{
namespace sdljoystick
{

	// Array of opened joysticks.
	SDL_Joystick ** joysticks = 0;

	int luainfo(lua_State * L)
	{
		love::luax_register_info(L,
			"sdljoystick",
			"joystick",
			"SDL Joystick Module",
			"LOVE Development Team",
			luaopen);

		return 0;
	}

	int luaopen(lua_State * L)
	{
		// Init the SDL timer system.
		if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
			return luaL_error(L, SDL_GetError());

		// Start joystick event watching.
		SDL_JoystickEventState(SDL_ENABLE);

		// Open all connected joysticks.
		int numjoysticks = getNumJoysticks();
		joysticks = (SDL_Joystick **)calloc(numjoysticks, sizeof(SDL_Joystick*));

		for(int i = 0;i<numjoysticks;i++)
			open(i);

		luareg(L);
		luax_register_gc(L, "sdljoystick", luagc);

		return 0;
	}

	int luagc(lua_State * L)
	{
		// Closes any open joysticks.
		for(int i = 0; i != getNumJoysticks(); i++)
		{
			if(isOpen(i))
				close(i);
		}

		free(joysticks);

		SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
		return 0;
	}

	bool checkIndex(int index)
	{
		if(index < getNumJoysticks())
			return true;
		else
			return false;
	}

	int getNumJoysticks()
	{
		return SDL_NumJoysticks();
	}

	const char * getName(int index)
	{
		return SDL_JoystickName(index);
	}

	bool open(int index)
	{
		if(isOpen(index))
			return true;

		if(!checkIndex(index))
			return false;

		if(!(joysticks[index] = SDL_JoystickOpen(index)) )
			return false;

		return true;
	}

	bool isOpen(int index)
	{
		if(!checkIndex(index))
			return false;

		return joysticks[index] != 0 ? true : false;
	}

	bool verifyJoystick(int index)
	{
		if(!checkIndex(index))
			return false;

		if(!isOpen(index))
			return false;

		return true;
	}

	int getNumAxes(int index)
	{
		return verifyJoystick(index) ? SDL_JoystickNumAxes(joysticks[index]) : 0;
	}

	int getNumBalls(int index)
	{
		return verifyJoystick(index) ? SDL_JoystickNumBalls(joysticks[index]) : 0;
	}

	int getNumButtons(int index)
	{
		return verifyJoystick(index) ? SDL_JoystickNumButtons(joysticks[index]) : 0;
	}

	int getNumHats(int index)
	{
		return verifyJoystick(index) ? SDL_JoystickNumHats(joysticks[index]) : 0;
	}

	float clamp(float x)
	{
		if(fabs((double)x) < 0.01) return 0.0f;
		if(x < -0.99f) return -1.0f;
		if(x > 0.99f) return 1.0f;
		return x;
	}

	float getAxis(int index, int axis)
	{
		if(!verifyJoystick(index))
			return 0;

		if(axis >= getNumAxes(index))
			return 0;
		
		return clamp(((float)SDL_JoystickGetAxis(joysticks[index], axis))/32768.0f);
	}

	int getAxes(lua_State * L)
	{
		love::luax_assert_argc(L, 1, 1);
		int index = (int)lua_tointeger(L, 1);

		if(!verifyJoystick(index))
			return 0;

		int num = getNumAxes(index);

		for(int i = 0; i<num; i++)
			lua_pushnumber(L, clamp(((float)SDL_JoystickGetAxis(joysticks[index], i))/32768.0f));
		return num;
	}

	int getBall(lua_State * L)
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

	bool isDown(int index, int button)
	{
		if(!verifyJoystick(index))
			return false;

		if(button >= getNumButtons(index))
			return false;

		return (SDL_JoystickGetButton(joysticks[index], button) == 1);
	}

	int getHat(int index, int hat)
	{
		if(!verifyJoystick(index))
			return 0;

		if(hat >= getNumHats(index))
			return 0;

		return SDL_JoystickGetHat(joysticks[index], hat);
	}

	void close(int index)
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
} // love
