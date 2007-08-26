/**
* @file AbstractMusic.h
* @author Anders Ruud
* @date 2007-08-19
* @brief Contains definition for class AbstractMusic.
**/

#ifndef LOVE_ABSTRACTMUSIC_H 
#define LOVE_ABSTRACTMUSIC_H 

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
	* @class AbstractMusic
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-19
	* @brief 
	**/
	class AbstractMusic : public Object, public Resource, public Loadable
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty AbstractMusic.
		**/
		AbstractMusic(AbstractFile * file);
		
		/**
		* @brief Destructor.
		**/
		virtual ~AbstractMusic();

		/**
		* @brief Plays the music.
		* @param loop Amount of loops. Default is forever.
		**/
		virtual void play(int loop = -1) = 0;

		/**
		* @brief Pauses music playback.
		**/
		virtual void pause() = 0;

		/**
		* @brief Resumes music playback.
		**/
		virtual void resume() = 0;

		/**
		* @brief Stops music playback.
		**/
		virtual void stop() = 0;

		/**
		* @brief Rewinds the music.
		**/
		virtual void rewind() = 0;

		
	}; // AbstractMusic
	
	typedef boost::shared_ptr<AbstractMusic> pAbstractMusic;
	
} // love

#endif
