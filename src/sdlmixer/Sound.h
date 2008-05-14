/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SDLMIXER_SOUND_H 
#define LOVE_SDLMIXER_SOUND_H 

// LOVE
#include <love/Resource.h>

// SDL_mixer
#include <SDL_mixer.h>

namespace love_sdlmixer
{
	/**
	* @author Michael Enger
	* @date 2007-08-19
	**/
	class Sound : public love::Resource
	{
	private:
	
		// The chunk of data used by SDL_mixer.
		Mix_Chunk * sound;

	public:
	
		/**
		* Creates a new sound from the given file.
		**/
		Sound(love::pFile file);
		
		virtual ~Sound();

		/**
		* Play the Sound.
		* @param loop The number of loops. Default 1 (play once), 0 is forever.
		**/
		void play(int loop = 1);

		/**
		* Sets the volume of the sound.
		* @param volume The volume from 0.0 - 1.0.
		**/
		void setVolume(float volume);

		// From resource
		bool load();
		void unload();
		
	}; // Sound

	typedef boost::shared_ptr<Sound> pSound;
	
} // love_sdlmixer

#endif // LOVE_SDLMIXER_SOUND_H
