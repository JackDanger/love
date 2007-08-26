/**
* @file Rectangle.h
* @brief Contains definition of class Rectangle.
* @date 2006-03-09
* @author Anders Ruud
**/

#ifndef LOVE_RECTANGLE_H
#define LOVE_RECTANGLE_H

#include "Polygon.h"

namespace love
{

	/**
	* @class Rectangle
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-09
	* @brief Represents a rectangle.
	**/
	class Rectangle : public Polygon
	{
		private:

			// The width of the rectangle.
			float width;

			// The height of the rectangle.
			float height;

		public:

			/**
			* @brief Creates a new Rectangle object.
			**/
			Rectangle();

			/**
			* @brief Creates a new Rectangle object.
			**/
			Rectangle(float width, float height);

			/**
			* @brief Called when the object is destroyed.
			**/
			~Rectangle();

			/**
			* @brief Checks the rectangle's width.
			* @return The rectangle's width.
			**/
			float getWidth();
			
			/**
			* @brief Checks the rectangle's height.
			* @return The rectangle's height.
			**/
			float getHeight();

	};

	typedef boost::shared_ptr<Rectangle> pRectangle;

}// love


#endif
