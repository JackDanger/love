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
#include "Sprite.h"

// Boost
#include <boost/shared_ptr.hpp>

namespace love_opengl
{
	// Represents a single particle.
	struct particle
	{
		float position[2];
		float direction[3];
		float color[3];
		float life;
		particle(); //constructor
	};

	/**
	* A class for creating, moving and drawing particles.
	* A big thanks to bobthebloke.org
	*
	* @author Michael Enger
	* @date 2008-04-18
	**/
	class ParticleSystem
	{
	protected:
		unsigned int bufferSize;
		particle * start; // the first particle
		particle * last; // the next free space
		particle * end; // the end of the memory allocation
		float shoot;

		void add();
		void remove(particle * p);

	public:
		//ParticleSystem(pSprite sprite, unsigned int buffer);
		ParticleSystem(unsigned int buffer);
		virtual ~ParticleSystem();

		void setBufferSize(unsigned int size);

		unsigned int getBufferSize() const;

		int count() const;
		bool isEmpty() const;
		bool isFull() const;

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
