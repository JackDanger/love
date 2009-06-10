/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

#include "Native.h"


#include <cstring>

namespace love
{
namespace native
{
namespace tcc
{

	struct tcc_function 
	{
		const char * name; 
		void * fn;
	};

	static tcc_function tcc_api[] =
	{

		// C
		{ "strcmp", strcmp },
		{ "strlen", strlen },

		// Lua
		{ "lua_isnumber", lua_isnumber },
		{ "lua_isstring", lua_isstring },
		{ "lua_iscfunction", lua_iscfunction },
		{ "lua_isuserdata", lua_isuserdata },
		{ "lua_type", lua_type },
		{ "lua_typename", lua_typename },

		{ "lua_equal", lua_equal },
		{ "lua_rawequal", lua_rawequal },
		{ "lua_lessthan", lua_lessthan },

		{ "lua_tonumber", lua_tonumber },
		{ "lua_tointeger", lua_tointeger },
		{ "lua_toboolean", lua_toboolean },
		{ "lua_tolstring", lua_tolstring },
		{ "lua_objlen", lua_objlen },
		{ "lua_tocfunction", lua_tocfunction },
		{ "lua_touserdata", lua_touserdata },
		{ "lua_tothread", lua_tothread },
		{ "lua_topointer", lua_topointer },

		{ "lua_pushnil", lua_pushnil },
		{ "lua_pushnumber", lua_pushnumber },
		{ "lua_pushinteger", lua_pushinteger },
		{ "lua_pushlstring", lua_pushlstring },
		{ "lua_pushstring", lua_pushstring },
		{ "lua_pushvfstring", lua_pushvfstring },

		{ "lua_pushfstring", lua_pushfstring },
		{ "lua_pushcclosure", lua_pushcclosure },
		{ "lua_pushboolean", lua_pushboolean },
		{ "lua_pushlightuserdata", lua_pushlightuserdata },
		{ "lua_pushthread", lua_pushthread },

		// End
		{ 0, 0 }
	};


	Native::Native()
		: state(0)
	{
		state = tcc_new();

		if(!state) 
		{
			throw love::Exception("Could not create TCC state.");
		}

		tcc_set_output_type(state, TCC_OUTPUT_MEMORY);

		// Add APIs here.
		for(tcc_function * f = tcc_api; (*f).name != 0; f++)
		{
			tcc_add_symbol(state, (*f).name, (*f).fn);
		}

	}

	Native::~Native()
	{
		if(state != 0)
		{
			tcc_delete(state);
		}

		for(int i = 0; i<(int)buffers.size(); i++)
		{
			if(buffers[i] != 0)
			{
				free(buffers[i]);
			}
		}
	}

	const char * Native::getName() const
	{
		return "love.native.tcc";
	}

	bool Native::compile(const char * str)
	{
		if(state == 0)
			return false;

		if (tcc_compile_string(state, str) == -1)
			return false;

		return true;
	}

	bool Native::relocate()
	{
		if(state == 0)
			return false;

		int size = tcc_relocate(state, 0);

		if(size == -1)
			return false;

		void * mem = malloc(size);

		if(mem == 0)
			return false;

		if(tcc_relocate(state, mem) == -1)
		{
			free(mem);
			return false;
		}

		buffers.push_back(mem);

		return true;
	}

	void * Native::getSymbol(const char * sym)
	{
		if(state == 0)
			return 0;

		return tcc_get_symbol(state, sym);
	}

} // tcc
} // native
} // love
