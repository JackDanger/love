/**
* @file MouseListener.h
* @brief Contains definition of class MouseListener.
* @date 2006-08-25
* @author Anders Ruud
**/

#ifndef LOVE_MOUSE_MOTION_LISTENER_H
#define LOVE_MOUSE_MOTION_LISTENER_H

#include "Listener.h"

namespace love 
{

	/**
	* @class MouseMotionListener
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-08-25
	* @brief
	**/
	class MouseMotionListener : public Listener
	{
	private:

	public:

		/**
		* @brief Called every time the mouse is moved.
		* @param x The current position of the mouse along the x axis.
		* @param y The current position of the mouse along the y axis.
		**/
		virtual void mouseMoved(float x, float y) = 0;

	};
	
}

#endif
