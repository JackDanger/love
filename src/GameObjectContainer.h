/**
* @file GameObjectContainer.h
* @author Anders Ruud
* @date 2007-06-08
* @brief Contains definition for struct GameObjectContainer.
**/

#ifndef LOVE_GAMEOBJECTCONTAINER_H
#define LOVE_GAMEOBJECTCONTAINER_H

// LOVE
#include "AbstractImage.h"
#include "Sprite.h"
#include "Font.h"
#include "Color.h"
#include "FrameAnimation.h"
#include "Actor.h"
#include "ParticleEmitter.h"
#include "AbstractSound.h"
#include "AbstractMusic.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @struct GameObjectContainer
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-06-08
	* @brief 
	**/
	struct GameObjectContainer
	{
		// Internal Containers
		Container<Loadable> loadables;
		Container<Sprite> sprites;

		// Exposed Containers
		Container<AbstractImage> abstractImages;
		Container<Font> fonts;
		Container<Color> colors;
		Container<FrameAnimation> frameAnimations;
		Container<Actor> actors;		
		Container<ParticleEmitter> particleEmitters;
		Container<AbstractSound> sounds;
		Container<AbstractMusic> music;
	};

} // love

#endif

