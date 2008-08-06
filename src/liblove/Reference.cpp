#include <love/Reference.h>

namespace love
{
	const char * Reference::TABLE = "refs";

	Reference::Reference(lua_State * L, int idx)
	{
		this->L = L;

		// Push reftable.
		lua_getglobal(L, "love");
		lua_getfield(L, -1, Reference::TABLE);
		lua_insert(L, -2); // move reftable
		lua_insert(L, -2); // move love

		// Stack should now be [ ..., love, reftable, value ]

		ref = luaL_ref(L, -1);

		// Pop love and reftable tables.
		lua_pop(L, 2);
	}

	Reference::~Reference()
	{
		lua_getglobal(L, "love");
		lua_getfield(L, -1, Reference::TABLE);
		luaL_unref(L, -1, ref);
		ref = LUA_REFNIL;
	}

	void Reference::push()
	{
		if(ref != LUA_REFNIL)
		{
			lua_getglobal(L, "love");
			lua_getfield(L, -1, Reference::TABLE);
			lua_rawgeti(L, -1, ref);
		}
		else
		{
			lua_pushnil(L);
		}
	}

} // love