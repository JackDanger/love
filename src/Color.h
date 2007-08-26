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
		 * @brief Initializes all the variables with the appropriate values and with alpha being 255.
		 **/
		Color(int red, int green, int blue);

		/**
		 * @param red The amount of red.
		 * @param green The amount of green.
		 * @param blue The amount of blue.
		 * @param alpah The amount of alpha.
		 * @brief Initializes all the variables with the appropriate values.
		 **/
		Color(int red, int green, int blue, int alpha);

		/**
		 * @param red The amount of red (a value between 0 and 1).
		 * @param green The amount of green (a value between 0 and 1).
		 * @param blue The amount of blue (a value between 0 and 1).
		 * @brief Initializes all the variables with the appropriate values and with alpha being 255.
		 **/
		Color(float red, float green, float blue);

		/**
		 * @param red The amount of red (a value between 0 and 1).
		 * @param green The amount of green (a value between 0 and 1).
		 * @param blue The amount of blue (a value between 0 and 1).
		 * @param alpha The amount of alpha (a value between 0 and 1).
		 * @brief Initializes all the variables with the appropriate values.
		 **/
		Color(float red, float green, float blue, float alpha);

		/**
		 * @brief Does nothing.
		 **/
		~Color();

		/**
		 * @param value The amount of red.
		 * @brief Sets the amount of red to the new value.
		 **/
		void setRed(int value);

		/**
		 * @param value The amount of red (a value between 0 and 1).
		 * @brief Sets the amount of red to the new value.
		 **/
		void setRed(float value);

		/**
		 * @param value The amount of blue.
		 * @brief Sets the amount of blue to the new value.
		 **/
		void setBlue(int value);

		/**
		 * @param value The amount of blue (a value between 0 and 1).
		 * @brief Sets the amount of blue to the new value.
		 **/
		void setBlue(float value);

		/**
		 * @param value The amount of green.
		 * @brief Sets the amount of green to the new value.
		 **/
		void setGreen(int value);

		/**
		 * @param value The amount of green (a value between 0 and 1).
		 * @brief Sets the amount of green to the new value.
		 **/
		void setGreen(float value);

		/**
		 * @param value The amount of alpha.
		 * @brief Sets the amount of alpha to the new value.
		 **/
		void setAlpha(int value);

		/**
		 * @param value The amount of alpha (a value between 0 and 1).
		 * @brief Sets the amount of alpha to the new value.
		 **/
		void setAlpha(float value);

		/**
		 * @param code The color code (in the syntax: 0xRRGGBB).
		 * @brief Sets the variables with the values derived from the color code.
		 **/
		void setColor(int code);

		/**
		 * @param red The amount of red.
		 * @param green The amount of green.
		 * @param blue The amount of blue.
		 * @brief Sets the variables to the approriate new values.
		 **/
		void setColor(int red, int green, int blue);

		/**
		 * @param red The amount of red.
		 * @param green The amount of green.
		 * @param blue The amount of blue.
		 * @param alpha The amount of alpha.
		 * @brief Sets the variables to the approriate new values.
		 **/
		void setColor(int red, int green, int blue, int alpha);

		/**
		 * @param red The amount of red (a value between 0 and 1).
		 * @param green The amount of green (a value between 0 and 1).
		 * @param blue The amount of blue (a value between 0 and 1).
		 * @brief Sets the variables to the approriate new values.
		 **/
		void setColor(float red, float green, float blue);

		/**
		 * @param red The amount of red (a value between 0 and 1).
		 * @param green The amount of green (a value between 0 and 1).
		 * @param blue The amount of blue (a value between 0 and 1).
		 * @param alpha The amount of alpha (a value between 0 and 1).
		 * @brief Sets the variables to the approriate new values.
		 **/
		void setColor(float red, float green, float blue, float alpha);


		/**
		 * @param other The other color.
		 * @param amount The amount of gradient (a value between 0 and 1).
		 * @brief Gets a gradient between this color and the other color determined by the amount.
		 **/
		Color getGradient(Color * other, float amount);

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
