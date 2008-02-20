#include "SDLTimer.h"

namespace love
{

	SDLTimer::SDLTimer(): currTime(0), prevTime(0), prevFpsUpdate(0)
	{
	}

	SDLTimer::~SDLTimer()
	{
	}

	void SDLTimer::update()
	{
		// If there's no cap, just update the value.
		if(max <= 0)
		{
			this->dt = getDelta();
			return;
		}

		// There is a cap:
		float diff = max - dt;

		if(diff > 0)
		{
			// Wait a little.
			SDL_Delay((int)(diff * 1000.0f));
			this->dt = getDelta();
			return;
		}

		this->dt =  getDelta();
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
		if((currTime - prevFpsUpdate)/1000.0f > fpsUpdateFrequency)
		{
			fps = frames/fpsUpdateFrequency;
			prevFpsUpdate = currTime;
			frames = 0;
		}

		if(dt < 0)
			printf("Timer: WTF: %f: \n", dt);

		return dt;
	}

	void SDLTimer::startBenchmark()
	{
		bench_start = SDL_GetTicks();
	}

	float SDLTimer::endBenchmark()
	{
		bench_end = SDL_GetTicks();
		return (bench_end - bench_start)/1000.0f;
	}

}// love
