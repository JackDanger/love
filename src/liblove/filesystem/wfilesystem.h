/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-30
*/

#ifndef LOVE_FILESYSTEM_W
#define LOVE_FILESYSTEM_W

// LOVE
#include "../luax.h"

#ifndef LOVE_WRAP_NAMESPACE
#error LOVE_WRAP_NAMESPACE must be defined.
#endif

#ifndef LOVE_WRAP_BITS
#error LOVE_WRAP_BITS must be defined.
#endif

#include "wFile.h"

namespace love
{
namespace LOVE_WRAP_NAMESPACE
{

	int _wrap_setIdentity(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);

		if(!setIdentity(arg))
			return luaL_error(L, "Could not set write directory.");

		return 0;
	}

	int _wrap_setSource(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);

		if(!setSource(arg))
			return luaL_error(L, "Could not set source.");

		return 0;
	}

	int _wrap_newFile(lua_State * L)
	{
		const char * filename = luaL_checkstring(L, 1);
		int mode = luaL_optint(L, 2, FILE_READ);

		File * t = newFile(filename, mode);
		if(t == 0)
			return luaL_error(L, "Could not open file %s", filename);
		luax_newtype(L, "File", LOVE_WRAP_FILE_BITS, (void*)t);

		return 1;
	}

	int _wrap_getWorkingDirectory(lua_State * L)
	{
		lua_pushstring(L, getWorkingDirectory());
		return 1;
	}

	int _wrap_getUserDirectory(lua_State * L)
	{
		lua_pushstring(L, getUserDirectory());
		return 1;
	}

	int _wrap_getAppdataDirectory(lua_State * L)
	{
		lua_pushstring(L, getAppdataDirectory());
		return 1;
	}

	int _wrap_getSaveDirectory(lua_State * L)
	{
		lua_pushstring(L, getSaveDirectory());
		return 1;
	}

	int _wrap_exists(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, exists(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_isDirectory(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, isDirectory(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_isFile(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, isFile(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_mkdir(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, mkdir(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_remove(lua_State * L)
	{
		const char * arg = luaL_checkstring(L, 1);
		lua_pushboolean(L, remove(arg) ? 1 : 0);
		return 1;
	}

	int _wrap_open(lua_State * L)
	{
		File * file = luax_checktype<File>(L, 1, "File", LOVE_WRAP_FILE_BITS);
		lua_pushboolean(L, file->open() ? 1 : 0);
		return 1;
	}

	int _wrap_close(lua_State * L)
	{
		File * file = luax_checktype<File>(L, 1, "File", LOVE_WRAP_FILE_BITS);
		lua_pushboolean(L, file->close() ? 1 : 0);
		return 1;
	}

	// int read(lua_State * L);
	// int write(lua_State * L);

	int _wrap_eof(lua_State * L)
	{
		File * file = luax_checktype<File>(L, 1, "File", LOVE_WRAP_FILE_BITS);
		lua_pushboolean(L, file->eof() ? 1 : 0);
		return 1;
	}	

	int _wrap_tell(lua_State * L)
	{
		File * file = luax_checktype<File>(L, 1, "File", LOVE_WRAP_FILE_BITS);
		lua_pushinteger(L, file->tell());
		return 1;
	}	

	int _wrap_seek(lua_State * L)
	{
		File * file = luax_checktype<File>(L, 1, "File", LOVE_WRAP_FILE_BITS);
		int pos = luaL_checkinteger(L, 2);
		lua_pushboolean(L, file->seek(pos) ? 1 : 0);
		return 1;
	}	

	// int enumerate(lua_State * L);
	// int lines(lua_State * L);
	// int load(lua_State * L);

	// List of functions to wrap.
	static const luaL_Reg module_fn[] = {
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
		{ "read",  read },
		{ "write",  write },
		{ "eof",  _wrap_eof },
		{ "tell",  _wrap_tell },
		{ "seek",  _wrap_seek },
		{ "enumerate",  enumerate },
		{ "lines",  lines },
		{ "load",  load },
		{ 0, 0 }
	};

	int luareg(lua_State * L)
	{
		luax_register_module(L, "filesystem", module_fn);
		luax_register_type(L, "File", File_mt);
		return 0;
	}

}
}

#endif // LOVE_FILESYSTEM_W
