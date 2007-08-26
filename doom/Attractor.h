#ifndef LOVE_ATTRACTOR_H
#define LOVE_ATTRACTOR_H

#include "Entity.h"
#include "ParticleEmitter.h"


namespace love
{

	/**
	 * @class Attractor
	 * @version 1.0
	 * @since 1.0
	 * @author Michael Enger
	 * @date 2006-08-21
	 * @brief An attractor which attracts things (like particles).
	 **/
	class Attractor : public Entity
	{
	private:
		ParticleEmitter * particles;
		float range, force;

	public:

		bool doRender;

		Attractor();
		Attractor(float x, float y);
		Attractor(float x, float y, ParticleEmitter * emitter);
		Attractor(float x, float y, ParticleEmitter * emitter, float range, float force);
		~Attractor();

		void setRange(float range);
		void setForce(float force);

		float getRange();
		float getForce();
		float getForce(float distance);


		void update(float dt);
		void render();
	};

	typedef boost::shared_ptr<Attractor> pAttractor;
}

#endif