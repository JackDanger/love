#include "LuaScriptableEntity.h"
#include "lualove.h"

namespace love
{

	LuaScriptableEntity::LuaScriptableEntity()
	{
		L = 0;
	}

	LuaScriptableEntity::~LuaScriptableEntity()
	{

	}

	void LuaScriptableEntity::setLuaState(lua_State * L)
	{
		this->L = L;
	}

	void LuaScriptableEntity::load()
	{
		// Check which methods exist.
		lualove_check_functions(L, this, LOVE_METHOD_ALL);

		// Init if available
		if(isAvailable(LOVE_METHOD_INIT))
			lualove_call_init(L, (void*)this, this->getScript(), this->getType());
	}

	void LuaScriptableEntity::update(float dt)
	{
		if(isAvailable(LOVE_METHOD_UPDATE))
			lualove_call_update(L, (void*)this, this->getScript(), this->getType(), dt);
		else
			baseUpdate(dt);
	}

	void LuaScriptableEntity::baseUpdate(float dt)
	{
	}

	void LuaScriptableEntity::render()
	{
		if(isAvailable(LOVE_METHOD_RENDER))
			lualove_call_render(L, (void*)this, this->getScript(), this->getType());
		else
			baseRender();
	}

	void LuaScriptableEntity::baseRender()
	{
	}



}// love
