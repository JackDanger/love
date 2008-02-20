/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_MOUSE_H
#define LOVE_MOUSE_H

// LOVE
#include "Device.h"

namespace love
{

	/**
	* Abstract Mouse device class.
	*
	* @author Anders Ruud
	* @date 2006-12-01
	**/
	class Mouse : public Device
	{
	protected:
	public:

		virtual ~Mouse();

		/**
		* Gets current mouse position on x-axis.
		**/
		virtual float getX() const = 0;

		/**
		* Gets current mouse position on x-axis.
		**/
		virtual float getY() const = 0;

		/**
		* Sets the mouse position along the x-axis.
		**/
		virtual void setX(float x) = 0;

		/**
		* Sets the mouse position along the y-axis.
		**/
		virtual void setY(float y) = 0;

		/**
		* Sets the mouse position.
		**/
		virtual void setPosition(float x, float y) = 0;

		/**
		* Checks if a mouse button is pressed.
		**/
		virtual bool isDown(int button) const = 0;

		/**
		* Hides/shows the Mouse.
		* @param visible True = visible, false = invisible.
		**/
		virtual void setVisible(bool visible) = 0;

		/**
		* Returns true if the mouse is visible, false otherwise.
		**/
		virtual bool isVisible() const = 0;

	}; // Mouse

} // love

#endif // LOVE_MOUSE_H
