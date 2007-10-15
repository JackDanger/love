#include "ScriptableParticle.h"
#include "lualove.h"
#include "love.h"

namespace love
{
	ScriptableParticle::ScriptableParticle()
	{
		load();
		setType(LOVE_TYPE_SCRIPTABLE_PARTICLE);
	}

	ScriptableParticle::ScriptableParticle(ParticleEmitter * parent, lua_State * state, const char * scriptname)
	{
		load();
		this->parent = parent;
		L = state;
		if(scriptname != "")
			setScript(scriptname);
		setType(LOVE_TYPE_SCRIPTABLE_PARTICLE);
	}

	ScriptableParticle::~ScriptableParticle()
	{}

	void ScriptableParticle::init()
	{
		lualove_check_functions(L, this, LOVE_METHOD_ALL);

		if(isAvailable(LOVE_METHOD_LOAD))
			lualove_call_load(L, (void*)this, this->getScript(), this->getType());
		else
			Particle::init();
	}

	void ScriptableParticle::update(float dt)
	{
		if(isAvailable(LOVE_METHOD_UPDATE))
			lualove_call_update(L, (void*)this, this->getScript(), this->getType(), dt);
		else
			Particle::update(dt);
	}

	void ScriptableParticle::render()
	{
		if(isAvailable(LOVE_METHOD_RENDER))
			lualove_call_render(L, (void*)this, this->getScript(), this->getType());
		else
			Particle::render();
	}

	int ScriptableParticle::load()
	{
		L = 0;
		Particle::load();

		return LOVE_OK;
	}

	void ScriptableParticle::unload()
	{}
}