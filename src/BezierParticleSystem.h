/**
* @file BezierParticleSystem.h
* @author Anders Ruud
* @date 2007-08-29
* @brief Contains definition for class BezierParticleSystem.
**/

#ifndef LOVE_BEZIERPARTICLESYSTEM_H 
#define LOVE_BEZIERPARTICLESYSTEM_H 

// LOVE
#include "ParticleSystem.h"
#include "Bezier.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class BezierParticleSystem
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-29
	* @brief 
	**/
	class BezierParticleSystem : public ParticleSystem
	{
	private:
	
		// The bezier used to map the rendering of the system.
		pBezier bezier;

		// The number of particles used to render the Bezier.
		int precision;

		// The current particle. (For shoot-ray-mode).
		float current;

		// Time taken to render entire Bezier.
		float speed;

	public:
	
		/**
		* @brief Constructs an empty BezierParticleSystem.
		**/
		BezierParticleSystem();
		
		/**
		* @brief Destructor.
		**/
		virtual ~BezierParticleSystem();

		void setBezier(const pBezier * bezier);
		void setPrecision(int precision);
		void setSpeed(float time);

		virtual void update(float dt);
		//virtual void render();

	private:
		
	}; // BezierParticleSystem
	
	typedef boost::shared_ptr<BezierParticleSystem> pBezierParticleSystem;
	
} // love

#endif
