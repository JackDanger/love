#include "World.h"
#include "mod_box2d.h"

namespace love_box2d
{
	World::World(b2AABB aabb, b2Vec2 gravity, bool sleep)
	{
		world = new b2World(aabb, gravity, sleep);
		world->SetContactListener(this);
		add_contacts.reserve(10);
	}

	World::~World()
	{
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
				// Call the function.
				add_ref->push();
				mod_push_contact(L, add_contacts[i]);
				lua_call(L, 1, 0);
			}

			// Clear contacts.
			add_contacts.clear();
		}


	}

	void World::Add(const b2ContactPoint* point)
	{
		if(add_ref != 0)
		{
			pContact p(new Contact(point));
			add_contacts.push_back(p);
		}
	}

	int World::setCallback(lua_State * L)
	{
		love::luax_assert_argc(L, 1, 1);
		love::luax_assert_function(L, -1);
		add_ref.reset<love::Reference>(new love::Reference(L));
		return 0;
	}

	int World::getCallback(lua_State * L)
	{
		love::luax_assert_argc(L, 0, 0);
		
		if(add_ref != 0)
			add_ref->push();
		else
			lua_pushnil(L);

		return 1;
	}

} // love_box2d