#ifndef LOVE_ABSTRACT_COLOR_H
#define LOVE_ABSTRACT_COLOR_H

#include "Object.h"
#include "Updateable.h"
#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	 * @class AbstractColor
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2007-05-22
	 * @brief The abstract parent class of Color and AnimatedColor.
	 **/
	class AbstractColor : public Object, public Updateable
	{
	protected:
		int red, green, blue, alpha;
		
	public:
		static const int LOVE_COLOR_BLACK  = 0x000000;
		static const int LOVE_COLOR_WHITE  = 0xFFFFFF;
		static const int LOVE_COLOR_RED    = 0xFF0000;
		static const int LOVE_COLOR_GREEN  = 0x00FF00;
		static const int LOVE_COLOR_BLUE   = 0x0000FF;
		static const int LOVE_COLOR_YELLOW = 0xFFFF00;
		static const int LOVE_COLOR_CYAN   = 0x00FFFF;
		static const int LOVE_COLOR_MAGENTA= 0xFF00FF;

		/**
		 * @brief Initializes all the variables with a value of 255 (which results in an opaque white).
		 **/
		AbstractColor();

		/**
		 * @brief Does nothing.
		 **/
		~AbstractColor();

		/**
		 * @return The amount of red.
		 * @brief Returns the amount of red is in the color.
		 **/
		int getRed() const;

		/**
		 * @return The amount of green.
		 * @brief Returns the amount of green is in the color.
		 **/
		int getGreen() const;

		/**
		 * @return The amount of blue.
		 * @brief Returns the amount of blue is in the color.
		 **/
		int getBlue() const;

		/**
		 * @return The amount of alpha.
		 * @brief Returns the amount of alpha.
		 **/
		int getAlpha() const;

		/**
		 * @return The color code.
		 * @brief Formats the color values into a color code (syntax: 0xRRGGBB).
		 **/
		int getCode() const;

		/**
		 * @param red The amount of red.
		 * @brief Sets the amount of red.
		 **/
		void setRed(int red);

		/**
		 * @param green The amount of green.
		 * @brief Sets the amount of green.
		 **/
		void setGreen(int green);

		/**
		 * @param blue The amount of blue.
		 * @brief Sets the amount of blue.
		 **/
		void setBlue(int blue);

		/**
		 * @param alpha The amount of alpha.
		 * @brief Sets the amount of alpha.
		 **/
		void setAlpha(int alpha);

		/**
		* @brief Sets the color using function value t.
		* @param t A value of 0 to 1 representing the start and the end of the dynamic color.
		**/
		virtual void setColor(float t) = 0;

		virtual void setColor(int r, int g, int b, int a);

		virtual void update(float dt) = 0;
	};

	typedef boost::shared_ptr<AbstractColor> pAbstractColor;
}

#endif
