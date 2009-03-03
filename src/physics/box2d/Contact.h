/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
**/

#ifndef LOVE_PHYSICS_BOX2D_CONTACT_H
#define LOVE_PHYSICS_BOX2D_CONTACT_H

// LOVE
#include "../../Object.h"
#include "../../luax.h"

// Box2D
#include "Include/Box2D.h"

namespace love
{
namespace physics
{
namespace box2d
{
	/**
	* A Contact represents a collision point between
	* two shapes.
	**/
	class Contact : public Object
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

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_CONTACT_H