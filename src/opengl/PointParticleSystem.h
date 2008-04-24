/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_POINT_PARTICLE_SYSTEM_H
#define LOVE_OPENGL_POINT_PARTICLE_SYSTEM_H

// Module
#include "ParticleSystem.h"

namespace love_opengl
{
	/**
	* A class for creating, moving and drawing particles.
	* A big thanks to bobthebloke.org
	*
	* TODO: Use sprites and perhaps add size and rotation.
	*
	* @author Michael Enger
	* @date 2008-04-18
	**/
	class PointParticleSystem : public ParticleSystem
	{
	protected:
	public:

		/**
		* Creates a particle system with the specified buffersize and sprite.
		**/
		PointParticleSystem(pImage sprite, unsigned int buffer);

		/**
		* Draws the particle emitter at the specified position.
		* @param x The x-coordinate.
		* @param y The y-coordinate.
		**/
		void draw(float x, float y) const;
	};

	typedef boost::shared_ptr<PointParticleSystem> pPointParticleSystem;
}

#endif
