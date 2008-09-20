#include "LuaGame.h"

// LOVE
#include <love/Exception.h>
#include "constants.h"

// STD
#include <iostream>

namespace love_system
{
	// Runtime error callback.
	extern int runtime_error(lua_State * L);
	extern void compile_error(lua_State * L, int status);

	LuaGame::LuaGame(love::pFile file, love::Core * core) 
		: Game(file), core(core), L(0)
	{
	}

	LuaGame::~LuaGame()
	{
		unload();
	}

	bool LuaGame::load()
	{
		// Create a new Lua state.
		L = lua_open();

		// Standard libs.
		luaL_openlibs(L);

		// Create the love table.
		lua_newtable(L);

		// Install constants.
		for(int i = 0; constants[i].name != 0; i++)
		{
			lua_pushinteger(L, constants[i].value);
			lua_setfield(L, -2, constants[i].name);
		}

		// Set the love table.
		lua_setglobal(L, "love");

		// Rename load. (Prevents the built-in load from 
		// being detected.
		luaL_dostring(L, "stdload = load; load = nil;");

		// Custom libs.
		if(!core->open((void*)L))
			return false;

		// Load the file serving as the entry point.
		if(!parse(file))
			return false;

		// Check for present functions.
		for(int i =0;i<CALLBACK_SIZE;i++) callbacks[i] = false;
		if(isFunction("load")) callbacks[CALLBACK_LOAD] = true;
		if(isFunction("update")) callbacks[CALLBACK_UPDATE] = true;
		if(isFunction("draw")) callbacks[CALLBACK_DRAW] = true;
		if(isFunction("keypressed")) callbacks[CALLBACK_KEYPRESSED] = true;
		if(isFunction("keyreleased")) callbacks[CALLBACK_KEYRELEASED] = true;
		if(isFunction("mousepressed")) callbacks[CALLBACK_MOUSEPRESSED] = true;
		if(isFunction("mousereleased")) callbacks[CALLBACK_MOUSERELEASED] = true;
		if(isFunction("joystickpressed")) callbacks[CALLBACK_JOYSTICKPRESSED] = true;
		if(isFunction("joystickreleased")) callbacks[CALLBACK_JOYSTICKRELEASED] = true;
		if(isFunction("message")) callbacks[CALLBACK_MESSAGE] = true;
		if(isFunction("event")) callbacks[CALLBACK_EVENT] = true;

		// Call load, if present.
		if(callbacks[CALLBACK_LOAD])
		{
			lua_getglobal(L, "load");
			call(0, 0);
		}

		return true;
	}

	void LuaGame::unload()
	{
		if(L == 0)
			return;
		lua_close(L);
		L = 0;
	}

	bool LuaGame::isLoaded() const
	{
		return (L != 0);
	}

	void LuaGame::update(float dt)
	{
		if(!callbacks[CALLBACK_UPDATE])
			return;
		lua_getglobal(L, "update");
		lua_pushnumber(L, dt);
		call(1, 0);
	}

	void LuaGame::draw()
	{
		if(!callbacks[CALLBACK_DRAW]) 
			return;
		lua_getglobal(L, "draw");
		call(0, 0);
	}

	void LuaGame::keyPressed(int key)
	{
		if(!callbacks[CALLBACK_KEYPRESSED])
			return;
		lua_getglobal(L, "keypressed");
		lua_pushnumber(L, key);
		call(1, 0);
	}

	void LuaGame::keyReleased(int key)
	{
		if(!callbacks[CALLBACK_KEYRELEASED])
			return;
		lua_getglobal(L, "keyreleased");
		lua_pushnumber(L, key);
		call(1, 0);
	}

	void LuaGame::mousePressed(int x, int y, int button)
	{
		if(!callbacks[CALLBACK_MOUSEPRESSED])
			return;
		lua_getglobal(L, "mousepressed");
		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		lua_pushnumber(L, button);
		call(3, 0);
	}

	void LuaGame::mouseReleased(int x, int y, int button)
	{
		if(!callbacks[CALLBACK_MOUSERELEASED])
			return;
		lua_getglobal(L, "mousereleased");
		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		lua_pushnumber(L, button);
		call(3, 0);		
	}

	void LuaGame::mouseMoved(int xrel, int yrel)
	{
		if(!callbacks[CALLBACK_MOUSEMOVED])
			return;
		lua_getglobal(L, "mousemoved");
		lua_pushnumber(L, xrel);
		lua_pushnumber(L, yrel);
		call(2, 0);
	}

	void LuaGame::joystickPressed(int index, int button)
	{
		if(!callbacks[CALLBACK_JOYSTICKPRESSED])
			return;
		lua_getglobal(L, "joystickpressed");
		lua_pushnumber(L, index);
		lua_pushnumber(L, button);
		call(2, 0);
	}

	void LuaGame::joystickReleased(int index, int button)
	{
		if(!callbacks[CALLBACK_JOYSTICKRELEASED])
			return;
		lua_getglobal(L, "joystickreleased");
		lua_pushnumber(L, index);
		lua_pushnumber(L, button);
		call(2, 0);
	}

	void LuaGame::message(const char * msg, int tag)
	{
		if(!callbacks[CALLBACK_MESSAGE])
			return;
		lua_getglobal(L, "message");
		lua_pushstring(L, msg);
		lua_pushnumber(L, tag);
		call(2, 0);
	}


	bool LuaGame::parse(love::pFile file)
	{
		if(!file->load())
			return false;

		int status = luaL_loadbuffer (L, (const char *)file->getData(), 
			file->getSize(), file->getFilename().c_str());

		if(status != 0)
		{
			// Important that this returns true, not false.
			compile_error(L, status);
			return true;
		}

		// Run the loaded chunk.
		call(0, 0);

		return true;
	}

	bool LuaGame::isFunction(const std::string function)
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

	int LuaGame::call(int narg, int nres)
	{
		int status;
		int base = lua_gettop(L) - narg;  /* function index */
		lua_pushcfunction(L, runtime_error);  /* push traceback function */
		lua_insert(L, base);  /* put it under chunk and args */
		status = lua_pcall(L, narg, nres, base);
		lua_remove(L, base);  /* remove traceback function */
		/* force a complete garbage collection in case of errors */
		if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
		return status;
	}

} // love_system
