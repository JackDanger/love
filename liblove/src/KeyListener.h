/**
* @file KeyListener.h
* @brief Contains definition of class KeyListener.
* @date 2006-03-06
* @author Anders Ruud
**/

#ifndef LOVE_KEYLISTENER_H
#define LOVE_KEYLISTENER_H

#include "Listener.h"

namespace love 
{

	/**
	* @class KeyListener
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-01-15
	* @brief
	**/
	class KeyListener : public Listener
	{
	private:

	public:

		/**
		* @brief Called when a key is pressed.
		* @param key The ASCII key code.
		**/
		virtual void keyPressed(int key) = 0;

		/**
		* @brief Called when a key is released.
		* @param key The ASCII key code.
		**/
		virtual void keyReleased(int key) = 0;

	};
	
}

#endif
