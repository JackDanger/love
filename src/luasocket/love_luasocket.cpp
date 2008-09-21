#include "love_luasocket.h"

// LuaSocket
extern "C" {
#include "luasocket/luasocket.h"
#include "luasocket/mime.h"
}

// LOVE
#include <love/Core.h>

// Quick macro for adding functions to 
// the preloder.
#define PRELOAD(name, function) \
	lua_getglobal(L, "package"); \
	lua_getfield(L, -1, "preload"); \
	lua_pushcfunction(L, function); \
	lua_setfield(L, -2, name); \
	lua_pop(L, 2);	

namespace love_luasocket
{
	bool module_init(int argc, char ** argv, love::Core * core)
	{
		std::cout << "INIT love.lib [LuaSocket] "<< std::endl;
		return true;
	}

	bool module_quit()
	{
		std::cout << "QUIT love.lib [LuaSocket] "<< std::endl;
		return true;
	}

	bool module_open(void * vm)
	{
		lua_State * L = (lua_State *)vm;
		if(L == 0)
			return false;
		
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

		return true;
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

} // love_luasocket
