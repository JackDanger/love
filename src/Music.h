/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_MUSIC_H 
#define LOVE_MUSIC_H 

// LOVE
#include "Resource.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* Abstract Music class.
	*
	* @author Anders Ruud
	* @date 2007-08-19
	**/
	class Music : public Resource
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty Music.
		**/
		Music(pFile file);
	
		virtual ~Music();

		/**
		* Plays Music. 
		* @param loop The number of loops. Default 1 (play once), 0 is forever.
		**/
		virtual void play(int loop = 1) = 0;
		
	}; // Music
	
	typedef boost::shared_ptr<Music> pMusic;
	
} // love

#endif // LOVE_MUSIC_H
