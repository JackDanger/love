/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-08
*/
#ifndef LOVE_PHYSICS_BOX2D_WORLD_H
#define LOVE_PHYSICS_BOX2D_WORLD_H

// LOVE
#include "../../Object.h"
#include "../../luax.h"
#include "../../Reference.h"

// STD
#include <vector>

// Box2D
#include "Include/Box2D.h"

namespace love
{
namespace physics
{
namespace box2d
{
	
	class Contact;

	/**
	* The World is the "God" container class, 
	* which contains all Bodies and Joints. Shapes
	* are contained in their associated Body. 
	* 
	* Bodies in different worlds can obviously not
	* collide.
	* 
	* The world also controls global parameters, like 
	* gravity.
	**/
	class World : public Object, public b2ContactListener
	{
		// Friends.
		friend class Joint;
		friend class DistanceJoint;
		friend class MouseJoint;
		friend class Body;

	private:

		// Pointer to the Box2D world.
		b2World * world;

		// Contact callbacks.
		Reference * add_ref;

		// Contacts buffers.
		std::vector<Contact *> add_contacts;

	public:

		/**
		* Creates a new world with the given bounding box.
		* @param aabb The bounding box.
		**/
		World(b2AABB aabb);

		/**
		* Creates a new world with the given bounding box, gravity
		* and whether or not the bodies should sleep when appropriate.
		* @param aabb The bounding box.
		* @param gravity The gravity of the World.
		* @param sleep True if the bodies should be able to sleep,
		* false otherwise.
		**/
		World(b2AABB aabb, b2Vec2 gravity, bool sleep);

		~World();

		/**
		* Updates everything in the world one timestep.
		* This is called update() and not step() to conform
		* with all other objects in LOVE.
		* @param dt The timestep.
		**/
		void update(float dt);

		// From b2ContactListener
		void Add(const b2ContactPoint* point);

		/**
		* Recieves a Lua function as argument, and
		* stores it for use when a collision occurs.
		**/
		int setCallback(lua_State * L);

		/**
		* Returns the stored Lua function for collision
		* handling, or nil if there is none.
		**/
		int getCallback(lua_State * L);
		
		/**
		* Sets the current gravity of the World.
		* @param x Gravity in the x-direction.
		* @param y Gravity in the y-direction.
		**/
		void setGravity(float x, float y);

		/**
		* Gets the current gravity.
		* @returns Gravity in the x-direction.
		* @returns Gravity in the y-direction.
		**/
		int getGravity(lua_State * L);

		/**
		* Sets whether this World allows sleep.
		* @param allow True to allow, false to disallow.
		**/
		void setAllowSleep(bool allow);

		/**
		* Returns whether this World allows sleep.
		* @return True if allowed, false if disallowed.
		**/
		bool isAllowSleep() const;

		/**
		* Get the current body count.
		* @return The number of bodies.
		**/
		int getBodyCount();

		/**
		* Get the current joint count.
		* @return The number of joints.
		**/
		int getJointCount();

	};

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_WORLD_H
