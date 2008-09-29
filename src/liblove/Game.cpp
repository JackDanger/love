#include <love/Game.h>

// LOVE
#include <love/constants.h>

namespace love
{
	Game::Game()
		: L(0)
	{
	}

	Game::~Game()
	{
		unload();
	}

	bool Game::isLoaded() const
	{
		return (L!=0);
	}

	bool Game::load()
	{
		// Create a new Lua state.
		L = lua_open();

		// Standard libs.
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

		return true;
	}

	void Game::unload()
	{
		if(L!=0)
		{
			lua_close(L);
			L = 0;
		}
	}

} // love
