/**
* @file SimpleEntity.h
* @author Anders Ruud
* @date 2006-03-13
* @brief Contains definition for class SimpleEntity.
**/

#ifndef AMF_SIMPLE_ENTITY_H
#define AMF_SIMPLE_ENTITY_H

#include "Entity.h"
#include "Polygon.h"
#include "Animation.h"

#include <vector>

using namespace std;

namespace love
{

	/**
	* @class SimpleEntity
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-13
	* @brief Entities which follow a certain simple pattern.
	*
	* The pattern is: <br />
	*  - No moving parts. (No skeletal animation). <br />
	*  - Represented by an arbitrary number of FrameAnimations. <br />
	*  - Must spawn, live, and die. <br />
	*  - Controllable by the state of the keyboard.
	*  - More shit later
	*
	* @todo This class is NOT done.
	**/
	class SimpleEntity : public Entity
	{
	private:
		
	public:



		/**
		* @brief Creates a new SimpleEntity object.
		**/
		SimpleEntity();
		virtual ~SimpleEntity();

		/**
		* @brief Renders the entity once.
		**/
		virtual void render();

		/**
		* @brief Updates the entity.
		* @param dt The time since last frame (in seconds).
		**/
		virtual void update(float dt);

	};

	typedef boost::shared_ptr<SimpleEntity> pSimpleEntity;

}// love

#endif