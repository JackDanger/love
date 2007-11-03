#include "Timer.h"

#include "love.h"

namespace love
{

	Timer::Timer() : fps(0), fpsUpdateFrequency(1.0f), lockedFps(0), maxFps(0), minFps(0), numAverage(10)
	{
		setType(LOVE_TYPE_TIMER);
	}

	Timer::~Timer()
	{
	}

	int Timer::init()
	{
		getDelta();
		return LOVE_OK;
	}

	unsigned int Timer::getFrames() const
	{
		return frames;
	}

	void Timer::setFrames(unsigned int frames)
	{
		this->frames = frames;
	}

	float Timer::getFpsUpdateFrequency() const
	{
		return fpsUpdateFrequency;
	}

	void Timer::setFpsUpdateFrequency(float fpsUpdateFrequency)
	{
		this->fpsUpdateFrequency = fpsUpdateFrequency;
	}

	float Timer::getFps() const
	{
		return fps;
	}

	void Timer::setFps(float fps)
	{
		this->fps = fps;
	}

	float Timer::getLockedFps() const
	{
		return lockedFps;
	}

	void Timer::setLockedFps(float lockedFps)
	{
		this->lockedFps = lockedFps;
	}

	float Timer::getMaxFps() const
	{
		return maxFps;
	}

	void Timer::setMaxFps(float maxFps)
	{
		this->maxFps = maxFps;
	}

	float Timer::getMinFps() const
	{
		return minFps;
	}

	void Timer::setMinFps(float minFps)
	{
		this->minFps = minFps;
	}

	void Timer::addValue(float dt)
	{
		// Add the value.
		lastValues.push_back(dt);

		// Remove old, if above limit.
		while((int)lastValues.size() > numAverage)
			lastValues.pop_front();
	}


	float Timer::getAverage() const
	{
		float total = 0;

		// Collect total.
		for(deque<float>::const_iterator i = lastValues.begin(); i != lastValues.end(); i++)
		{
			total += *i;
		}


		float avg = total / lastValues.size();

		return avg;
	}


}// love
