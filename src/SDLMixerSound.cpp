#include "SDLMixerSound.h"
#include "AbstractFile.h"
#include "love.h"

namespace love
{
	
	SDLMixerSound::SDLMixerSound(AbstractFile * file) : AbstractSound(file)
	{
	}
	
	SDLMixerSound::~SDLMixerSound()
	{
		unload();
	}

	void SDLMixerSound::play(int loop)
	{
		Mix_PlayChannel(-1, sound, loop);
	}

	void SDLMixerSound::setVolume(float volume)
	{
		Mix_VolumeChunk(sound, (int)(MIX_MAX_VOLUME*volume));
	}

	int SDLMixerSound::load()
	{
		if(!file->load())
			return LOVE_ERROR;

		// Create SDL_RWops
		SDL_RWops * rw = SDL_RWFromMem(file->getData(), file->getSize());

		if( !(sound = Mix_LoadWAV_RW(rw, 1)) )
		{
			printf("Unable to create sound: %s\n", Mix_GetError());
			return LOVE_ERROR;
		}

		return LOVE_OK;
	}

	void SDLMixerSound::unload()
	{
		file->unload();
	}
	
} // love
