/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_WIN32TIMER_H
#define LOVE_WIN32TIMER_H

#include <windows.h>

// LOVE
#include "Timer.h"

// STD
#include <vector>

namespace love
{

	/**
	* Windows specific timer class.
	*
	* @author Anders Ruud
	* @date 2006-10-21
	**/
	class Win32Timer : public Timer
	{
	private:

		LARGE_INTEGER pc_frequency;
		LARGE_INTEGER pc_start;
		LARGE_INTEGER pc_current;
		LARGE_INTEGER pc_last;
		LARGE_INTEGER prev_fps_update;

		// Data for one benchmark.
		LARGE_INTEGER bench_start;
		LARGE_INTEGER bench_end;

	public:

		Win32Timer();

		virtual ~Win32Timer();

		
		// From Timer
		float getDelta();
		void startBenchmark();
		float endBenchmark();

	}; // Win32Timer

} // love

#endif // LOVE_WIN32TIMER_H
