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
		bool operator==(const AbstractColor & other) const;
		bool operator!=(const AbstractColor & other) const;

		/**
		 * @return The amount of red.
		 * @brief Returns the amount of red is in the color.
		 **/
		virtual int getRed() const;

		/**
		 * @return The amount of green.
		 * @brief Returns the amount of green is in the color.
		 **/
		virtual int getGreen() const;

		/**
		 * @return The amount of blue.
		 * @brief Returns the amount of blue is in the color.
		 **/
		virtual int getBlue() const;

		/**
		 * @return The amount of alpha.
		 * @brief Returns the amount of alpha.
		 **/
		virtual int getAlpha() const;

		/**
		 * @return The color code.
		 * @brief Formats the color values into a color code (syntax: 0xRRGGBB).
		 **/
		virtual int getCode() const;

		/**
		 * @param red The amount of red.
		 * @brief Sets the amount of red.
		 **/
		virtual void setRed(int red);

		/**
		 * @param green The amount of green.
		 * @brief Sets the amount of green.
		 **/
		virtual void setGreen(int green);

		/**
		 * @param blue The amount of blue.
		 * @brief Sets the amount of blue.
		 **/
		virtual void setBlue(int blue);

		/**
		 * @param alpha The amount of alpha.
		 * @brief Sets the amount of alpha.
		 **/
		virtual void setAlpha(int alpha);

		/**
		 * @param code The color code (in the syntax: 0xRRGGBB).
		 * @brief Sets the variables with the values derived from the color code.
		 **/
		virtual void setColor(int code);

		/**
		 * @param red The amount of red.
		 * @param green The amount of green.
		 * @param blue The amount of blue.
		 * @brief Sets the variables to the approriate new values.
		 **/
		virtual void setColor(int r, int g, int b);

		/**
		 * @param red The amount of red.
		 * @param green The amount of green.
		 * @param blue The amount of blue.
		 * @param alpha The amount of alpha.
		 * @brief Sets the variables to the approriate new values.
		 **/
		virtual void setColor(int r, int g, int b, int a);

		/**
		 * @brief Sets the color using function value t.
		 * @param t A value of 0 to 1 representing the start and the end of the dynamic color.
		 **/
		virtual void setColor(float t) = 0;

		/**
		 * @return An AbstractColor.
		 * @brief Returns a pointer to the current object.
		 **/
		virtual boost::shared_ptr<AbstractColor> getColor();

		/**
		 * @param time Used in the AnimatedColor.
		 * @return An AbstractColor.
		 * @brief Returns a pointer to the current object.
		 **/
		virtual boost::shared_ptr<AbstractColor> getColor(float time);

		/**
		 * @param other The other color.
		 * @param amount The amount of gradient (a value between 0 and 1).
		 * @return An AbstractColor.
		 * @brief Gets a gradient between this color and the other color determined by the amount.
		 **/
		virtual boost::shared_ptr<AbstractColor> getGradient(const boost::shared_ptr<AbstractColor> * other, float amount);

		/**
		 * @param color A pointer to a Color object.
		 * @param time The amount of time associated with the color.
	 	 * @brief Does nothing.
	 	 **/
		virtual void addColor(const boost::shared_ptr<AbstractColor> * color, float time);

		/**
		* @brief Does nothing.
		* @param r The red color component.
		* @param g The green color component.
		* @param b The blue color component.
		* @param a The alpha component.
		* @param time The amount of time associated with the color.
		**/
		virtual void addColor(int r, int g, int b, int a, float time);

		/**
		 * @param dt The elapsed time (in milliseconds).
	 	 * @brief Updates the color.
	 	 **/
		virtual void update(float dt) = 0;

		/**
		 * @param mode The desired mode.
	 	 * @brief Does nothing.
	 	 **/
		virtual void setMode(int mode);

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void play();

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void stop();

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void reset();

		void testColor(boost::shared_ptr<AbstractColor> color) const;
	};

	typedef boost::shared_ptr<AbstractColor> pAbstractColor;
}

#endif
