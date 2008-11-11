#include "World.h"

#include "Shape.h"
#include "Contact.h"

namespace love
{
namespace box2d
{

	World::World(b2AABB aabb)
		: add_ref(0)
	{
		world = new b2World(aabb, b2Vec2(0,0), true);
		world->SetContactListener(this);
		add_contacts.reserve(10);
	}

	World::World(b2AABB aabb, b2Vec2 gravity, bool sleep)
		: add_ref(0)
	{
		world = new b2World(aabb, gravity, sleep);
		world->SetContactListener(this);
		add_contacts.reserve(10);
	}

	World::~World()
	{
		if(add_ref != 0)
			delete add_ref;

		delete world;
	}

	void World::update(float dt)
	{
		world->Step(dt, 10);

		// Process contacts.
		if(add_ref != 0)
		{
			lua_State * L = add_ref->getL();
			for(int i = 0;i<(int)add_contacts.size();i++)
			{
				// Push the function.
				add_ref->push();
				
				// Push first userdata.
				{
					shapeudata * d = (shapeudata *)(add_contacts[i]->point.shape1->GetUserData());
					if(d->ref != 0) 
						d->ref->push(); 
					else 
						lua_pushnil(L);
				}

				// Push first userdata.
				{
					shapeudata * d = (shapeudata *)(add_contacts[i]->point.shape2->GetUserData());
					if(d->ref != 0) 
						d->ref->push(); 
					else 
						lua_pushnil(L);
				}

				luax_newtype(L, "Contact", (LOVE_CONTACT_BITS | LOVE_BOX2D_BITS), (void*)add_contacts[i], false);
				lua_call(L, 3, 0);
			}

			// Clear contacts.
			for(int i = 0;i<(int)add_contacts.size();i++)
				delete add_contacts[i];
			add_contacts.clear();
		}

	}

	void World::Add(const b2ContactPoint* point)
	{
		/**
		* We must copy contacts, since we're not allowed to process
		* them inside this function. Removing bodies in this function
		* pretty much guarantees segfault. ^^
		**/

		if(add_ref != 0)
			add_contacts.push_back(new Contact(point));
	}

	int World::setCallback(lua_State * L)
	{
		luax_assert_argc(L, 1, 1);
		luax_assert_function(L, -1);

		if(add_ref != 0)
		{
			delete add_ref;
			add_ref = 0;
		}

		add_ref = new Reference(L);
		return 0;
	}

	int World::getCallback(lua_State * L)
	{
		if(add_ref != 0)
			add_ref->push();
		else
			lua_pushnil(L);

		return 1;
	}

	void World::setGravity(float x, float y)
	{
		world->SetGravity(b2Vec2(x, y));
	}

	int World::getGravity(lua_State * L)
	{
		b2Vec2 v = world->m_gravity;
		lua_pushnumber(L, v.x);
		lua_pushnumber(L, v.y);
		return 2;
	}

	void World::setAllowSleep(bool allow)
	{
		world->m_allowSleep = allow;
	}

	bool World::isAllowSleep() const
	{
		return world->m_allowSleep;
	}

	int World::getBodyCount()
	{
		return world->GetBodyCount();
	}

	int World::getJointCount()
	{
		return world->GetJointCount();
	}

} // box2d
} // love
