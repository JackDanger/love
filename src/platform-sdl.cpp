#include "platform.h"

// love.h contains love::core (and moar)
#include "Core.h"
#include "love.h"


// SDL header needed for any SDL-stuff at all.
#include "SDL/SDL.h"

// GLee needed for OpenGL 2.0+ support.
#include "GLee.h"

// SDL_opengl makes SDL able of setting up an OpenGL context.
#include "SDL/SDL_opengl.h"

// Include the devices this platform uses.
#include "SDLDisplay.h"
#include "SDLTimer.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "PhysFSFileSystem.h"
#include "SDLMixerSoundDevice.h"
#include "DevILImageDevice.h"
#include "OpenGLGraphics.h"
#include "lualove_globals.h"
#include "Parameters.h"

#include <IL/il.h>

#include <cmath>


// Declare this external bastard here
// @todo MAKE GENERIC
//gcn::SDLInput * gcn_input;



namespace love
{

	int platform_init(int argc, char* argv[])
	{

		// Init SDL
		if(SDL_Init(0))
		{
			printf("Could not init SDL: %s\n", SDL_GetError());
			return LOVE_ERROR;
		}


		
		// Assign devices
		core->display = new SDLDisplay();
		core->timer = new SDLTimer();
		core->mouse = new Mouse();
		core->keyboard = new Keyboard();
		core->filesystem = new PhysFSFileSystem(argc, argv);
		core->audio = new SDLMixerSoundDevice();
		core->imaging = new DevILImageDevice();
		core->graphics = new OpenGLGraphics();
		core->parameters = new Parameters(argc, argv);

		// Init GuiChan here
		// @todo MAKE GENERIC
		//gcn_input = new gcn::SDLInput();

		return LOVE_OK;
	}

	int platform_loop()
	{

		// Enable UNICODE. This is needed for input to work properly.
		// And yes, this only worked here.
		SDL_EnableUNICODE(1);

		// The union used to get SDL events. 
		SDL_Event e;


		while(1)
		{
		
			// Get the time since last time.
			float dt = core->timer->getDelta();

			// Tell core to update.
			core->update(dt);

			// Tell core to render
			core->render();

			// Main loop
			while(SDL_PollEvent(&e))
			{

				// Pass input to GuiChan
				// @todo MAKE GENERIC
				//gcn_input->pushInput(e);
		
				// Do events.
				switch(e.type)
				{
				case SDL_KEYDOWN:
						core->keyPressed(e.key.keysym.sym);
						break;
					case SDL_KEYUP:
						core->keyReleased(e.key.keysym.sym);
						break;
					case SDL_MOUSEBUTTONDOWN:
						core->mousePressed(e.button.x, e.button.y, (int)pow(2, (float)(e.button.button-1)));
						//printf("Pressed: %i\n", e.button.button);
						break;
					case SDL_MOUSEBUTTONUP:
						core->mouseReleased(e.button.x, e.button.y, (int)pow(2, (float)(e.button.button-1)));
						//printf("Released: %i\n", e.button.button);
						break;
					case SDL_MOUSEMOTION:
						core->mouseMoved(e.motion.x, e.motion.y);
						break;
					case SDL_QUIT:
						return LOVE_OK;
					default:
						break;
				}
			}

			// Show buffer on screen. 
			SDL_GL_SwapBuffers();
			
			// Save some CPU
			if(dt < 0.008f)
				SDL_Delay((int)((0.008f - dt)*1000.0f));

		}
	}

	void platform_quit()
	{
		// Create quit event
		SDL_Event e;
		e.type = SDL_QUIT;

		// Push onto queue.
		SDL_PushEvent(&e);
	}
}

