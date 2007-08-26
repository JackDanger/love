/**
* @file Win32Timer.h
* @author Anders Ruud
* @date 2006-10-21
* @brief Contains definition for class Win32Timer.
**/

#ifndef LOVE_WIN32TIMER_H
#define LOVE_WIN32TIMER_H

#include <windows.h>

// LOVE
#include "Timer.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Win32Timer
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-10-21
	* @brief 
	**/
	class Win32Timer : public Timer
	{
	private:

		LARGE_INTEGER pc_frequency;
		LARGE_INTEGER pc_start;
		LARGE_INTEGER pc_current;
		LARGE_INTEGER pc_last;
		LARGE_INTEGER prev_fps_update;

	public:

		/**
		* @brief Contructs a new Win32Timer.
		**/
		Win32Timer();
		virtual ~Win32Timer();

		/**
		* @brief Gets seconds since last call to this method.
		* @return Seconds since last call to this method.
		**/
		float getDelta();

	};

	typedef boost::shared_ptr<Win32Timer> pWin32Timer;

} // love

#endif
