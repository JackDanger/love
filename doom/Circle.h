/**
* @file Circle.h
* @author Anders Ruud
* @date 2007-01-20
* @brief Contains definition for class Circle.
**/

#ifndef LOVE_CIRCLE_H
#define LOVE_CIRCLE_H

// LOVE
#include "Polygon.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class Circle
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-01-20
	* @brief 
	**/
	class Circle : public Polygon
	{
	private:

		// radius
		float radius;

	public:

		/**
		* @brief Contructs an Circle.
		**/
		Circle(float radius);

		virtual ~Circle();

		/**
		* @brief Gets radius.
		* @return radius.
		**/
		float getRadius() const;

	};

	typedef boost::shared_ptr<Circle> pCircle;

} // love

#endif
