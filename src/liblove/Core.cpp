#include <love/Core.h>

// STD
#include <iostream>
#include <cstdarg>

// LOVE
#include <love/constants.h>

namespace love
{
	Core * core = 0;

	Core::Core()
	{
		// Only do this once.
		if(core != 0)
			return;

		// Create a Lua state.
		L = lua_open();

		// Open standard libraries.
		luaL_openlibs(L);

		// Create the love table.
		lua_newtable(L);

		// Install constants.
		for(int i = 0; lua_constants[i].name != 0; i++)
		{
			lua_pushinteger(L, lua_constants[i].value);
			lua_setfield(L, -2, lua_constants[i].name);
		}

		// Set the love table.
		lua_setglobal(L, "love");

		// TODO: IMPROVE
		// Rename load. (Prevents the built-in load from 
		// being detected.
		luaL_dostring(L, "stdload = load; load = nil;");
		
		luaL_dofile(L, "love.lua");
	
		love::core = this;
	}

	Core::~Core()
	{
		// Unload modules in reverse order.
		while(!modules.empty())
		{
			// Tell the module to quit.
			Module & m = modules.back();
			m.quit(this);

			// Remove it from the list.
			modules.pop_back();
		}

		lua_close(L);
	}

	int Core::init()
	{
		lua_getglobal(L, "love");
		lua_getfield(L, -1, "init");
		if(!lua_isfunction(L, -1))
			return 1;
		lua_call(L, 0, 2);
		bool success = lua_toboolean(L, -2) == 1;
		lua_pop(L, lua_gettop(L));
		return success ? 0 : 2;
	}

	void Core::setArg(int argc, char ** argv)
	{
		lua_newtable(L);
		for(int i=0; i<argc; i++)
		{
			lua_pushinteger(L, i-1);
			lua_pushstring(L, argv[i]);
			lua_settable(L, -3);
		}
		lua_setglobal(L, "arg");
	}

	void Core::addSearcher(lua_CFunction f)
	{
		lua_getglobal(L, "package");
		lua_getfield(L, -1, "loaders");
		int next = (int)lua_objlen(L, -1)+1;
		lua_pushcfunction(L, f);
		lua_rawseti(L, -2, next);
		lua_pop(L, 2);
	}

	bool Core::insert(Module module)
	{
		// Open the Lua library.
		if(!module.open(this))
		{
			std::cerr << "Could not open the module." << std::endl;
			return false;
		}

		// Load the module.
		if(!module.init(this))
		{
			std::cerr << "Could not init the module." << std::endl;
			return false;
		}

		// Add it to the list of modules.
		// Note that this must happen *BEFORE* module_init, 
		// otherwise love.system won't b included.
		modules.push_back(module);

		return true;
	}

	bool Core::error(const char * fmt, ...)
	{
		va_list argp;
		va_start(argp,fmt);
		lua_pushvfstring(L, fmt, argp);
		va_end(argp);
		lua_error(L);
		return false;
	}

} // love
