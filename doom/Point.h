#ifndef LOVE_POINT_H
#define LOVE_POINT_H

#include "Shape.h"
#include "Matrix.h"

// boost
#include <boost/shared_ptr.hpp>

namespace love 
{

	class Vector;

	/**
	* @class Point
	* @version 1.0
	* @since 1.0
	* @author Kjell Ivar Storstein
	* @date 2006-01-15
	* @brief
	**/
	class Point : public Shape 
	{
		public:
			Point();
			Point(float x, float y);
			virtual ~Point();

			virtual void render();
			float dot(Point & p);

			Vector to(Point& p);


			bool operator == (Point& p);
			bool operator < (Point& p);
			Point operator - (Point & p);
			void operator -= (Point & p);
			Point operator + (Point & p);

			void operator += (Vector& v);
			void operator -= (Vector& v);

			Point operator + (Vector& v);
			Point operator - (Vector& v);

			

			

	};

	// Typedefs
	typedef boost::shared_ptr<Point> pPoint;
	
}// namespace love

#endif
