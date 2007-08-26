/**
* @file AbstractSound.h
* @author Anders Ruud
* @date 2007-08-19
* @brief Contains definition for class AbstractSound.
**/

#ifndef LOVE_ABSTRACTSOUND_H 
#define LOVE_ABSTRACTSOUND_H 

// LOVE
#include "Object.h"
#include "Resource.h"
#include "Loadable.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class AbstractFile;

	/**
	* @class AbstractSound
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-19
	* @brief 
	**/
	class AbstractSound : public Object, public Resource, public Loadable
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty AbstractSound.
		**/
		AbstractSound(AbstractFile * file);
		
		/**
		* @brief Destructor.
		**/
		virtual ~AbstractSound();

		/**
		* @brief Plays the sound.
		* @param loop The number of loops. Default is 1, -1 for forever.
		**/
		virtual void play(int loop = 0) = 0;

		/**
		* @brief Sets the volume for this sound.
		* @param volume The volume from 0.0 - 1.0.
		**/
		virtual void setVolume(float volume) = 0;
		
	}; // AbstractSound
	
	typedef boost::shared_ptr<AbstractSound> pAbstractSound;
	
} // love

#endif
