/**
* @file Entity.h
* @author Anders Ruud
* @date 2006-03-13
* @brief Contains definition for class Entity.
**/

#ifndef LOVE_ENTITY_H
#define LOVE_ENTITY_H

#include "AbstractEntity.h"
#include "Vextor.h"

// Boost
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;

namespace love
{

	/**
	* @class Entity
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2006-03-13
	* @brief Entities are things that appear in the game directly.
	*
	* This class is abstract and can not be used directly.
	**/
	class Entity : public AbstractEntity
	{
	private:

	protected:

		// Position
		Vextor position;

		// Next displacement
		Vextor displacement;

	public:



		Entity();
		virtual ~Entity();

		/**
		* @brief Returns the x position.
		* @return The x position.
		**/
		float getX();

		/**
		* @brief Sets the x position.
		* @param The new x position.
		**/
		void setX(float x);

		/**
		* @brief Returns the y position.
		* @return The y position.
		**/
		float getY();

		/**
		* @brief Sets the y position.
		* @param The new y position.
		**/
		void setY(float y);

		/**
		* @brief Moves the viewport horizontally.
		* @param dx How far we want to move.
		**/
		void xMove(float dx);

		/**
		* @brief Moves the viewport vertically.
		* @param dy How far we want to move.
		**/
		void yMove(float dy);

		/**
		* @brief Adds a Vextor to the displacement Vextor.
		* @param i The Vextor that will be added to the displacement Vextor.
		* @todo IMPLEMENT ME
		**/
		void addImpulse(const Vextor & i);

		/**
		* @brief Sets the displacement Vextor to (0,0).
		* @todo IMPLEMENT ME
		**/
		void clearImpulse();

		/**
		* @brief Move the Entity with the current displacement.
		*
		* It also resets the current displacement to (0,0).
		* @todo IMPLEMENT ME
		**/
		void move();

		/**
		* @brief Immediately moves the Entity by the given Vextor.
		* @param dv The Vextor containing the displacement.
		**/
		void move(const Vextor & dv);

		/**
		* @brief Returns a reference to the current position.
		* @return The Vextor containing the current position.
		**/
		const Vextor & getPosition() const;

		/**
		* @brief Immediately changes the position.
		* @param v The Vextor containing the new positon.
		**/
		void setPosition(const Vextor & v);

		/**
		* @brief Immediately changes the position.
		* @param x The new position on the x-axis.
		* @param y The new position on the x-axis.
		**/
		void setPosition(float x, float y);

		const Vextor & getDisplacement();

		void setDisplacement(Vextor displacement);

	};

	typedef boost::shared_ptr<Entity> pEntity;

}// love

#endif
