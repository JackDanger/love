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
		 * @param red The amount of red (a value between 0 and 1).
		 * @param green The amount of green (a value between 0 and 1).
		 * @param blue The amount of blue (a value between 0 and 1).
		 * @param alpha The amount of alpha (a value between 0 and 1).
		 * @brief Initializes all the variables with the appropriate values.
		 **/
		//Color(float red, float green, float blue, float alpha = 1.0);

		/**
		 * @brief Does nothing.
		 **/
		~Color();

		/**
		 * @param value The amount of red (a value between 0 and 1).
		 * @brief Sets the amount of red to the new value.
		 **/
		//void setRed(float value);

		/**
		 * @param value The amount of blue (a value between 0 and 1).
		 * @brief Sets the amount of blue to the new value.
		 **/
		//void setBlue(float value);

		/**
		 * @param value The amount of green (a value between 0 and 1).
		 * @brief Sets the amount of green to the new value.
		 **/
		//void setGreen(float value);

		/**
		 * @param value The amount of alpha (a value between 0 and 1).
		 * @brief Sets the amount of alpha to the new value.
		 **/
		//void setAlpha(float value);

		/**
		 * @param red The amount of red (a value between 0 and 1).
		 * @param green The amount of green (a value between 0 and 1).
		 * @param blue The amount of blue (a value between 0 and 1).
		 * @brief Sets the variables to the approriate new values.
		 **/
		//void setColor(float red, float green, float blue);

		/**
		 * @param red The amount of red (a value between 0 and 1).
		 * @param green The amount of green (a value between 0 and 1).
		 * @param blue The amount of blue (a value between 0 and 1).
		 * @param alpha The amount of alpha (a value between 0 and 1).
		 * @brief Sets the variables to the approriate new values.
		 **/
		//void setColor(float red, float green, float blue, float alpha);

		/**
		 * @param dt The elapsed time (in milliseconds).
	 	 * @brief Does nothing.
	 	 **/
		void update(float dt);

		virtual void setColor(float t);
	};

	typedef boost::shared_ptr<Color> pColor;
}

#endif
