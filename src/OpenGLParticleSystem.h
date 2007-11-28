/**
* @file OpenGLParticleSystem.h
* @author Anders Ruud
* @date 2007-08-13
* @brief Contains definition for class OpenGLParticleSystem.
**/

#ifndef LOVE_OpenGLParticleSystem_H
#define LOVE_OpenGLParticleSystem_H

// LOVE
#include "ParticleSystem.h"

namespace love
{

	/**
	* @class OpenGLParticleSystem
	* @brief 
	**/
	class OpenGLParticleSystem : public ParticleSystem
	{
	protected:

	public:

		OpenGLParticleSystem();
		virtual ~OpenGLParticleSystem();

		virtual void render();
		virtual void render(float x, float y);
	};

	typedef boost::shared_ptr<OpenGLParticleSystem> pOpenGLParticleSystem;

} // love

#endif

