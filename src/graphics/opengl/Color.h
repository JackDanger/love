/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Michael Enger
* @date 2007-05-22
**/

#ifndef LOVE_GRAPHICS_OPENGL_COLOR_H
#define LOVE_GRAPHICS_OPENGL_COLOR_H

// LOVE
#include "../../Object.h"

namespace love
{
namespace graphics
{
namespace opengl
{

	class Color : public Object
	{
	protected:

		// Color components. (0-255)
		int red, green, blue, alpha;
		
	public:

		Color();

		/**
		 * Creates a new color with the specified component values.
		 * Values must be unsigned bytes. (0-255).
		 **/
		Color(int r, int g, int b, int a);

		virtual ~Color();

		/**
		 * Sets the amount of red in the color.
		 **/
		void setRed(int red);

		/**
		 * Sets the amount of green in the color.
		 **/
		void setGreen(int green);

		/**
		 * Sets the amount of blue in the color.
		 **/
		void setBlue(int blue);

		/**
		 * Sets the amount of alpha.
		 **/
		void setAlpha(int alpha);

		/**
		 * Returns the amount of red in the color.
		 **/
		int getRed() const;

		/**
		 * Returns the amount of green in the color.
		 **/
		int getGreen() const;

		/**
		 * Returns the amount of blue in the color.
		 **/
		int getBlue() const;

		/**
		 * Returns the amount of alpha.
		 **/
		int getAlpha() const;

	}; // Color

} // opengl
} // graphics
} // love

#endif // LOVE_GRAPHICS_OPENGL_COLOR_H
