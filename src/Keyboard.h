/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_KEYBOARD_H
#define LOVE_KEYBOARD_H

// LOVE
#include "Device.h"

namespace love
{

	/**
	* Abstract keyboard class.
	*
	* @author Anders Ruud
	* @date 2006-03-12
	**/
	class Keyboard : public Device
	{
	private:
	public:

		virtual ~Keyboard();

		/**
		* Checks whether a key is down or not.
		**/
		virtual bool isDown(int key) const = 0;

	}; // Keyboard

}// love

#endif // LOVE_KEYBOARD_H
