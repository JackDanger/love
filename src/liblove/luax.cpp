#include <love/luax.h>

namespace love
{
	int luax_assert_argc(lua_State * L, int lower)
	{
		int argc = lua_gettop(L);
		if( argc < lower )
			return luaL_error(L, "Incorrect number of arguments. Got [%d], expected at least [%d]", argc, lower);
		return 0;
	}

	int luax_assert_argc(lua_State * L, int lower, int upper)
	{
		int argc = lua_gettop(L);
		if( argc < lower || argc > upper)
			return luaL_error(L, "Incorrect number of arguments. Got [%d], expected [%d-%d]", argc, lower, upper);
		return 0;
	}

	int luax_assert_function(lua_State * L, int n)
	{
		if(!lua_isfunction(L, n))
			return luaL_error(L, "Argument must be of type \"function\".");
		return 0;
	}

} // love
