#include <love/luax.h>

namespace love
{
	int luax_assert_argc(lua_State * L, int lower)
	{
		int argc = lua_gettop(L);
		if( argc < lower )
			return luaL_error(L, "Incorrect number of arguments. Got [%i], expected [%i]", argc, lower);
		return 0;
	}

	int luax_assert_argc(lua_State * L, int lower, int upper)
	{
		int argc = lua_gettop(L);
		if( argc < lower || argc > upper)
			return luaL_error(L, "Incorrect number of arguments. Got [%i], expected [%i-%i]", argc, lower, upper);
		return 0;
	}

} // love
