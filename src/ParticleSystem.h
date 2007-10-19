/**
* @file ParticleSystem.h
* @author Anders Ruud
* @date 2007-08-13
* @brief Contains definition for class ParticleSystem.
**/

#ifndef LOVE_PARTICLESYSTEM_H
#define LOVE_PARTICLESYSTEM_H

// LOVE
#include "AbstractEntity.h"
#include "Sprite.h"
#include "Vector.h"
#include "Loadable.h"
#include "FrameAnimation.h"
#include "AnimatedColor.h"

// STL
#include <list>

using std::list;

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{
	class AbstractColor;

	typedef struct 
	{
		float min;
		float max;
		float delta;
		float var;
	} interval;

	typedef struct
	{

		Vector pos;
		Vector speed;

		//Vector start_pos;
		Vector direction;

		// Time, Mr Freeman?
		float life;
		float age;

		float gravity;
		float radialAcc;
		float tangentialAcc;

		float spin;
		float angle;
		
		interval size;

	} particle;


	/**
	* @class ParticleSystem
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-13
	* @brief 
	**/
	class ParticleSystem : public AbstractEntity, public Loadable
	{
	protected:

		// Additive blending.
		bool additive;

		// Position of Particle System
		Vector pos;

		// Contains all particles
		list<particle> particles;

		// lifetime
		float lifetime;

		// elapsedTime
		float age;
		float linger;

		float spawnBuffer;
		float spawnFreq;

		float particlesPerSecond;

		// sprite
		pSprite sprite;

		// color
		pAnimatedColor color;

		// spread
		interval direction;

		// startSpeed
		interval startSpeed;

		// gravity
		interval gravity;

		// radialAcc
		interval radialAcc;

		// tangentialAcc
		interval tangentialAcc;

		// particleLifetime
		interval particleLifetime;

		// particleSize
		interval particleSize;

		// particleSpin
		interval particleSpin;





		inline float getT(particle & p) const;
		inline Vector getPosition(particle & p) const;
		inline void estimateStart(particle & p);
		inline void displace(particle & p, float dt);
		
		inline float getScalar(interval & i) const;
		inline interval getInterval(interval & i) const;

		inline void fillInterval(interval & i, float min, float max, float var = 0.0f);
		inline Vector getDirection(float angle) const;
		

	public:

		/**
		* @brief Contructs an empty ParticleSystem.
		**/
		ParticleSystem();
		virtual ~ParticleSystem();

		/**
		* @brief Loads the ParticleSystem.
		* Should be called after all variables are set.
		**/
		int load();

		/**
		* @brief Supposed to free resources used by the ParticleSystem.
		* )As of right now, the ParticleSystem uses no resources.)
		**/
		void unload();

		/**
		* @brief Spawns a single particle after the preset rules.
		**/
		void spawn(float age = 0.0f);

		void setAutostart(bool autoStart);

		int getNumParticles() const;

		const list<particle> & getParticles() const;
		const pSprite & getSprite() const;
		const pAnimatedColor & getColor() const;
		bool isAdditive() const;

		void reset();

		/**
		* @brief Sets the position of the ParticleSystem.
		* @param x The x-coordinate of the ParticleSystem.
		* @param y The y-coordinate of the ParticleSystem.
		**/
		void setPosition(float x, float y);

		/**
		* @brief Gets lifetime.
		* @return lifetime.
		**/
		float getLifetime() const;


		/**
		* @brief Sets lifetime.
		* @param lifetime 
		**/
		void setLifetime(float lifetime);

		/**
		* @brief Gets elapsedTime.
		* @return elapsedTime.
		**/
		float getAge() const;

		/**
		* @brief Sets how long the system should be alive after age > life.
		* @param linger The new linger value.
		**/ 
		void setLinger(float linger);

		/**
		* @brief Gets the amount of time this system stays alive after age > life.
		* @return The amount of time to linger after age > life.
		**/
		float getLinger();

		/**
		* @brief Checks whether a system is dead or not.
		* @return True if age >= life + linger (or life = -1),  false otherwise.
		**/
		bool isDead() const;

		/**
		* @brief Checks whether the system is active or not.
		* @return True if age >= life (or life = -1), false otherwise.
		**/
		bool isActive() const;

		/**
		* @brief Gets sprite.
		* @return sprite.
		**/
		//pSprite getSprite();

		void setParticlesPerSecond(float particlesPerSecond);


		/**
		* @brief Gets color.
		* @return color.
		**/
		//AbstractColor getColor();

		

		/**
		* @brief Sets color.
		* @param color 
		**/
		void addColor(int r, int g, int b, int a, float time = 1.0f);
		void addColor(const pColor * color, float time = 1.0f);

		// Note: using pointers so SWIG won't go anal.
		void setSprite(const pSprite * sprite);
		void setSprite(const pAbstractImage * image);
		void setSprite(const pFrameAnimation * anim);

		void setAdditiveBlending(bool additive);

		void setDirection(float min, float max, float var = 0.0f);
		void setDirection(float m);

		void setStartSpeed(float min, float max, float var = 0.0f);
		void setStartSpeed(float m);

		void setGravity(float min, float max, float var = 0.0f);
		void setGravity(float m);

		void setRadialAcc(float min, float max, float var = 0.0f);
		void setRadialAcc(float m);

		void setTangentialAcc(float min, float max, float var = 0.0f);
		void setTangentialAcc(float m);

		void setParticleLifetime(float min, float max, float var = 0.0f);
		void setParticleLifetime(float m);

		void setParticleSize(float min, float max, float var = 0.0f);
		void setParticleSize(float m);

		void setParticleSpin(float min, float max, float var = 0.0f);
		void setParticleSpin(float m);



		virtual void update(float dt);
		virtual void render();


	};

	typedef boost::shared_ptr<ParticleSystem> pParticleSystem;

} // love

#endif

