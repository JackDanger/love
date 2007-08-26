#include "SDLMixerMusic.h"
#include "AbstractFile.h"
#include "love.h"

namespace love
{
	
	SDLMixerMusic::SDLMixerMusic(AbstractFile * file) : AbstractMusic(file)
	{
	}
	
	SDLMixerMusic::~SDLMixerMusic()
	{
		unload();
	}

	void SDLMixerMusic::play(int loop)
	{
		Mix_PlayMusic(music, loop);
	}

	void SDLMixerMusic::pause()
	{
		Mix_PauseMusic();
	}

	void SDLMixerMusic::resume()
	{
		Mix_ResumeMusic();
	}

	void SDLMixerMusic::stop()
	{
		Mix_HaltMusic();
	}

	void SDLMixerMusic::rewind()
	{
		Mix_RewindMusic();
	}

	int SDLMixerMusic::load()
	{
		if(!file->load())
			return LOVE_ERROR;

		// Create SDL_RWops
		SDL_RWops * rw = SDL_RWFromMem(file->getData(), file->getSize());

		if( !(music = Mix_LoadMUS_RW(rw)))
		{
			printf("Unable to open music file '%s': %s\n", file->getFilename().c_str(), Mix_GetError());
			return LOVE_ERROR;
		}
		

		Mix_VolumeMusic(SDL_MIX_MAXVOLUME);

		return LOVE_OK;
	}

	void SDLMixerMusic::unload()
	{
		Mix_FreeMusic(music);
		file->unload();
	}

	
} // love
