#ifndef LOVE_PARTICLE_H
#define LOVE_PARTICLE_H

#include <vector>
#include <math.h>
#include "love_gl.h"
#include "Entity.h"
#include "Color.h"

using std::vector;

namespace love
{

	class ParticleController;

	/**
	 * @class Particle
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2006-07-29
	 * @brief A particle which will be spewed forth from a particle emittor.
	 **/
	class Particle : public Entity
	{
	private:
		ParticleController * parent;

		/**
		 * @param time The amount of milliseconds which has passed since last move.
		 * @brief Accelerates the particle in relation to the emitter.
		 **/
		void accelerate(float time);

		/**
		 * @param time The amount of milliseconds which has passed since last move.
		 * @brief Rotates the particle in relation to the emitter.
		 **/
		void rotate(float time);

	public:
		//defining
		Vextor displacement;
		float energy; //how translucent the particle is (255 = max, 0 = invisible)
		float life; //how long the particle has lived
		float rotationRate; //how much the particle should rotate
		float rotation; //how much the particle has been rotated

		Particle();
		Particle(ParticleController * newParent);
		~Particle();
		void update(float dt);
		void render();
	};

	typedef boost::shared_ptr<Particle> pParticle;
}

#endif