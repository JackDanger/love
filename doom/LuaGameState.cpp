#include "LuaGameState.h"

// Lua
extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include "lualove.h"

namespace love
{

	LuaGameState::LuaGameState()
	{
		setType(LOVE_TYPE_LUA_GAMESTATE);
	}

	LuaGameState::LuaGameState(GameObjectContainer * master, lua_State * L, const string & script) 
		: GameState(master), L(L)
	{
		this->setScript(script);
		setType(LOVE_TYPE_LUA_GAMESTATE);
	}

	LuaGameState::~LuaGameState()
	{
	}

	void LuaGameState::init()
	{
		lualove_check_functions(L, this, LOVE_METHOD_ALL);

		// Call init
		if(isAvailable(LOVE_METHOD_INIT))
			lualove_call_init_noarg(L, this);

		// Init ALL Actors
		//for(obj.actors.begin(); !obj.actors.end(); obj.actors.next())
		//	obj.actors.value()->init();

	}

	void LuaGameState::update(float dt)
	{
		// Update ALL Actors
		for(obj.actors.begin(); !obj.actors.end(); obj.actors.next())
			obj.actors.value()->update(dt);

		// Call update
		if(isAvailable(LOVE_METHOD_UPDATE))
			lualove_call_update_noarg(L, this, dt);

	}

	void LuaGameState::render()
	{

		// Render ALL Actors
		for(obj.actors.begin(); !obj.actors.end(); obj.actors.next())
			obj.actors.value()->render();

		if(isAvailable(LOVE_METHOD_RENDER))
			lualove_call_render_noarg(L, this);
	}

	void LuaGameState::keyPressed(int key)
	{
		if(isAvailable(LOVE_METHOD_KEYPRESSED))
			lualove_call_keypressed_noarg(L, this, key);
	}

	void LuaGameState::keyReleased(int key)
	{
		if(isAvailable(LOVE_METHOD_KEYRELEASED))
			lualove_call_keyreleased_noarg(L, this, key);
	}

	void LuaGameState::mousePressed(float x, float y, int button)
	{
		if(isAvailable(LOVE_METHOD_MOUSEPRESSED))
			lualove_call_mousepressed_noarg(L, this, x, y, button);
	}

	void LuaGameState::mouseReleased(float x, float y, int button)
	{
		if(isAvailable(LOVE_METHOD_MOUSERELEASED))
			lualove_call_mousereleased_noarg(L, this, x, y, button);
	}


	void LuaGameState::load()
	{
		for(obj.loadables.begin(); !obj.loadables.end(); obj.loadables.next())
			obj.loadables.value()->load();
	}

	void LuaGameState::unload()
	{
		for(obj.loadables.begin(); !obj.loadables.end(); obj.loadables.next())
			obj.loadables.value()->unload();
	}


}// love
