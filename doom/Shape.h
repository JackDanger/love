/**
* @file Shape.h
* @brief Contains definition of class Shape.
* @date 2006-02-07
* @author Kjell Ivar Storstein
**/

#ifndef AMF_SHAPE_H
#define AMF_SHAPE_H

#include "Entity.h"

#include <cmath>
#define M_PI 3.14159265


namespace love 
{


	/**
	* @class Shape
	* @version 1.0
	* @since 1.0
	* @author Kjell Ivar Storstein
	* @date 2006-02-07
	*
	* @brief Superclass of all shapes.
	**/
	class Shape : public Entity
	{
	protected:
	public:	
	};

	typedef boost::shared_ptr<Shape> pShape;
	
}//love

#endif
