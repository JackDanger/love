#include "mod.h"

// STD
#include <iomanip>

namespace love_mod
{
	// This is the currently running Lua state. All 
	// modules need to know about this to do error
	// reporting and other stuff.
	lua_State * L = 0;

	// The pointer 
	modconf * conf = 0;

	void setL(lua_State * s)
	{
		L = s;
	}

	lua_State * getL()
	{
		return L;
	}

	void setConf(modconf * c)
	{
		conf = c;
	}

	void error(const std::string & str)
	{
		if(conf->error != 0)
			conf->error(str.c_str());
	}

	void print(const std::string & str)
	{
		if(conf->print != 0)
			conf->print(str.c_str());
	}

	void do_string( const std::string & s )
	{
		if( luaL_dostring(L, s.c_str()) != 0)
		{
			std::cout << "Error in love_mod::do_string." << std::endl;
		}
	}

	void runtime_error( const std::string & e )
	{
		if(L == 0) return;
		luaL_error(L, e.c_str());
	}

	void report_init( const std::string & device, const std::string & provider )
	{
		std::cout << std::setiosflags(std::ios::left) << std::setw(20) << " # " + device + " ";
		std::cout << std::setiosflags(std::ios::left) << "["+provider+"]" << std::endl;
	}

	int call(int narg, int nres)
	{
		int status;
		int base = lua_gettop(L) - narg;  /* function index */
		lua_pushcfunction(L, runtime_error_callback);  /* push traceback function */
		lua_insert(L, base);  /* put it under chunk and args */
		status = lua_pcall(L, narg, nres, base);
		lua_remove(L, base);  /* remove traceback function */
		/* force a complete garbage collection in case of errors */
		if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
		return status;
	}

	void handle_error(int state)
	{
		switch (state)
		{
		// This is actually all the error codes, but
		// writing them here anyway for eventual specialization.
		case LUA_YIELD:
		// In case of run-time errors, lua_runtime_error is also called by Lua. 
		// (Most of the errors in Lua are run-time errors)
		case LUA_ERRRUN:
		case LUA_ERRSYNTAX:
		case LUA_ERRMEM:
		case LUA_ERRERR:
			
			// This is the human readable error message.
			const char * msg = lua_tostring(L, -1);

			// Remove error message.
			lua_pop(L, 1);

			// Print error message.
			printf("%s\n", msg);
			break;
		}
	}

	int runtime_error_callback(lua_State * L)
	{
		lua_getfield(L, LUA_GLOBALSINDEX, "debug");
		if (!lua_istable(L, -1)) {
			lua_pop(L, 1);
			return 1;
		}
		lua_getfield(L, -1, "traceback");
		if (!lua_isfunction(L, -1)) {
			lua_pop(L, 2);
			return 1;
		}
		lua_pushvalue(L, 1);  /* pass error message */
		lua_pushinteger(L, 2);  /* skip this function and traceback */
		lua_call(L, 2, 1);  /* call debug.traceback */

		// Extract message.

		if(lua_isstring(L, -1))
		{
			// For future reference. msg now hold the complete error message (with stack trace).
			const char * msg = lua_tostring(L, -1);
			//lualove_gui_error(msg);
			printf(msg);
		}

		return 1;
	}

} // love_mod
