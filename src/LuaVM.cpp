#include "LuaVM.h"

// LOVE
#include "lualove_glue.h"

namespace love
{

	// Forward declaration.
	int lua_runtime_error(lua_State * L);

	LuaVM::LuaVM()
	{
	}

	LuaVM::~LuaVM()
	{
	}

	bool LuaVM::open()
	{
		L = lua_open();
		//luaopen_love(L);
		//int SWIG_init(lua_State* L)
		luaL_openlibs(L);
		Love_Init(L);
		return true;
	}

	void LuaVM::close()
	{
		// End Lua-state
		lua_close(L);
	}

	bool LuaVM::load(pFile file)
	{
		file->load();

		int result = luaL_loadbuffer (	L,
										(const char *)file->getData(), 
										file->getSize(),
										file->getFilename().c_str());

		// Could not load file, for some reason.
		if(result != 0)
		{
			// Get error message.
			const char * msg = lua_tostring(L, -1);
			lua_pop(L, 1);
			printf("%s\n", msg);
			//lualove_gui_error(msg);

			return false;
		}

		// Run the loaded chunk.
		int status = call(0);
		handleError(status);

		return (status == 0);
	}

	bool LuaVM::isFunction(const std::string & function)
	{
		lua_pushstring(L, function.c_str());
		lua_rawget(L, LUA_GLOBALSINDEX);

		if(lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return true;
		}

		lua_pop(L, 1);
		return false;
	}

	bool LuaVM::isFunction(const std::string & table, const std::string & function)
	{
		lua_pushstring(L, table.c_str());
		lua_rawget(L, LUA_GLOBALSINDEX);

		if(lua_istable(L, -1))
		{
			lua_pushstring(L, function.c_str());
			lua_rawget(L, -2);
			bool result = lua_isfunction(L, -1);
			lua_pop(L, 2);
			return result;
		}else
		{
			lua_pop(L, 1);
			return false;
		}
	}

	void LuaVM::call(const std::string & function)
	{
		lua_getglobal(L, function.c_str());
		int status = call(0);
		handleError(status);
	}

	void LuaVM::calln(const std::string & function, float n)
	{
		lua_getglobal(L, function.c_str());
		lua_pushnumber(L, n);
		int status = call(1);
		handleError(status);
	}

	void LuaVM::call3n(const std::string & function, float n1, float n2, float n3)
	{
		lua_getglobal(L, function.c_str());
		lua_pushnumber(L, n1);
		lua_pushnumber(L, n2);
		lua_pushnumber(L, n3);
		int status = call(3);
		handleError(status);
	}

	void LuaVM::call1n2n(const std::string & table, const std::string & function, float n, float & r1, float & r2)
	{
		lua_getglobal(L, table.c_str()); // Push table
		lua_getfield(L, 1, function.c_str());	// Push render

		// Params
		lua_pushnumber(L, n);

		int status = call(1, 2);
		handleError(status);

		// Return values. (Reverse order)
		if(lua_isnumber(L, -1))
		{
			r2 = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}
		if(lua_isnumber(L, -1))
		{
			r1 = (float)lua_tonumber(L, -1);
			lua_pop(L, 1);
		}

		lua_pop(L, 1);				// Pops table
	}

	int LuaVM::call(int narg, int nres)
	{
		int status;
		int base = lua_gettop(L) - narg;  /* function index */
		lua_pushcfunction(L, lua_runtime_error);  /* push traceback function */
		lua_insert(L, base);  /* put it under chunk and args */
		status = lua_pcall(L, narg, nres, base);
		lua_remove(L, base);  /* remove traceback function */
		/* force a complete garbage collection in case of errors */
		if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
		return status;
	}

	void LuaVM::handleError(int state)
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


	/**
	* Functions outside LuaVM.
	**/

	// Calls traceback in case of runtime errors.
	int lua_runtime_error(lua_State * L)
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
		
} // love

