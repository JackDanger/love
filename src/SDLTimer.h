/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SDLTIMER_H
#define LOVE_SDLTIMER_H

// SDL
#include "SDL/SDL.h"

// LOVE
#include "Timer.h"


namespace love
{

	/**
	* SDL Timer class.
	*
	* @author Anders Ruud
	* @date 2006-10-21
	**/
	class SDLTimer : public Timer
	{
	private:

		Uint32 currTime;
		Uint32 prevTime;
		Uint32 prevFpsUpdate;

		// Benchmark variables
		Uint32 bench_start;
		Uint32 bench_end;

	public:

		/**
		* Constructs a new SDLTImer.
		**/
		SDLTimer();

		virtual ~SDLTimer();

		// From Timer.
		float getDelta();
		void startBenchmark();
		float endBenchmark();

	}; // SDLTimer

} // love

#endif // LOVE_SDLTIMER_H
