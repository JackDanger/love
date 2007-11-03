#include "ScriptableActorState.h"
#include "lualove.h"
#include "Actor.h"
#include "love.h"

namespace love
{
	ScriptableActorState::ScriptableActorState(Actor * parent, lua_State * state, const char * scriptname)
	{
		VisualEntity::load();
		this->parent = parent;
		L = state;
		setScript(scriptname);
		setType(LOVE_TYPE_SCRIPTABLE_ACTOR_STATE);
	}

	ScriptableActorState::~ScriptableActorState()
	{
	}

	void ScriptableActorState::init()
	{
		lualove_check_functions(L, this, LOVE_METHOD_ALL);

		if(isAvailable(LOVE_METHOD_LOAD))
			lualove_call_load(L, (void*)this, this->getScript(), this->getType());
	}

	void ScriptableActorState::render()
	{
		if(isAvailable(LOVE_METHOD_RENDER))
			lualove_call_render(L, (void*)this, this->getScript(), this->getType());
		else
			ActorState::render();
	}

	void ScriptableActorState::update(float dt)
	{
		if(isAvailable(LOVE_METHOD_UPDATE))
			lualove_call_update(L, (void*)this, this->getScript(), this->getType(), dt);
		else
			ActorState::update(dt);
	}

	int ScriptableActorState::load()
	{
		return LOVE_OK;
	}

	void ScriptableActorState::unload()
	{
	}
}
