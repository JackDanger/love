#ifndef LOVE_PARTICLE_H
#define LOVE_PARTICLE_H

#include "VisualEntity.h"

namespace love
{
	class ParticleEmitter;

	/**
	* @class Particle
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-05-22
	* @brief A particle; a non-corporeal entity which is created by a ParticleEmitter and which utilizes point
	*		 sprites (where available).
	**/
	class Particle : public VisualEntity
	{
	protected:
		ParticleEmitter * parent;
		float life; //how long it will life
		float lifetime; //how long it has lived
		bool fade; //whether the particle fades

	public:
		/**
		 * @brief Default constructor. Clears variables and declares this as a Particle type.
		 **/
		Particle();

		/**
		 * @param parent The parent ParticleEmitter.
		 * @brief Clears variables, sets the parent as the passed parameter and declares this as a Particle type.
		 **/
		Particle(ParticleEmitter * parent);

		/**
		 * @brief Does nothing.
		 **/
		~Particle();

		/**
		 * @return The life (in seconds).
		 * @brief Returns the amount of life the particle has (how long it will stay onscreen).
		 **/
		float getLife();

		/**
		 * @return The lifetime (in seconds).
		 * @brief Returns the amount of lifetime the particle has "survied" (how long it has stayed onscreen).
		 **/
		float getLifetime();

		/**
		 * @return Whether the particle fades.
		 * @brief Returns whether or not the particle should fade when as it expends its lifetime.
		 **/
		bool getFade();

		/**
		 * @return Whether the Particle is alive or not.
		 * @brief If the lifetime is greater than the life, the Particle is considered dead and false is returned.
		 **/
		bool isAlive();

		/**
		 * @param life The new life (in seconds).
		 * @brief Sets the life of the particle (how long it will stay onscreen).
		 **/
		void setLife(float life);

		/**
		 * @param lifetime The new lifetime (in seconds).
		 * @brief Sets the lifetime of the particle (how long it has stayed onscreen).
		 **/
		void setLifetime(float lifetime);

		/**
		 * @param fade Whether the particle will fade or not.
		 * @brief Sets wether the particle will fade or not.
		 **/
		void setFade(bool fade);

		/**
		 * @param sprite A pointer to a Sprite object.
		 * @brief Sets the sprite of the particle.
		 **/
		void setSprite(Sprite * sprite);

		/**
		 * @param name The name of the Sprite which should be used.
		 * @brief Sets the sprite of the particle which it gets from the parent ParticleEmitter.
		 **/
		void setSprite(const char * name);

		/**
		 * @brief Sets the position of the particle as the position of the parent ParticleEmitter.
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

	typedef boost::shared_ptr<Particle> pParticle;
}

#endif
