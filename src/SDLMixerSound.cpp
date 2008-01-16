#include "SDLMixerSound.h"


namespace love
{
	
	SDLMixerSound::SDLMixerSound(pFile file) : Sound(file)
	{
	}
	
	SDLMixerSound::~SDLMixerSound()
	{
		unload();
	}

	void SDLMixerSound::play(int loop)
	{
		Mix_PlayChannel(-1, sound, loop - 1);
	}

	void SDLMixerSound::setVolume(float volume)
	{
		Mix_VolumeChunk(sound, (int)(MIX_MAX_VOLUME*volume));
	}

	bool SDLMixerSound::load()
	{
		if(!file->load())
			return false;

		// Create SDL_RWops
		SDL_RWops * rw = SDL_RWFromMem(file->getData(), file->getSize());

		if( !(sound = Mix_LoadWAV_RW(rw, 1)) )
		{
			printf("Unable to create sound: %s\n", Mix_GetError());
			return false;
		}

		return true;
	}

	void SDLMixerSound::unload()
	{
		Mix_FreeChunk(sound);
		sound = 0;
		file->unload();
	}
	
} // love
