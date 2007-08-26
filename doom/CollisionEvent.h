/**
* @file CollisionEvent.h
* @author Anders Ruud
* @date 2006-11-21
* @brief Contains definition for class CollisionEvent.
**/

#ifndef LOVE_COLLISIONEVENT_H
#define LOVE_COLLISIONEVENT_H

// LOVE
#include "Event.h"
#include "Entity.h"
#include "Vextor.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class CollisionEvent
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-11-21
	* @brief 
	**/
	class CollisionEvent : public Event
	{
	private:

		// firstEntity
		pEntity firstEntity;

		// secondEntity
		pEntity secondEntity;

		// collisionPoint
		Vextor collisionPoint;

	public:

		/**
		* @brief Contructs an empty CollisionEvent.
		**/
		CollisionEvent();
		virtual ~CollisionEvent();

		/**
		* @brief Gets firstEntity.
		* @return firstEntity.
		**/
		const pEntity & getFirstEntity() const;


		/**
		* @brief Sets firstEntity.
		* @param firstEntity 
		**/
		void setFirstEntity(pEntity firstEntity);


		/**
		* @brief Gets secondEntity.
		* @return secondEntity.
		**/
		const pEntity & getSecondEntity() const;


		/**
		* @brief Sets secondEntity.
		* @param secondEntity 
		**/
		void setSecondEntity(pEntity secondEntity);


		/**
		* @brief Gets collisionPoint.
		* @return collisionPoint.
		**/
		const Vextor & getCollisionPoint() const;


		/**
		* @brief Sets collisionPoint.
		* @param collisionPoint 
		**/
		void setCollisionPoint(Vextor collisionPoint);


	};

	typedef boost::shared_ptr<CollisionEvent> pCollisionEvent;

} // love

#endif
