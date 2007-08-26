/**
* @file MouseListener.h
* @brief Contains definition of class MouseListener.
* @date 2006-04-20
* @author Anders Ruud
**/

#ifndef LOVE_MOUSELISTENER_H
#define LOVE_MOUSELISTENER_H

#include "Listener.h"

namespace love 
{

	/**
	* @class MouseListener
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-04-20
	* @brief
	**/
	class MouseListener : public Listener
	{
	private:

	public:


		/**
		* @brief Called when the mouse is pressed.
		* @param x The x-coordinate of the mousepress.
		* @param y The y-coordinate of the mousepress.
		* @param button The button that was pressed.
		**/
		virtual void mousePressed(float x, float y, int button)	= 0;

		/**
		* @brief Called when the mouse is released.
		* @param x The x-coordinate of the mouserelease.
		* @param y The y-coordinate of the mouserelease.
		* @param button The button that was released.
		**/
		virtual void mouseReleased(float x, float y, int button)	= 0;

	};
	
}

#endif
