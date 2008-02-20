/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_TIMER_H
#define LOVE_TIMER_H

// LOVE
#include "Device.h"

namespace love
{

	/**
	* Superclass for all timers.
	* 
	* @author Anders Ruud
	* @date 2006-10-21
	**/
	class Timer : public Device
	{
		// Friend functions
		friend int platform_loop();
		friend class NoGame;

	protected:

		// Updated with a certain frequency.
		float fps;

		// The frequency by which to update the FPS.
		float fpsUpdateFrequency;

		// Frames since last FPS update.
		int frames;

		// Millisecond timer cap (in seconds).
		float max;
		float max_buffer;

		// The current timestep.
		float dt;

	public:

		/**
		* Inits some member variables.
		**/
		Timer();

		virtual ~Timer();

		// From Device.
		bool init(int argc, char* argv[]);
		void quit();
		
		/**
		* Updates the timer. This method may sleep if FPS
		* capping is enabled.
		**/
		virtual void update() = 0;

		/**
		* Gets seconds since last call to this method.
		**/
		virtual float getDelta() = 0;

		/**
		* Resets benchmarking variables.
		**/
		virtual void startBenchmark() = 0;

		/**
		* Returns the time since startBenchmark was last called.
		**/
		virtual float endBenchmark() = 0;

		/**
		* Gets the FPS.
		**/
		float getFps() const;

		/**
		* Sets the current max frame rate.
		**/
		void setCap(float fps);

		/**
		* Gets the current max framerate.
		**/
		float getCap() const;


	}; // Timer

} // love

#endif // LOVE_TIMER_H
