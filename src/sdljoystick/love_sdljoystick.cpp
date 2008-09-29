#include "love_sdljoystick.h"
#include "mod_sdljoystick.h"

// LOVE
#include <love/constants.h>
#include <love/Core.h>

// SDL
#include <SDL.h>
#include <SDL_joystick.h>

// STD
#include <cmath>

namespace love_sdljoystick
{
	// Array of opened joysticks.
	SDL_Joystick ** joysticks = 0;

	bool module_init(love::Core * core)
	{
		std::cout << "INIT love.joystick [" << "SDL" << "]" << std::endl;
		
		// Initialize the joystick.
		if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
		{
			std::cout << "Could not init SDL_JOYSTICK: " << SDL_GetError() << std::endl;
			return false;
		}

		// Start joystick event watching.
		SDL_JoystickEventState(SDL_ENABLE);

		// Open all connected joysticks.
		int numjoysticks = getNumJoysticks();
		joysticks = (SDL_Joystick **)calloc(numjoysticks, sizeof(SDL_Joystick*));

		for(int i = 0;i<numjoysticks;i++)
			open(i);

		return true;
	}

	bool module_quit(love::Core * core)
	{
		// Closes any open joysticks.
		for(int i = 0; i != getNumJoysticks(); i++)
		{
			if(isOpen(i))
				close(i);
		}

		free(joysticks);

		std::cout << "QUIT love.joystick [" << "SDL" << "]" << std::endl;
		return true;
	}

	bool module_open(love::Core * core)
	{
		luaopen_mod_sdljoystick(core->getL());
		return true;
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

	void open(int index)
	{
		if(isOpen(index))
			return;

		if(!checkIndex(index))
		{
			love::core->error("Could not open joystick with index %d: Invalid joystick index.", index);
			return;
		}

		if(!(joysticks[index] = SDL_JoystickOpen(index)) )
		{
			love::core->error("Could not open joystick with index %d: Unknown error.", index);
			return;
		}
	}

	bool isOpen(int index)
	{
		if(!checkIndex(index))
			return love::core->error("Could not check joystick with index %d: Invalid joystick index.", index);

		return joysticks[index] != 0 ? true : false;
	}

	bool verifyJoystick(int index)
	{
		if(!checkIndex(index))
			return love::core->error("Invalid joystick index: %d", index);

		if(!isOpen(index))
			return love::core->error("Joystick with index %d is not open.", index);

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
		{
			love::core->error("Could not get axis status of joystick with index %d: axis %d is invalid.", axis);
			return 0;
		}
		
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
		{
			love::core->error("Could not get trackball status of joystick with index %d: trackball %d is invalid.", ball);
			return 0;
		}

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
			return love::core->error("Could not get button status of joystick with index %d: button %d is invalid.", button);

		return (SDL_JoystickGetButton(joysticks[index], button) == 1);
	}

	int getHat(int index, int hat)
	{
		if(!verifyJoystick(index))
			return 0;

		if(hat >= getNumHats(index))
		{
			love::core->error("Could not get viewhat status of joystick with index %d: viewhat %d is invalid.", hat);
			return 0;
		}

		return SDL_JoystickGetHat(joysticks[index], hat);
	}

	void close(int index)
	{
		if(!checkIndex(index))
		{
			love::core->error("Invalid joystick index: %d", index);
			return;
		}

		if(joysticks[index]!=0)
		{
			SDL_JoystickClose(joysticks[index]);
			joysticks[index] = 0;
		}
	}

} // love_sdljoystick
