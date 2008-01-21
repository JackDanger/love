/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_OPENGL_PARTICLE_SYSTEM_H
#define LOVE_OPENGL_PARTICLE_SYSTEM_H

// LOVE
#include "Particlesystem.h"

namespace love
{

	/**
	* OpenGL implementaiton of particle system renderer. 
	*
	* @author Anders Ruud
	* @date 2007-08-13
	**/
	class OpenGLParticleSystem : public Particlesystem
	{
	protected:
	public:

		
		OpenGLParticleSystem();

		virtual ~OpenGLParticleSystem();

		// From Particlesystem
		void render() const;
		void render(float x, float y) const;

	}; // OpenGLParticleSystem

} // love

#endif // LOVE_OPENGL_PARTICLE_SYSTEM_H

