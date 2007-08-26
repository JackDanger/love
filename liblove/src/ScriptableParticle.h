#ifndef LOVE_SCRIPTABLE_PARTICLE_H
#define LOVE_SCRIPTABLE_PARTICLE_H

#include "Particle.h"

struct lua_State;

namespace love
{
	/**
	* @class ScriptableParticle
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-06-13
	* @brief A scriptable version of the Particle.
	**/
	class ScriptableParticle : public Particle
	{
	protected:
		lua_State * L;

	public:
		ScriptableParticle();
		ScriptableParticle(ParticleEmitter * parent, lua_State * state, const char * scriptname);
		~ScriptableParticle();

		/**
		 * @brief Does nothing.
		 **/
		virtual void init();

		/**
		 * @param dt Time elapsed in milliseconds.
		 * @brief Updates the texture and increments velocity with acceleration and position with velocity.
		 **/
		virtual void update(float dt);

		/**
		 * @brief Renders a point sprite using the position as center.
		 **/
		virtual void render();

		/**
	 	 * @brief Initializes all the variables as 0.
	 	 **/
		virtual int load();

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void unload();
	};

	typedef boost::shared_ptr<ScriptableParticle> pScriptableParticle;
}

#endif
