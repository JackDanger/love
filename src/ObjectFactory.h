/**
* @file ObjectFactory.h
* @author Anders Ruud
* @date 2007-08-27
* @brief Contains definition for class ObjectFactory.
**/

#ifndef LOVE_OBJECTFACTORY_H 
#define LOVE_OBJECTFACTORY_H 

// LOVE
#include "AbstractImage.h"
#include "FrameAnimation.h"
#include "AbstractSound.h"
#include "AbstractMusic.h"
#include "Font.h"
#include "Color.h"
#include "ParticleSystem.h"
#include "Bezier.h"


// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class ObjectFactory
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-27
	* @brief 
	**/
	class ObjectFactory
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty ObjectFactory.
		**/
		ObjectFactory();
		
		/**
		* @brief Destructor.
		**/
		virtual ~ObjectFactory();

		pAbstractImage newImage(const char * filename) const;

		pFrameAnimation newAnimation(const pAbstractImage * image);
		pFrameAnimation newAnimation(const pAbstractImage * image, int xFrames, int yFrames, int frameWidth, int frameHeight, float delay);

		pAbstractMusic newMusic(const char * filename) const;
		pAbstractSound newSound(const char * filename) const;

		pColor newColor(int r, int g, int b, int a = 255) const;
		pColor newColor(int code, int a = 255) const;
		pFont newDefaultFont(int size) const;
		pFont newFont(const char * filename, int size) const;

		pParticleSystem newParticleSystem() const;

		pBezier newBezier() const;
		pBezier newBezier(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) const;
		
	}; // ObjectFactory
	
	typedef boost::shared_ptr<ObjectFactory> pObjectFactory;
	
} // love

#endif
