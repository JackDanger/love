/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This module simply exposes the functionality
* present in LuaSocket. 
*
* Webpage:
* http://www.tecgraf.puc-rio.br/~diego/professional/luasocket/
* 
* 
* @author Anders Ruud
* @date 2008-11-06
**/

#ifndef LOVE_LUASOCKET_LUASOCKET_H
#define LOVE_LUASOCKET_LUASOCKET_H

// LOVE
#include "../luax.h"

namespace love
{
namespace luasocket
{
	int __open(lua_State * L);

	// Loaders for all lua files. We want to be able
	// to load these dynamically. (Identical in the LuaSocket 
	// documentation. These functions wrap the parsing of code, etc).
	int __open_luasocket_socket(lua_State * L);
	int __open_luasocket_ftp(lua_State * L);
	int __open_luasocket_http(lua_State * L);
	int __open_luasocket_ltn12(lua_State * L);
	int __open_luasocket_mime(lua_State * L);
	int __open_luasocket_smtp(lua_State * L);
	int __open_luasocket_tp(lua_State * L);
	int __open_luasocket_url(lua_State * L);

} // luasocket
} // love

#endif // LOVE_LUASOCKET_LUASOCKET_H
