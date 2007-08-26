/**
* @file Timer.h
* @author Anders Ruud
* @date 2006-10-21
* @brief Contains definition for class Timer.
**/

#ifndef LOVE_TIMER_H
#define LOVE_TIMER_H

// LOVE
#include "AbstractDevice.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Timer
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-10-21
	* @brief 
	**/
	class Timer : public AbstractDevice
	{
	private:

		// fps
		float fps;

		// fpsUpdateFrequency
		float fpsUpdateFrequency;

		// lockedFps
		float lockedFps;

		// maxFps
		float maxFps;

		// minFps
		float minFps;

	protected:

		// Frames since last FPS update.
		unsigned int frames;

	public:

		/**
		* @brief Contructs an empty Timer.
		**/
		Timer();
		virtual ~Timer();

		/**
		* @brief Starts timer.
		**/
		virtual int init();
		
		/**
		* @brief Gets seconds since last call to this method.
		* @return Seconds since last call to this method.
		**/
		virtual float getDelta() = 0;

		/**
		* @brief Gets frames.
		* @return frames.
		**/
		unsigned int getFrames() const;


		/**
		* @brief Sets frames.
		* @param frames 
		**/
		void setFrames(unsigned int frames);


		/**
		* @brief Gets fpsUpdateFrequency.
		* @return fpsUpdateFrequency.
		**/
		float getFpsUpdateFrequency() const;


		/**
		* @brief Sets fpsUpdateFrequency.
		* @param fpsUpdateFrequency 
		**/
		void setFpsUpdateFrequency(float fpsUpdateFrequency);


		/**
		* @brief Gets fps.
		* @return fps.
		**/
		float getFps() const;


		/**
		* @brief Sets fps.
		* @param fps 
		**/
		void setFps(float fps);


		/**
		* @brief Gets lockedFps.
		* @return lockedFps.
		**/
		float getLockedFps() const;


		/**
		* @brief Sets lockedFps.
		* @param lockedFps 
		**/
		void setLockedFps(float lockedFps);


		/**
		* @brief Gets maxFps.
		* @return maxFps.
		**/
		float getMaxFps() const;


		/**
		* @brief Sets maxFps.
		* @param maxFps 
		**/
		void setMaxFps(float maxFps);


		/**
		* @brief Gets minFps.
		* @return minFps.
		**/
		float getMinFps() const;


		/**
		* @brief Sets minFps.
		* @param minFps 
		**/
		void setMinFps(float minFps);


	};

	typedef boost::shared_ptr<Timer> pTimer;

} // love

#endif
