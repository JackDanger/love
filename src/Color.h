#ifndef LOVE_COLOR_H
#define LOVE_COLOR_H

#include "AbstractColor.h"

namespace love
{
	/**
	 * @class Color
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2006-08-16
	 * @brief The class for handling static colors.
	 **/
	class Color : public AbstractColor
	{
	public:
		/**
		 * @brief Initializes all the variables with a value of 255 (which results in an opaque white).
		 **/
		Color();

		/**
		 * @param code The color code (in the syntax: 0xRRGGBB).
		 * @brief Initializes all the variables with the values derived from the color code and with alpha being 255.
		 **/
		Color(int code);

		/**
		 * @param red The amount of red.
		 * @param green The amount of green.
		 * @param blue The amount of blue.
		 * @param alpah The amount of alpha.
		 * @brief Initializes all the variables with the appropriate values.
		 **/
		Color(int red, int green, int blue, int alpha = 255);

		/**
		 * @brief Does nothing.
		 **/
		~Color();

		/**
		 * @brief Sets the color using function value t.
		 * @param t A value of 0 to 1 representing the start and the end of the dynamic color.
		 **/
		virtual void setColor(float t);

		/**
		 * @param dt The elapsed time (in milliseconds).
	 	 * @brief Does nothing.
	 	 **/
		virtual void update(float dt);
	};

	typedef boost::shared_ptr<Color> pColor;
}

#endif
