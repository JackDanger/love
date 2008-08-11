#include <love/Reference.h>

namespace love
{
	const char * Reference::TABLE = "refs";

	Reference::Reference(lua_State * L)
	{
		this->L = L;

		// Push reftable.
		lua_getglobal(L, "love");
		lua_getfield(L, -1, Reference::TABLE);
		lua_pushvalue(L, -3); // Copy value

		ref = luaL_ref(L, -2);

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
		lua_insert(L, -3);
		lua_pop(L, 2);
	}

	lua_State * Reference::getL()
	{
		return L;
	}

} // love