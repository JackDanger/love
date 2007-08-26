#include "SDLTimer.h"

namespace love
{

	SDLTimer::SDLTimer(): currTime(0), prevTime(0), prevFpsUpdate(0)
	{
		
	}

	SDLTimer::~SDLTimer()
	{
	}
	
	float SDLTimer::getDelta()
	{
		
		// Frame rendered
		frames++;
			
		// "Current" time is previous time by now.
		prevTime = currTime;

		// Get ticks from SDL
		currTime = SDL_GetTicks();

		// Convert to number of seconds
		float dt = (currTime - prevTime)/1000.0f;

		// Update FPS?
		if((currTime - prevFpsUpdate)/1000.0f > getFpsUpdateFrequency())
		{
			setFps(frames/getFpsUpdateFrequency());
			prevFpsUpdate = currTime;
			frames = 0;
		}

		if(dt < 0)
			printf("Timer: WTF: %f: \n", dt);

		return dt;
	}


}// love
