/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_PARTICLE_SYSTEM_H
#define LOVE_OPENGL_PARTICLE_SYSTEM_H

// LOVE
#include "../constants.h"

// Module
#include "Color.h"
#include "Sprite.h"

// Boost
#include <boost/shared_ptr.hpp>

namespace love_opengl
{
	// Represents a single particle.
	struct particle
	{
		float lifetime;
		float life;

		float position[2];
		float direction;

		float speed[2]; // speed "vector"
		float gravity;
		float radialAcceleration;
		float tangentialAcceleration;

		float color[4];
		
		particle(); // constructor
	};

	/**
	* A class for creating, moving and drawing particles.
	* A big thanks to bobthebloke.org
	*
	* TODO: Use sprites and perhaps add size and rotation.
	*
	* @author Michael Enger
	* @date 2008-04-18
	**/
	class ParticleSystem
	{
	protected:

		// The max amount of particles.
		unsigned int bufferSize;

		// Pointer to the first particle.
		particle * pStart;

		// Pointer to the next available free space.
		particle * pLast;

		// Pointer to the end of the memory allocation.
		particle * pEnd;

		// Whether the particle emitter is active.
		bool active;

		// The emission rate (particles/sec).
		int emissionRate;

		// The lifetime of the particle emitter (-1 means infinite) and the life it has left.
		float lifetime;
		float life;

		// The particle life.
		float particleLifeMin;
		float particleLifeMax;

		// The direction (and spread) the particles will be emitted in. Measured in radians.
		float direction;
		float spread;

		// The speed.
		float speedMin;
		float speedMax;

		// Acceleration towards the bottom of the screen
		float gravityMin;
		float gravityMax;

		// Acceleration towards the emitter's center
		float radialAccelerationMin;
		float radialAccelerationMax;

		// Acceleration perpendicular to the particle's direction.
		float tangentialAccelerationMin;
		float tangentialAccelerationMax;

		// The color.
		pColor colorStart;
		pColor colorEnd;
		float colorVariation;

		void add();
		void remove(particle * p);

	public:
		//ParticleSystem(pSprite sprite, unsigned int buffer);
		/**
		* Creates a particle system by allocating space to the particles and initializing all the values.
		**/
		ParticleSystem(unsigned int buffer);

		/**
		* Deletes any allocated memory.
		**/
		virtual ~ParticleSystem();

		/**
		* Clears the current buffer and allocates the appropriate amount of space for the buffer.
		* @param size The new buffer size.
		**/
		void setBufferSize(unsigned int size);

		/**
		* Sets the emission rate.
		* @param rate The amount of particles per second.
		**/
		void setEmissionRate(int rate);

		/**
		* Sets the lifetime of the particle emitter (-1 means eternal)
		* @param life The lifetime (in seconds).
		**/
		void setLifetime(float life);

		/**
		* Sets the life range of the particles.
		* @param lifeMin The minimum life.
		* @param lifeMax The maximum life (if 0, then becomes the same as minimum life).
		**/
		void setParticleLife(float min, float max = 0);

		/**
		* Sets the direction and the spread of the particle emitter.
		* @param direction The direction (in radians).
		* @param spread The spread (in radians).
		**/
		void setDirection(float direction, float spread = 0);

		/**
		* Sets the speed of the particles.
		* @param min The minimum speed.
		* @param max The maximum speed (if 0 uses minimum speed)
		**/
		void setSpeed(float min, float max = 0);

		/**
		* Sets the gravity of the particles (the acceleration along the y-axis).
		* @param min The minimum gravity.
		* @param max The maximum gravity (if 0 uses minimum gravity)
		**/
		void setGravity(float min, float max = 0);

		/**
		* Sets the radial acceleration (the acceleration towards the particle emitter).
		* @param min The minimum acceleration.
		* @param max The maximum acceleration (if 0 uses minimum acceleration)
		**/
		void setRadialAcceleration(float min, float max = 0);

		/**
		* Sets the tangential acceleration (the acceleration perpendicular to the particle's direction).
		* @param min The minimum acceleration.
		* @param max The maximum acceleration (if 0 uses minimum acceleration)
		**/
		void setTangentialAcceleration(float min, float max = 0);

		/**
		* Sets the color of the particles.
		* @param color The color.
		**/
		void setColor(pColor color);

		/**
		* Sets the color of the particles.
		* @param start The color of the particle when created.
		* @param end The color of the particle upon death.
		**/
		void setColor(pColor start, pColor end);

		/**
		* Sets the color of the particles.
		* @param start The color of the particle when created.
		* @param end The color of the particle upon death.
		* @param variation The amount of variation on the starting color (0 means no variation and 1 means random variation between start and end).
		**/
		void setColor(pColor start, pColor end, float variation);

		/**
		* Sets the amount of variation on the starting color (0 means no variation and 1 means random variation between start and end).
		* @param variation The amount of variation.
		**/
		void setColorVariation(float variation);

		/**
		* Returns the buffer size.
		**/
		unsigned int getBufferSize() const;

		/**
		* Returns the emission rate.
		**/
		int getEmissionRate() const;

		/**
		* Returns the lifetime of the particle emitter.
		**/
		float getLifetime() const;

		/**
		* Returns the amount of particles that are currently active in the system.
		**/
		int count() const;

		/**
		* Starts/resumes the particle emitter.
		**/
		void start();

		/**
		* Stops the particle emitter and resets.
		**/
		void stop();

		/**
		* Pauses the particle emitter.
		**/
		void pause();

		/**
		* Resets the particle emitter.
		**/
		void reset();

		/**
		* Returns whether the particle emitter is active.
		**/
		bool isActive() const;

		/**
		* Returns whether the particle system is empty of particles or not.
		**/
		bool isEmpty() const;

		/**
		* Returns whether the amount of particles has reached the buffer limit or not.
		**/
		bool isFull() const;

		/**
		* Draws the particle emitter at the specified position.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		**/
		void draw(float x, float y) const;

		/**
		* Updates the particle system.
		* @param dt Time since last update.
		**/
		void update(float dt);
	};

	typedef boost::shared_ptr<ParticleSystem> pParticleSystem;
}

#endif
