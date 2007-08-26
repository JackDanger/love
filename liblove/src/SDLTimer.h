/**
* @file SDLTimer.h
* @author Anders Ruud
* @date 2006-10-21
* @brief Contains definition for class SDLTimer.
**/

#ifndef LOVE_SDLTIMER_H
#define LOVE_SDLTIMER_H

#include "SDL/SDL.h"

// LOVE
#include "Timer.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class SDLTimer
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-10-21
	* @brief 
	**/
	class SDLTimer : public Timer
	{
	private:

		Uint32 currTime;
		Uint32 prevTime;
		Uint32 prevFpsUpdate;

	public:

		/**
		* @brief Contructs an empty SDLTimer.
		**/
		SDLTimer();
		virtual ~SDLTimer();
	
		/**
		* @brief Gets seconds since last call to this method.
		* @return Seconds since last call to this method.
		**/
		float getDelta();

	};

	typedef boost::shared_ptr<SDLTimer> pSDLTimer;

} // love

#endif
