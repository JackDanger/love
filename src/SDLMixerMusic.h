/**
* @file SDLMixerMusic.h
* @author Michael Enger
* @date 2007-08-19
* @brief Contains definition for class SDLMixerMusic.
**/

#ifndef LOVE_SDLMIXERMUSIC_H 
#define LOVE_SDLMIXERMUSIC_H 

// LOVE
#include "Music.h"

// SDL_mixer
#define USE_RWOPS
#include <SDL_mixer.h>

namespace love
{

	/**
	* 
	* @author Michael Enger
	* @date 2007-08-19
	**/
	class SDLMixerMusic : public Music
	{
	private:
	
		// The music data used by SDL_mixer
		_Mix_Music * music;

	public:
	
		/**
		* Creates new Music from the given file.
		**/
		SDLMixerMusic(pFile file);
		
		virtual ~SDLMixerMusic();

		// From Music
		void play(int loop = 1);

		// From Resource.
		bool load();
		void unload();

		
	}; // SDLMixerMusic
	
} // love

#endif // LOVE_SDLMIXERMUSIC_H
