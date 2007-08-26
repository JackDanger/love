#ifndef LOVE_PARTICLE_EMITTER_H
#define LOVE_PARTICLE_EMITTER_H

#include <vector>
#include <map>
#include <cmath>
#include <ctime>

#include "Container.h"
#include "Entity.h"
#include "ScriptableParticle.h"
#include "Renderable.h"

using std::vector;
using std::map;

struct lua_State;

namespace love
{
	/**
	* @class ParticleEmitter
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-05-22
	* @brief An object used to create, update and render particles.
	**/
	class ParticleEmitter : public Entity
	{
	protected:
		lua_State * L;
		Container<Sprite> * sprites;

		Container<ScriptableParticle> models; //objects of particles which should be emitted
		vector<ScriptableParticle> particles; //the particles that have been emitted
		int particle; //which particle was emitted
		int mode; //the mode
		float delay; //how much time should pass before a new particle is emitted
		float elapsed; //how much time has passed since last particle was emitted
		bool active; //whether the emitter is active
		bool direction; //used for bounce mode (true = right way, false = wrong way)

	public:
		const static int LOVE_PARTICLE_MODE_LOOP = 1;
		const static int LOVE_PARTICLE_MODE_BOUNCE = 2;
		const static int LOVE_PARTICLE_MODE_ONCE = 3;
		const static int LOVE_PARTICLE_MODE_SIMULTANEOUS = 4;
		const static int LOVE_PARTICLE_MODE_RANDOM = 5;

		/**
		 * @brief Calls the load function.
		 * @see load()
		 **/
		ParticleEmitter(lua_State * state = 0, Container<Sprite> * sprites = 0);

		/**
		 * @brief Calls the load function and then sets the mode (if not 0) and delay.
		 * @see load()
		 **/
		ParticleEmitter(float delay, int mode = 1);

		/**
		 * @breif Does nothing.
		 **/
		~ParticleEmitter();

		/**
		 * @param name The name of the new particle.
		 * @param newParticle A formatted particle.
		 * @return A pointer to the particle which is now in the container.
		 * @brief Adds the newParticle to the container of models.
		 **/
		ScriptableParticle * addParticle(const char * name, ScriptableParticle * newParticle);

		/**
		 * @param name The name of the new particle.
		 * @return A pointer to the particle which is now in the container.
		 * @brief Adds a new (empty) particle to the container of models.
		 **/
		ScriptableParticle * addParticle(const char * name);

		/**
		 * @param name The name of the new particle.
		 * @param script The name of the script which will handle the new particle.
		 * @return A pointer to the particle which is now in the container.
		 * @brief Adds a new (empty) scriptable particle to the container of models and sets the script as the particle's script.
		 **/
		ScriptableParticle * addParticle(const char * name, const char * script);

		/**
		 * @param name The name of the sought particle.
		 * @return Pointer to a particle.
		 * @brief Returns the particle which is associated with the passed name. If it doesn't exist returns 0.
		 **/
		ScriptableParticle * getParticle(const char * name);

		Sprite * getSprite(const char * name);

		/**
		 * @return A particle emitter mode.
		 * @brief Returns the current emitter mode.
		 **/
		int getMode();

		/**
		 * @return The delay time (in seconds).
		 * @brief Returns the amount of delay time.
		 **/
		float getDelay();

		/**
		 * @return A boolean value.
		 * @brief Returns whether the emitter is active.
		 **/
		bool isActive();

		/**
		 * @param mode A particle emitter mode.
		 * @brief Sets the current mode.
		 **/
		void setMode(int mode);

		/**
		 * @param delay The new amount of delay (in seconds).
		 * @brief Sets the delay.
		 **/
		void setDelay(float delay);

		/**
		 * @brief Starts the emitter.
		 **/
		void play();

		/**
		 * @brief Stops the emitter.
		 **/
		void stop();

		/**
		 * @param dt Time elapsed in milliseconds.
		 * @brief Updates the particles and adds new ones if required.
		 **/
		virtual void update(float dt);

		/**
		 * @brief Renders all the particles.
		 **/
		virtual void render();

		/**
	 	 * @brief Initializes all the variables as 0 and calls the load function in Entity.
		 * @see Entity::load()
	 	 **/
		virtual int load();

		/**
	 	 * @brief Does nothing.
	 	 **/
		virtual void unload();
	};

	typedef boost::shared_ptr<ParticleEmitter> pParticleEmitter;
}

#endif
