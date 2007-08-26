#ifndef LOVE_ENTITY2_H
#define LOVE_ENTITY2_H

#include "AbstractEntity.h"
#include "Loadable.h"
#include "Vextor.h"
#include <boost/shared_ptr.hpp>

namespace love
{
	/**
	* @class Entity
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-05-21
	* @brief An abstract class for entities within the game.
	**/
	class Entity : public AbstractEntity, public Loadable
	{
	protected:
		Vextor position;
		Vextor velocity;
		Vextor acceleration;

		float orientation;
		float z;

	public:
		Entity();
		virtual ~Entity();

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void init();

		/**
		 * @return The X position.
		 * @brief Returns the X position.
		 **/
		float getX();

		/**
		 * @return The Y position.
		 * @brief Returns the Y position.
		 **/
		float getY();

		/**
		 * @return The Z position.
		 * @brief Returns the Z position.
		 **/
		float getZ();

		/**
		 * @param x The new X postion.
		 * @brief Sets the X position.
		 **/
		void setX(float x);

		/**
		 * @param y The new Y postion.
		 * @brief Sets the Y position.
		 **/
		void setY(float y);

		/**
		 * @param z The new Z postion.
		 * @brief Sets the Z position.
		 **/
		void setZ(float z);

		/**
		 * @return The position.
		 * @brief Gets the position.
		 **/
		Vextor* getPosition();

		/**
		 * @return The X position.
		 * @brief Returns the X position.
		 **/
		float getXPosition();

		/**
		 * @return The Y position.
		 * @brief Returns the Y position.
		 **/
		float getYPosition();

		/**
		 * @return The Z position.
		 * @brief Returns the Z position.
		 **/
		float getZPosition();

		/**
		 * @param newPosition The new position.
		 * @brief Sets the position.
		 **/
		void setPosition(Vextor * newPosition);

		/**
		 * @param x The new X postion.
		 * @param y The new Y position.
		 * @brief Sets the position.
		 **/
		void setPosition(float x, float y);

		/**
		 * @param x The new X postion.
		 * @brief Sets the X position.
		 **/
		void setXPosition(float x);

		/**
		 * @param y The new Y postion.
		 * @brief Sets the Y position.
		 **/
		void setYPosition(float y);

		/**
		 * @param z The new Z postion.
		 * @brief Sets the Z position.
		 **/
		void setZPosition(float z);

		/**
		 * @return The velocity.
		 * @brief Gets the velocity.
		 **/
		Vextor* getVelocity();

		/**
		 * @return The X velocity.
		 * @brief Returns the X velocity.
		 **/
		float getXVelocity();

		/**
		 * @return The Y velocity.
		 * @brief Returns the Y velocity.
		 **/
		float getYVelocity();

		/**
		 * @param newVelocity The new velocity.
		 * @brief Sets the velocity.
		 **/
		void setVelocity(Vextor * newVelocity);

		/**
		 * @param x The new X velocity.
		 * @param y The new Y velocity.
		 * @brief Sets the velocity.
		 **/
		void setVelocity(float x, float y);

		/**
		 * @param x The new X velocity.
		 * @brief Sets the X velocity.
		 **/
		void setXVelocity(float x);

		/**
		 * @param y The new Y velocity.
		 * @brief Sets the Y velocity.
		 **/
		void setYVelocity(float y);

		/**
		 * @return The acceleration.
		 * @brief Gets the acceleration.
		 **/
		Vextor* getAcceleration();

		/**
		 * @return The X acceleration.
		 * @brief Returns the X acceleration.
		 **/
		float getXAcceleration();

		/**
		 * @return The Y acceleration.
		 * @brief Returns the Y acceleration.
		 **/
		float getYAcceleration();

		/**
		 * @param newAcceleration The new acceleration.
		 * @brief Sets the acceleration.
		 **/
		void setAcceleration(Vextor * newAcceleration);

		/**
		 * @param x The new X acceleration.
		 * @param y The new Y acceleration.
		 * @brief Sets the acceleration.
		 **/
		void setAcceleration(float x, float y);

		/**
		 * @param x The new X acceleration.
		 * @brief Sets the X acceleration.
		 **/
		void setXAcceleration(float x);

		/**
		 * @param y The new Y acceleration.
		 * @brief Sets the Y acceleration.
		 **/
		void setYAcceleration(float y);

		/**
		 * @return The orientation of the actor.
		 * @brief Gets the orientation.
		 **/
		float getOrientation();

		/**
		 * @param orientation The new orientation.
		 * @brief Sets the orientation.
		 **/
		void setOrientation(float orientation);

		/**
		 * @param dt Time elapsed in milliseconds.
		 * @brief Increments velocity with acceleration and position with velocity.
		 **/
		virtual void update(float dt);

		/**
	 	 * @brief Initializes all the variables as 0.
	 	 **/
		virtual int load();

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void unload();
	};

	typedef boost::shared_ptr<Entity> pEntity;
}

#endif
