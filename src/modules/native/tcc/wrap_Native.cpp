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

// LOVE
#include "wrap_Native.h"

#include "../../Filesystem/File.h"

namespace love
{
namespace native
{
namespace tcc
{
	static Native * instance = 0;

	int _wrap_compile(lua_State * L)
	{
		// Convert to File, if necessary.
		if(lua_isstring(L, 1))
			luax_strtofile(L, 1);

		filesystem::File * file = luax_checktype<filesystem::File>(L, 1, "File", LOVE_FILESYSTEM_FILE_BITS);

		Data * data = file->read();
		int size = data->getSize();

		char * str = new char[size+1];
		str[size] = 0;
		memcpy(str, data->getData(), size);
		data->release();

		bool r = instance->compile((const char *)str);
		
		delete [] str;

		luax_pushboolean(L, r);
		return 1;
	}

	int _wrap_relocate(lua_State * L)
	{
		luax_pushboolean(L, instance->relocate());
		return 1;
	}

	int _wrap_getSymbol(lua_State * L)
	{
		const char * sym = luaL_checkstring(L, 1);
		void * ptr = instance->getSymbol(sym);
		lua_CFunction fn = (lua_CFunction)ptr;

		if(fn == 0)
			lua_pushnil(L);
		else
			lua_pushcfunction(L, fn);

		return 1;
	}
	
	// List of functions to wrap.
	static const luaL_Reg wrap_Native_functions[] = {
		{ "compile", _wrap_compile },
		{ "relocate", _wrap_relocate },
		{ "getSymbol", _wrap_getSymbol },
		{ 0, 0 }
	};

	int wrap_Native_open(lua_State * L)
	{
		if(instance == 0)
		{
			try 
			{
				instance = new Native();
			} 
			catch(Exception & e)
			{
				return luaL_error(L, e.what());
			}
		}

		return luax_register_module(L, wrap_Native_functions, 0);
	}

} // tcc
} // native
} // love
