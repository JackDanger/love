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

	LuaGameState::LuaGameState(lua_State * L, const string & script) 
		: L(L)
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
				
	}

	void LuaGameState::update(float dt)
	{
		// Call update
		if(isAvailable(LOVE_METHOD_UPDATE))
			lualove_call_update_noarg(L, this, dt);

	}

	void LuaGameState::render()
	{

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


}// love
