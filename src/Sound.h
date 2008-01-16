/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SOUND_H 
#define LOVE_SOUND_H 

// LOVE
#include "Resource.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* Abstract Sound class.
	* 
	* @author Anders Ruud
	* @date 2007-08-19
	**/
	class Sound : public Resource
	{
	private:
	public:
	
		/**
		* Constructs a new Sound from the given file.
		**/
		Sound(pFile file);
	
		virtual ~Sound();

		/**
		* Play the Sound.
		* @param loop The number of loops. Default 1 (play once), 0 is forever.
		**/
		virtual void play(int loop = 1) = 0;

		/**
		* Sets the volume of the sound.
		* @param volume The volume from 0.0 - 1.0.
		**/
		virtual void setVolume(float volume) = 0;
		
	}; // Sound

	typedef boost::shared_ptr<Sound> pSound;
	
} // love

#endif // LOVE_SOUND_H
