#include "Sound.h"

namespace love_sdlmixer
{
	Sound::Sound(love::pFile file) : love::Resource(file), sound(0)
	{
	}
	
	Sound::~Sound()
	{
		unload();
	}

	void Sound::play(int loop)
	{
		Mix_PlayChannel(-1, sound, loop - 1);
	}

	void Sound::setVolume(float volume)
	{
		Mix_VolumeChunk(sound, (int)(MIX_MAX_VOLUME*volume));
	}

	bool Sound::load()
	{
		if(!file->load())
			return false;

		// Create SDL_RWops
		SDL_RWops * rw = SDL_RWFromMem(file->getData(), file->getSize());

		if( !(sound = Mix_LoadWAV_RW(rw, 1)) )
		{
			//love_mod::runtime_error("Unable to create sound " + std::string(Mix_GetError()));
			return false;
		}

		return true;
	}

	void Sound::unload()
	{
		if(sound != 0)
		{
			Mix_FreeChunk(sound);
			sound = 0;
		}

		// Unload the file.
		file->unload();
	}
	
} // love_sdlmixer
