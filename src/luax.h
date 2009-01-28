/**
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* Lua auxiliary library. 
*
* @author Anders Ruud
* @date 2008-08-06
**/

#ifndef LOVE_LUAX_H
#define LOVE_LUAX_H

#include "types.h"

// Lua
extern "C" {
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
}

namespace love
{
	void luax_printstack(lua_State * L);
	bool luax_toboolean(lua_State * L, int idx);
	void luax_pushboolean(lua_State * L, bool b);
	bool luax_optboolean(lua_State * L, int idx, bool b);
	int luax_assert_argc(lua_State * L, int lower);
	int luax_assert_argc(lua_State * L, int lower, int upper);
	int luax_assert_function(lua_State * L, int n);
	int luax_register_gc(lua_State * L, const char * mname, lua_CFunction f);
	int luax_register_info(lua_State * L, const char * name, 
		const char * provides, const char * desc, const char * author,
		lua_CFunction open);

	int luax_register_module(lua_State * L, const char * mname, const luaL_Reg * fn);
	int luax_register_type(lua_State * L, const char * tname, const luaL_Reg * fn);

	void luax_newtype(lua_State * L, const char * tname, bits flags, void * data, bool own = true);

	bool luax_istype(lua_State * L, int idx, love::bits type);
	
	// Gets a function love.mod.fn.
	int luax_getfunction(lua_State * L, const char * mod, const char * fn);

	/**
	* Converts an object into another object
	* by the specified function mod.fn. The function must accept
	* a single file as a parameter, and return one value.
	* 
	* Note that the initial object is converted, i.e. replaced.
	**/
	int luax_convobj(lua_State * L, int idx, const char * mod, const char * fn);

	/**
	* Converts a string into a File object. Note that the 
	* string is replaced by the new File object at the
	* specified index, and NOT pushed onto the stack.
	**/
	int luax_strtofile(lua_State * L, int idx);

	template <typename T>
	T * luax_checktype(lua_State * L, int idx, const char * tname, love::bits type)
	{
		if(lua_isuserdata(L, idx) == 0)
			luaL_error(L, "Incorrect parameter type: expected userdata.");

		userdata * u = (userdata *)lua_touserdata(L, idx);

		if((u->flags & type) != type)
			luaL_error(L, "Incorrect parameter type: expected %s", tname);

		return (T *)u->data;	
	}

} // love

#endif // LOVE_LUAX_H
