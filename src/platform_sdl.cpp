#include "platform.h"

// LOVE
#include "love.h"
#include "using_gl.h"
#include "SDLDisplay.h"
#include "SDLTimer.h"
#include "Graphics.h"
#include "PhysFSFilesystem.h"
#include "SDLMixerAudio.h"
#include "SDLMouse.h"
#include "SDLKeyboard.h"


#ifdef W32
#include "Win32Timer.h"
#endif

// STD
#include <cmath>

namespace love
{

	int platform_init(int argc, char* argv[])
	{

		// Init SDL
		if(SDL_Init(0))
		{
			printf("Could not init SDL: %s\n", SDL_GetError());
			return 1;
		}

		// Create devices.
		display = new SDLDisplay();
		graphics = display->getGraphics();
		audio = new SDLMixerAudio();
		timer = new SDLTimer();
		//timer = new Win32Timer();
		filesystem = new PhysFSFilesystem();
		mouse = new SDLMouse();
		keyboard = new SDLKeyboard();

		// Init love.
		if(!love::init(argc, argv))
			return 1;

		return 0;
	}

	void platform_free()
	{
		// Call love::free.
		free();

		// Delete devices.
		delete display;
		delete graphics;
		delete audio;
		delete timer;
		delete filesystem;
		delete mouse;
		delete keyboard;

		// Quit SDL.
		SDL_Quit();
	}

	int platform_loop()
	{

		// Enable UNICODE. This is needed for input to work properly.
		// And yes, this only worked here.
		SDL_EnableUNICODE(1);

		// The union used to get SDL events. 
		SDL_Event e;

		// Main loop.
		while(1)
		{

			// Get the time since last time.
			float dt = timer->getDelta();

			// Update everything.
			update(dt);

			// Render everything.
			render();

			// Process events.
			while(SDL_PollEvent(&e))
			{

				// Do events.
				switch(e.type)
				{
					case SDL_KEYDOWN:
						key_pressed(e.key.keysym.sym);
						break;
					case SDL_KEYUP:
						key_released(e.key.keysym.sym);
						break;
					case SDL_MOUSEBUTTONDOWN:
						mouse_pressed(e.button.x, e.button.y, e.button.button);
						break;
					case SDL_MOUSEBUTTONUP:
						mouse_released(e.button.x, e.button.y, e.button.button);
						break;
					case SDL_MOUSEMOTION:
						//mouse_moved(e.motion.x, e.motion.y);
						break;
					case SDL_QUIT:
						platform_free();
						return 0;
					default:
						break;
				}
			}

			// Show buffer on screen. 
			SDL_GL_SwapBuffers();
		}

		return 0;
	}

	void platform_quit()
	{
		// Send quit message.
		SDL_Event e;
		e.type = SDL_QUIT;
		SDL_PushEvent(&e);
	}
}

