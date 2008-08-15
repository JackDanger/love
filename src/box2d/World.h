/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-08
*/
#ifndef LOVE_BOX2D_WORLD_H
#define LOVE_BOX2D_WORLD_H

// LOVE
#include <love/mod.h>

// STD
#include <vector>

// Boost
#include <boost/shared_ptr.hpp>

// Box2D
#include <Box2D.h>

// Module
#include "Contact.h"

namespace love_box2d
{
	class World : public b2ContactListener
	{
		friend class Joint;
		friend class DistanceJoint;
		friend class MouseJoint;
		friend class Body;
	private:
		b2World * world;

		// Contact callbacks.
		love::pReference add_ref;

		// Contacts buffers.
		std::vector<pContact> add_contacts;
	public:
		World(b2AABB aabb);
		World(b2AABB aabb, b2Vec2 gravity, bool sleep);
		~World();
		void update(float dt);

		// From b2ContactListener
		void Add(const b2ContactPoint* point);

		int setCallback(lua_State * L);
		int getCallback(lua_State * L);

		void setGravity(float x, float y);
		int getGravity(lua_State * L);

		int getBodyCount();
		int getJointCount();

	};

	typedef boost::shared_ptr<World> pWorld;

} // love_box2d

#endif // LOVE_BOX2D_WORLD_H
