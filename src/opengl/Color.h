/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_COLOR_H
#define LOVE_OPENGL_COLOR_H

// Boost
#include <boost/shared_ptr.hpp>

namespace love_opengl
{
	/**
	 * Bah.
	 * 
	 * @author Michael Enger
	 * @date 2007-05-22
	 **/
	class Color
	{
	protected:

		// Color components. (0-255)
		int red, green, blue, alpha;
		
	public:

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

		/**
		 * Updates the color.
	 	 **/
		virtual void update(float dt);

	}; // Color

	typedef boost::shared_ptr<Color> pColor;

} // love_opengl

#endif // LOVE_OPENGL_COLOR_H
