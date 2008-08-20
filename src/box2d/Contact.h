/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-10
*/
#ifndef LOVE_BOX2D_CONTACT_H
#define LOVE_BOX2D_CONTACT_H

// LOVE
#include <love/mod.h>

// Boost
#include <boost/shared_ptr.hpp>

// Box2D
#include <Box2D.h>

namespace love_box2d
{
	/**
	* A Contact represents a collision point between
	* two shapes.
	**/
	class Contact
	{
		// Friends.
		friend class World;

	private:

		// The Box2D contact point.
		b2ContactPoint point;

	public:

		/**
		* Creates a new Contact by copying a Box2D contact
		* point. It does not store the pointer, but copy the
		* data pointed to.
		* @param point Pointer to the Box2D contact.
		**/
		Contact(const b2ContactPoint * point);

		~Contact();

		/**
		* Gets the position of the Contact.
		* @return The position along the x-axis.
		* @return The position along the y-axis.
		**/
		int getPosition(lua_State * L);

		/**
		* Gets the linear impact velocity.
		* @return The velocity along the x-axis.
		* @return The velocity along the y-axis.
		**/
		int getVelocity(lua_State * L);

		/**
		* Gets the collision normal.
		* @return The x-component of the normal.
		* @return The y-component of the normal.
		**/
		int getNormal(lua_State * L);

		/**
		* How far apart the shapes are. If they are intersecting
		* this value is negative.
		**/
		float getSeparation() const;

		/**
		* The mixed friction between the two shapes at
		* the point of impact.
		**/
		float getFriction() const;

		/**
		* The mixed restitution of the two shapes
		* at the point of impact.
		**/
		float getRestitution() const;

	};

	typedef boost::shared_ptr<Contact> pContact;

} // love_box2d

#endif // LOVE_BOX2D_CONTACT_H
