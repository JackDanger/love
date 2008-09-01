/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* This module simply exposes the functionality
* present in LuaSocket. 
*
* Webpage:
* http://www.tecgraf.puc-rio.br/~diego/professional/luasocket/
* 
* 
* @author Anders Ruud
* @date 2008-08-31
*/

#ifndef LOVE_MOD_luaopen_luasocket_H
#define LOVE_MOD_luaopen_luasocket_H

// LOVE
#include <love/mod.h>

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_luasocket
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

	// Loaders for all lua files. We want to be able
	// to load these dynamically. (Identical in the LuaSocket 
	// documentation. These functions wrap the parsing of code, etc).
	int luaopen_luasocket_socket(lua_State * L);
	int luaopen_luasocket_ftp(lua_State * L);
	int luaopen_luasocket_http(lua_State * L);
	int luaopen_luasocket_ltn12(lua_State * L);
	int luaopen_luasocket_mime(lua_State * L);
	int luaopen_luasocket_smtp(lua_State * L);
	int luaopen_luasocket_tp(lua_State * L);
	int luaopen_luasocket_url(lua_State * L);

} // love_luasocket

#endif // LOVE_MOD_luaopen_luasocket_H
