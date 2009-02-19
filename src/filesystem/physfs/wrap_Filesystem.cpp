/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
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
* 
* -- LOVE Development Team, http://love2d.org
**/

// LOVE
#include "../../luax.h"

#include "wrap_Filesystem.h"

namespace love
{
namespace filesystem
{
namespace physfs
{

	int _wrap_setIdentity(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);

		if(!Filesystem::__getinstance()->setIdentity(arg))
			return luaL_error(L, "Could not set write directory.");

		return 0;
	}

	int _wrap_setSource(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);

		if(!Filesystem::__getinstance()->setSource(arg))
			return luaL_error(L, "Could not set source.");

		return 0;
	}

	int _wrap_newFile(lua_State * L)
	{
		const char * filename = luaL_checkstring(L, 1);
		int mode = luaL_optint(L, 2, FILE_READ);

		File * t = Filesystem::__getinstance()->newFile(filename, mode);
		if(t == 0)
			return luaL_error(L, "Could not open file %s", filename);
		luax_newtype(L, "File", LOVE_FILESYSTEM_FILE_BITS, (void*)t);

		return 1;
	}

	int _wrap_getWorkingDirectory(lua_State * L)
	{
		lua_pushstring(L, Filesystem::__getinstance()->getWorkingDirectory());
		return 1;
	}

	int _wrap_getUserDirectory(lua_State * L)
	{
		lua_pushstring(L, Filesystem::__getinstance()->getUserDirectory());
		return 1;
	}

	int _wrap_getAppdataDirectory(lua_State * L)
	{
		lua_pushstring(L, Filesystem::__getinstance()->getAppdataDirectory());
		return 1;
	}

	int _wrap_getSaveDirectory(lua_State * L)
	{
		lua_pushstring(L, Filesystem::__getinstance()->getSaveDirectory());
		return 1;
	}

	int _wrap_exists(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, Filesystem::__getinstance()->exists(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_isDirectory(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, Filesystem::__getinstance()->isDirectory(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_isFile(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, Filesystem::__getinstance()->isFile(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_mkdir(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, Filesystem::__getinstance()->mkdir(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_remove(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, Filesystem::__getinstance()->remove(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_open(lua_State * L)
	{
		File * file = luax_checkfile(L, 1);
		lua_pushboolean(L, file->open() ? 1 : 0);
		return 1;
	}

	int _wrap_close(lua_State * L)
	{
		File * file = luax_checkfile(L, 1);
		lua_pushboolean(L, file->close() ? 1 : 0);
		return 1;
	}

	int _wrap_read(lua_State * L)
	{
		return Filesystem::__getinstance()->read(L);
	}

	int _wrap_write(lua_State * L)
	{
		return Filesystem::__getinstance()->write(L);
	}

	int _wrap_eof(lua_State * L)
	{
		File * file = luax_checkfile(L, 1);
		lua_pushboolean(L, file->eof() ? 1 : 0);
		return 1;
	}	

	int _wrap_tell(lua_State * L)
	{
		File * file = luax_checkfile(L, 1);
		lua_pushinteger(L, file->tell());
		return 1;
	}	

	int _wrap_seek(lua_State * L)
	{
		File * file = luax_checkfile(L, 1);
		int pos = luaL_checkinteger(L, 2);
		lua_pushboolean(L, file->seek(pos) ? 1 : 0);
		return 1;
	}	

	int _wrap_enumerate(lua_State * L)
	{
		return Filesystem::__getinstance()->enumerate(L);
	}

	int _wrap_lines(lua_State * L)
	{
		return Filesystem::__getinstance()->lines(L);
	}

	int _wrap_load(lua_State * L)
	{
		return Filesystem::__getinstance()->load(L);
	}

	// List of functions to wrap.
	static const luaL_Reg wrap_Filesystem_functions[] = {
		{ "setIdentity",  _wrap_setIdentity },
		{ "setSource",  _wrap_setSource },
		{ "newFile",  _wrap_newFile },
		{ "getWorkingDirectory",  _wrap_getWorkingDirectory },
		{ "getUserDirectory",  _wrap_getUserDirectory },
		{ "getAppdataDirectory",  _wrap_getAppdataDirectory },
		{ "getSaveDirectory",  _wrap_getSaveDirectory },
		{ "exists",  _wrap_exists },
		{ "isDirectory",  _wrap_isDirectory },
		{ "isFile",  _wrap_isFile },
		{ "mkdir",  _wrap_mkdir },
		{ "remove",  _wrap_remove },
		{ "open",  _wrap_open },
		{ "close",  _wrap_close },
		{ "read",  _wrap_read },
		{ "write",  _wrap_write },
		{ "eof",  _wrap_eof },
		{ "tell",  _wrap_tell },
		{ "seek",  _wrap_seek },
		{ "enumerate",  _wrap_enumerate },
		{ "lines",  _wrap_lines },
		{ "load",  _wrap_load },
		{ 0, 0 }
	};

	int wrap_Filesystem_open(lua_State * L)
	{
		luax_register_module(L, "filesystem", wrap_Filesystem_functions);
		wrap_File_open(L);
		return 0;
	}

} // physfs
} // filesystem
} // love

