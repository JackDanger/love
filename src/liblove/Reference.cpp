#include <love/Reference.h>

namespace love
{
	Reference::Reference(lua_State * L)
	{
		this->L = L;
		ref = luaL_ref(L, LUA_GLOBALSINDEX);
	}

	Reference::~Reference()
	{
		luaL_unref(L, LUA_GLOBALSINDEX, ref);
		ref = LUA_REFNIL;
	}

	void Reference::push()
	{
		if(ref != LUA_REFNIL)
			lua_rawgeti(L, LUA_GLOBALSINDEX, ref);
		else
			lua_pushnil(L);
	}

	lua_State * Reference::getL()
	{
		return L;
	}

} // love
