/**
* @file rect.h
* @brief Contains definition of struct rect.
* @date 2006-02-07
* @author Anders Ruud
**/

#ifndef AMF_RECT_H
#define AMF_RECT_H

// Boost
#include <boost/shared_ptr.hpp>

namespace love 
{

	/**
	* @struct rect
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-02-07
	* @brief Represents a rectangle.
	**/
	struct rect
	{
		float x;
		float y;
		float width;
		float height;
	};

	typedef boost::shared_ptr<rect> prect;
	
}//love

#endif