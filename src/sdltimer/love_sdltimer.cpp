#include "love_sdltimer.h"

// SDL
#include <SDL.h>

// From SWIG.
extern "C" {
	int luaopen_mod_sdltimer(lua_State * L);
}

namespace love_sdltimer
{

	Uint32 currTime = 0;
	Uint32 prevTime;
	Uint32 prevFpsUpdate = 0;

	// Updated with a certain frequency.
	float fps = 0;

	// The frequency by which to update the FPS.
	float fpsUpdateFrequency = 1;

	// Frames since last FPS update.
	int frames = 0;

	// The current timestep.
	float dt = 0;

	bool init(love_mod::modconf * conf)
	{
		
		// Init the SDL timer system.
		if(SDL_InitSubSystem(SDL_INIT_TIMER) < 0)
		{
			std::cout << "Could not init SDL_TIMER: " << SDL_GetError() << std::endl;
			return false;
		}

		love_mod::setConf(conf);
		love_mod::report_init("love.timer", "SDL");

		return true;
	}

	bool quit()
	{
		SDL_QuitSubSystem(SDL_INIT_TIMER);
		love_mod::report_init("love.timer", "Shutdown");
		return true;
	}

	bool luaopen(lua_State * s)
	{
		love_mod::setL(s);
		luaopen_mod_sdltimer(s);
		love_mod::do_string("love.timer = mod_sdltimer");
		return true;
	}

	void step()
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

		if(dt < 0)
			printf("Timer: WTF: %f: \n", dt);
	}

	float getDelta()
	{
		return dt;
	}

	float getFPS()
	{
		return fps;
	}

	void sleep(int ms)
	{
		SDL_Delay(ms);
	}

} // love_sdltimer
