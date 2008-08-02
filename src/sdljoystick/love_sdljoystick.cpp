#include "love_sdljoystick.h"
#include "mod_sdljoystick.h"

// LOVE
#include <love/constants.h>
#include <love/Core.h>

// SDL
#include <SDL.h>
#include <SDL_Joystick.h>

namespace love_sdljoystick
{
	// Requires Core (for error messages).
	love::Core * core = 0;

	bool module_init(int argc, char ** argv, love::Core * core)
	{
		std::cout << "INIT love.gamepad [" << "SDL" << "]" << std::endl;
		
		// Set function pointers and load module.
		{
			love::Gamepad * g = core->getGamepad();
			g->loaded = true;
		}

		love_sdljoystick::core = core;

		// Initialize the joystick.
		if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0)
		{
			std::cout << "Could not init SDL_JOYSTICK: " << SDL_GetError() << std::endl;
			return false;
		}

		// Start joystick event watching.
		SDL_JoystickEventState(SDL_ENABLE);

		return true;
	}

	bool module_quit()
	{
		// Closes any open gamepads.
		for(int i = 0; i != numGamepads(); i++)
		{
			if(isOpen(i))
				close(i);
		}

		std::cout << "QUIT love.gamepad [" << "SDL" << "]" << std::endl;
		return true;
	}

	bool module_open(void * vm)
	{
		lua_State * s = (lua_State *)vm;
		if(s == 0)
			return false;
		luaopen_mod_sdljoystick(s);
		return true;
	}

	bool checkIndex(int index)
	{
		if(index < numGamepads())
			return true;
		else
			return false;
	}

	int numGamepads()
	{
		return SDL_NumJoysticks();
	}

	const char * getName(int index)
	{
		return SDL_JoystickName(index);
	}

	void open(int index)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not open gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return;
		}

		SDL_Joystick * gamepad;
		if( !(gamepad = SDL_JoystickOpen(index)) )
		{
			std::stringstream err;
			err << "Could not open gamepad with index " << index << ": Unknown error.";
			core->error(err.str().c_str());
			return;
		}
	}

	bool isOpen(int index)
	{
		return SDL_JoystickOpened(index) == 1 ? true : false;
	}

	int numAxes(int index)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not get axes of gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return 0;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not get axes of gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return 0;
		}

		return SDL_JoystickNumAxes(SDL_JoystickOpen(index));
	}

	int numBalls(int index)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not get trackballs of gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return 0;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not get trackballs of gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return 0;
		}

		return SDL_JoystickNumBalls(SDL_JoystickOpen(index));
	}

	int numButtons(int index)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not get buttons of gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return 0;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not get buttons of gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return 0;
		}

		return SDL_JoystickNumButtons(SDL_JoystickOpen(index));
	}

	int numHats(int index)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not get viewhats of gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return 0;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not get viewhats of gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return 0;
		}

		return SDL_JoystickNumHats(SDL_JoystickOpen(index));
	}

	int getAxis(int index, int axis)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not get axis status of gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return 0;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not get axis status of gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return 0;
		}

		if(axis >= numAxes(index))
		{
			std::stringstream err;
			err << "Could not get axis status of gamepad with index " << index << ": Axis " << axis << " is invalid.";
			core->error(err.str().c_str());
			return 0;
		}

		return SDL_JoystickGetAxis(SDL_JoystickOpen(index), axis);
	}

	int getBallX(int index, int ball)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not get trackball status of gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return 0;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not get trackball status of gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return 0;
		}

		if(ball >= numBalls(index))
		{
			std::stringstream err;
			err << "Could not get trackball status of gamepad with index " << index << ": Trackball " << ball << " is invalid.";
			core->error(err.str().c_str());
			return 0;
		}

		int dx;
		int dy;

		SDL_JoystickGetBall(SDL_JoystickOpen(index), ball, &dx, &dy);
		return dx;
	}

	int getBallY(int index, int ball)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not get trackball status of gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return 0;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not get trackball status of gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return 0;
		}

		if(ball >= numBalls(index))
		{
			std::stringstream err;
			err << "Could not get trackball status of gamepad with index " << index << ": Trackball " << ball << " is invalid.";
			core->error(err.str().c_str());
			return 0;
		}

		int dx;
		int dy;

		SDL_JoystickGetBall(SDL_JoystickOpen(index), ball, &dx, &dy);
		return dy;
	}

	int getButton(int index, int button)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not get button status of gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return 0;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not get button status of gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return 0;
		}

		if(button >= numButtons(index))
		{
			std::stringstream err;
			err << "Could not get button status of gamepad with index " << index << ": Button " << button << " is invalid.";
			core->error(err.str().c_str());
			return 0;
		}

		return SDL_JoystickGetButton(SDL_JoystickOpen(index), button);
	}

	int getHat(int index, int hat)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not get viewhat status of gamepad with index " << index << ": Invalid gamepad index.";
			core->error(err.str().c_str());
			return 0;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not get viewhat status of gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return 0;
		}

		if(hat >= numHats(index))
		{
			std::stringstream err;
			err << "Could not get viewhat status of gamepad with index " << index << ": Hat " << hat << " is invalid.";
			core->error(err.str().c_str());
			return 0;
		}

		return SDL_JoystickGetHat(SDL_JoystickOpen(index), hat);
	}

	void close(int index)
	{
		if(!checkIndex(index))
		{
			std::stringstream err;
			err << "Could not close gamepad with index " << index << ": Invalid index.";
			core->error(err.str().c_str());
			return;
		}

		if(!isOpen(index))
		{
			std::stringstream err;
			err << "Could not close gamepad with index " << index << ": Gamepad is not open.";
			core->error(err.str().c_str());
			return;
		}

		return SDL_JoystickClose(SDL_JoystickOpen(index));
	}

} // love_sdljoystick
