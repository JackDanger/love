#include "ActorState.h"
#include "Actor.h"
#include "love.h"

namespace love
{
	ActorState::ActorState()
	{
		VisualEntity::load();
		parent = 0;
		setType(LOVE_TYPE_ACTOR_STATE);
	}

	ActorState::ActorState(Actor * parent)
	{
		VisualEntity::load();
		this->parent = parent;
		setType(LOVE_TYPE_ACTOR_STATE);
	}

	ActorState::~ActorState()
	{
	}

	void ActorState::init()
	{
	}

	void ActorState::setSprite(const char * name)
	{
		if(parent != 0)
			sprite = parent->getSprite(name);
	}

	void ActorState::setSprite(Sprite * sprite)
	{
		this->sprite = sprite;
	}

	int ActorState::load()
	{
		return LOVE_OK;
	}

	void ActorState::unload()
	{
	}
}
