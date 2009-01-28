/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
*
* @author Anders Ruud
* @date 2008-08-06
**/

#include "luax.h"

// STD
#include <iostream>

namespace love
{
	void luax_printstack(lua_State * L)
	{
		for(int i = 1;i<=lua_gettop(L);i++)
		{
			std::cout << i << " - " << luaL_typename(L, i) << std::endl;
		}
	}

	bool luax_toboolean(lua_State * L, int idx)
	{
		return (lua_toboolean(L, idx) == 1 ? true : false);
	}

	void luax_pushboolean(lua_State * L, bool b)
	{
		lua_pushboolean(L, b ? 1 : 0);
	}

	bool luax_optboolean(lua_State * L, int idx, bool b)
	{
		if(lua_isboolean(L, idx) == 1)
			return (lua_toboolean(L, idx) == 1 ? true : false);
		return b;
	}

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

	int luax_register_gc(lua_State * L, const char * mname, lua_CFunction f)
	{

		lua_getglobal(L, "love");
		lua_getfield(L, -1, "__fin");

		lua_newuserdata(L, 0); 

		luaL_newmetatable(L, mname);
		lua_pushcfunction(L, f);
		lua_setfield(L, -2, "__gc");
		lua_setmetatable(L, -2);

		lua_setfield(L, -2, mname);

		lua_settop(L, 0);
		return 0;
	}

	int luax_register_info(lua_State * L, const char * name, 
		const char * provides, const char * desc, const char * author,
		lua_CFunction open)
	{
		lua_getglobal(L, "love");
		lua_getfield(L, -1, "__mod");
		lua_getfield(L, -1, provides);

		// Make sure it exists.
		if(lua_isnil(L, -1))
		{
			lua_pop(L, 1);
			lua_newtable(L);
			lua_setfield(L, -2, provides);
			lua_getfield(L, -1, provides);
		}

		lua_newtable(L);

		lua_pushstring(L, desc);
		lua_setfield(L, -2, "description");
		lua_pushstring(L, author);
		lua_setfield(L, -2, "author");
		lua_pushcfunction(L, open);
		lua_setfield(L, -2, "open");

		lua_setfield(L, -2, name);

		// Pop "provides", __mod, love
		lua_pop(L, 3);
		return 0;
	}

	int luax_register_module(lua_State * L, const char * mname, const luaL_Reg * fn)
	{
		lua_getglobal(L, "love");

		lua_newtable(L); // Table for the new module.
		luaL_register(L, 0, fn);
		lua_setfield(L, -2, mname);
	
		lua_settop(L, 0);	
		return 0;
	}

	int luax_register_type(lua_State * L, const char * tname, const luaL_Reg * fn)
	{
		luaL_newmetatable(L, tname);
		luaL_register(L, 0, fn);
		lua_pop(L, 1); // Pops metatable.
		return 0;
	}

	void luax_newtype(lua_State * L, const char * tname, bits flags, void * data, bool own)
	{
		userdata * u = (userdata *)lua_newuserdata(L, sizeof(userdata));

		u->data = data;
		u->flags = flags;
		u->own = own;

		luaL_newmetatable(L, tname);
		lua_setmetatable(L, -2);
	}

	bool luax_istype(lua_State * L, int idx, love::bits type)
	{
		if(lua_isuserdata(L, idx) == 0)
			return false;

		userdata * u = (userdata *)lua_touserdata(L, idx);

		return ((u->flags & type) == type);
	}

	int luax_getfunction(lua_State * L, const char * mod, const char * fn)
	{
		lua_getglobal(L, "love");
		if(lua_isnil(L, -1)) return luaL_error(L, "Could not find global love!");
		lua_getfield(L, -1, "filesystem");
		if(lua_isnil(L, -1)) return luaL_error(L, "Could not find love.%s!", mod);
		lua_getfield(L, -1, "newFile");
		if(lua_isnil(L, -1)) return luaL_error(L, "Could not find love.%s.%s!", mod, fn);
		
		lua_remove(L, -2); // remove filesystem
		lua_remove(L, -2); // remove love
		return 0;
	}

	int luax_convobj(lua_State * L, int idx, const char * mod, const char * fn)
	{
		// Convert string to a file.
		luax_getfunction(L, mod, fn);
		lua_pushvalue(L, idx); // The initial argument.
		lua_call(L, 1, 1); // Call the function, one arg, one return value.
		lua_replace(L, idx); // Replace the initial argument with the new object.
		return 0;
	}

	int luax_strtofile(lua_State * L, int idx)
	{
		return luax_convobj(L, idx, "filesystem", "newFile");
	}

} // love
