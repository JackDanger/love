#include <love/Reference.h>

namespace love
{
	Reference::Reference()
		: L(0), idx(LUA_REFNIL)
	{
	}

	Reference::Reference(lua_State * L)
	{
		ref(L);
	}

	Reference::~Reference()
	{
		unref();
	}

	void Reference::ref(lua_State * L)
	{
		unref(); // Just to be safe.
		this->L = L;
		idx = luaL_ref(L, LUA_GLOBALSINDEX);
	}

	void Reference::unref()
	{
		if(idx != LUA_REFNIL)
		{
			luaL_unref(L, LUA_GLOBALSINDEX, idx);
			idx = LUA_REFNIL;
		}
	}

	void Reference::push()
	{
		if(idx != LUA_REFNIL)
			lua_rawgeti(L, LUA_GLOBALSINDEX, idx);
		else
			lua_pushnil(L);
	}

	lua_State * Reference::getL()
	{
		return L;
	}

} // love
