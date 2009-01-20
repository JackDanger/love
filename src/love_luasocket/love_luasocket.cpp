/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
*
* @author Anders Ruud
* @date 2008-11-06
**/

#include "love_luasocket.h"

// LuaSocket
extern "C" {
#include "luasocket/luasocket.h"
#include "luasocket/mime.h"
}

// Quick macro for adding functions to 
// the preloder.
#define PRELOAD(name, function) \
	lua_getglobal(L, "package"); \
	lua_getfield(L, -1, "preload"); \
	lua_pushcfunction(L, function); \
	lua_setfield(L, -2, name); \
	lua_pop(L, 2);	

namespace love
{
namespace luasocket
{

	int luainfo(lua_State * L)
	{
		love::luax_register_info(L,
			"luasocket",
			"luasocket",
			"LuaSocket",
			"Diego Nehab",
			luaopen);

		return 0;
	}

	int luaopen(lua_State * L)
	{

		// Preload code from LuaSocket.
		PRELOAD("socket.core", luaopen_socket_core);
		PRELOAD("mime.core", luaopen_mime_core);

		PRELOAD("socket", luaopen_luasocket_socket);
		PRELOAD("socket.ftp", luaopen_luasocket_ftp)
		PRELOAD("socket.http", luaopen_luasocket_http);
		PRELOAD("ltn12", luaopen_luasocket_ltn12);
		PRELOAD("mime", luaopen_luasocket_mime)
		PRELOAD("socket.smtp", luaopen_luasocket_smtp);
		PRELOAD("socket.tp", luaopen_luasocket_tp)
		PRELOAD("socket.url", luaopen_luasocket_url)

		// No need to register garbage collector function.

		return 0;
	}

	int luagc(lua_State * L)
	{
		return 0;
	}

	int luaopen_luasocket_socket(lua_State * L)
	{
		#include "luasocket/socket.lua.h"
		lua_getglobal(L, "socket");
		return 1;
	}

	int luaopen_luasocket_ftp(lua_State * L)
	{
		#include "luasocket/ftp.lua.h"
		lua_getglobal(L, "socket.ftp");
		return 1;
	}

	int luaopen_luasocket_http(lua_State * L)
	{
		#include "luasocket/http.lua.h"
		lua_getglobal(L, "socket.http");
		return 1;
	}

	int luaopen_luasocket_ltn12(lua_State * L)
	{
		#include "luasocket/ltn12.lua.h"
		lua_getglobal(L, "ltn12");
		return 1;
	}

	int luaopen_luasocket_mime(lua_State * L)
	{
		#include "luasocket/mime.lua.h"
		lua_getglobal(L, "mime");
		return 1;
	}

	int luaopen_luasocket_smtp(lua_State * L)
	{
		#include "luasocket/smtp.lua.h"
		lua_getglobal(L, "socket.smtp");
		return 1;
	}

	int luaopen_luasocket_tp(lua_State * L)
	{
		#include "luasocket/tp.lua.h"
		lua_getglobal(L, "socket.tp");
		return 1;
	}

	int luaopen_luasocket_url(lua_State * L)
	{
		#include "luasocket/url.lua.h"
		lua_getglobal(L, "socket.url");
		return 1;
	}

} // luasocket
} // love
