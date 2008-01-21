/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_COLOR_H
#define LOVE_COLOR_H

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	 * Bah.
	 * 
	 * @author Michael Enger
	 * @date 2007-05-22
	 **/
	class Color
	{
		friend class AnimatedColor;

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

} // love

#endif // LOVE_COLOR_H
