#include "SDLMixerMusic.h"

namespace love
{
	
	SDLMixerMusic::SDLMixerMusic(pFile file) : Music(file)
	{
	}
	
	SDLMixerMusic::~SDLMixerMusic()
	{
		unload();
	}

	void SDLMixerMusic::play(int loop)
	{
		Mix_PlayMusic(music, loop - 1);
	}

	bool SDLMixerMusic::load()
	{
		if(!file->load())
			return false;

		// Create SDL_RWops
		SDL_RWops * rw = SDL_RWFromMem(file->getData(), file->getSize());

		if( !(music = Mix_LoadMUS_RW(rw)))
		{
			printf("SDLMixerMusic: Unable to open music file '%s': %s\n", file->getFilename().c_str(), Mix_GetError());
			return false;
		}

		Mix_VolumeMusic(SDL_MIX_MAXVOLUME);

		return true;
	}

	void SDLMixerMusic::unload()
	{
		Mix_FreeMusic(music);
		music = 0;
		file->unload();
	}

	
} // love
