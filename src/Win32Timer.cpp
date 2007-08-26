#include "Win32Timer.h"

namespace love
{

	Win32Timer::Win32Timer()
	{
		// Get frequency from counter
		BOOL success = QueryPerformanceFrequency(&pc_frequency);
			
		if(!success)
			printf("QueryPerformanceFrequency FAILED\n");
		else
			QueryPerformanceCounter(&pc_start);

		pc_last = pc_start;
		prev_fps_update = pc_last;

		printf("Using W32 Timer ..\n");
	}

	Win32Timer::~Win32Timer()
	{
	}


	float Win32Timer::getDelta()
	{

		frames++;

		static LARGE_INTEGER s_lastTime = pc_start;
		LARGE_INTEGER currentTime;

		QueryPerformanceCounter(&currentTime);

		float seconds =  ((float)currentTime.QuadPart - (float)s_lastTime.QuadPart) / (float)pc_frequency.QuadPart;

		// Update FPS?
		if(((float)currentTime.QuadPart - (float)prev_fps_update.QuadPart) / (float)pc_frequency.QuadPart > getFpsUpdateFrequency())
		{
			setFps(frames/getFpsUpdateFrequency());
			prev_fps_update = currentTime;
			frames = 0;
		}

		// reset the timer
		s_lastTime = currentTime;

		if(seconds < 0)
			printf("Timer: WTF: %f: \n", seconds);


		return seconds;
	}


}// love
