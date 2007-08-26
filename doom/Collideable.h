/**
* @file Collidable.h
* @brief Contains definition of class Collidable.
* @date 2006-04-01
* @author Anders Ruud
**/

#ifndef AMF_COLLIDEABLE_H
#define AMF_COLLIDEABLE_H

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{



	/**
	* @class Collidable
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-04-01
	* @brief Superclass for all objects in the engine that can 
	* collide with eachother.
	**/
	class Collidable
	{
	private:
	public:
		//todo: const CompositeBody & getCompositeBody() = 0;

	};

	typedef boost::shared_ptr<Collidable> pCollidable;

}// love

#endif