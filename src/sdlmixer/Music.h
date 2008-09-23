/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SDLMIXER_MUSIC_H
#define LOVE_SDLMIXER_MUSIC_H 

// LOVE
#include <love/Resource.h>

// SDL_mixer
#define USE_RWOPS
#include <SDL_mixer.h>

namespace love_sdlmixer
{
	/**
	* @author Michael Enger
	* @date 2007-08-19
	**/
	class Music : public love::Resource
	{
	private:
	
		// The music data used by SDL_mixer
		_Mix_Music * music;

	public:
	
		/**
		* Creates new Music from the given file.
		**/
		Music(love::pFile file);
		
		virtual ~Music();

		/**
		* Plays Music. 
		* @param loop The number of loops. Default 1 (play once), 0 is forever.
		**/
		void play(int loop = 1);

		// From Resource.
		bool load();
		void unload();
		
	}; // Music

	typedef boost::shared_ptr<Music> pMusic;
	
} // love_sdlmixer

#endif // LOVE_SDLMIXER_MUSIC_H
