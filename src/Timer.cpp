#include "Timer.h"

namespace love
{
	Timer::Timer() : fps(0), fpsUpdateFrequency(1.0f), frames(0), max(0), max_buffer(0), dt(0)
	{
	}

	Timer::~Timer()
	{
		quit();
	}

	bool Timer::init(int argc, char* argv[])
	{
		getDelta();
		return true;
	}

	void Timer::quit()
	{
	}

	float Timer::getFps() const
	{
		return fps;
	}

	void Timer::setCap(float fps)
	{
		max = 1.0f/fps;
		max_buffer = 0;
	}

	float Timer::getCap() const
	{
		return max;
	}

}// love
