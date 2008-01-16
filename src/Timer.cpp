#include "Timer.h"

namespace love
{
	Timer::Timer() : fps(0), fpsUpdateFrequency(1.0f)
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

}// love
