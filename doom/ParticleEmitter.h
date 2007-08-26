#ifndef LOVE_PARTICLEEMITTER_H
#define LOVE_PARTICLEEMITTER_H

#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>
#include <string.h>
#include "love_gl.h"
#include "Particle.h"
#include "ParticleController.h"
#include "Vextor.h"

using std::vector;


namespace love
{
	class Particle;

	/**
	 * @class ParticleEmitter
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2006-07-31
	 * @brief This is a class which spews forth Particles.
	 **/
	class ParticleEmitter : public ParticleController
	{
	private:
		GradientColor gradient;

		bool active;
		int ammunition; //how many particles emitted per burst
		float reloadRate; //how long between bursts of particles (in seconds)
		float reloading; //used to find out if a burst is to come

		void init(float x, float y);

	public:

		bool doRender;

		Tileset * image;
		ParticleEmitter();
		ParticleEmitter(float x, float y, Color color);
		ParticleEmitter(float x, float y, GradientColor gradient);
		ParticleEmitter(float x, float y, string filename);
		ParticleEmitter(float x, float y, string filename, int width, int height);
		//ParticleEmitter(float x, float y, Texture texture);
		ParticleEmitter(float x, float y, Tileset tileset);
		~ParticleEmitter();

		/**
		 * @brief Activates the emitter. Required to start.
		 **/
		void start();

		/**
		 * @brief De-activates the emitter, but it can be restared with start()
		 **/
		void stop();

		/**
		 * @param dt Delta time.
		 * @brief Updates all the particles (calling the function update(dt) in each), removes those who are dead and adds new ones if needed.
		 **/
		void update(float dt);

		/**
		 * @brief Calls the render() function in each particle and, for testing purposes, draws a red square.
		 **/
		void render();

		/**
		 * @param ammo How many particles are emitted per cycle.
		 * @param rate The time of the cycle.
		 * @brief Sets the ammunition and reloadRate.
		 **/
		void setAmmo(int ammo, float rate);

		/**
		 * @return A boolean; true = the particles fade, false = the particles do NOT fade
		 * @brief Returns whether the particles fade or not.
		 **/
		bool fades();

		/**
		 * @return How much time between particle emittions.
		 * @brief Returns the variable reloadRate.
		 **/
		float getReloadRate();

	};

	typedef boost::shared_ptr<ParticleEmitter> pParticleEmitter;
}

#endif