/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SDLMIXERSOUND_H 
#define LOVE_SDLMIXERSOUND_H 

// LOVE
#include "Sound.h"

// STL

// SDL_mixer
#include <SDL_mixer.h>

namespace love
{

	/**
	* 
	* @author Michael Enger
	* @date 2007-08-19
	**/
	class SDLMixerSound : public Sound
	{
	private:
	
		// The chunk of data used by SDL_mixer.
		Mix_Chunk * sound;

	public:
	
		/**
		* Creates a new sound from the given file.
		**/
		SDLMixerSound(pFile file);
		
		virtual ~SDLMixerSound();

		// From Sound.
		void play(int loop = 1);
		void setVolume(float volume);

		// From resource
		bool load();
		void unload();
		
	}; // SDLMixerSound
	
} // love

#endif // LOVE_SDLMIXERSOUND_H
