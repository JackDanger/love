#include "Music.h"

namespace love_sdlmixer
{
	Music::Music(love::pFile file) : Resource(file), music(0)
	{
	}
	
	Music::~Music()
	{
		unload();
	}

	void Music::play(int loop)
	{
		Mix_PlayMusic(music, loop - 1);
	}

	bool Music::load()
	{
		if(!file->load())
			return false;

		// Create SDL_RWops
		SDL_RWops * rw = SDL_RWFromMem(file->getData(), file->getSize());

		if( !(music = Mix_LoadMUS_RW(rw)))
		{
			//love_mod::runtime_error("Music: Unable to open music file " + file->getFilename() + ":" + std::string( Mix_GetError() ));
			return false;
		}

		Mix_VolumeMusic(SDL_MIX_MAXVOLUME);

		return true;
	}

	void Music::unload()
	{
		// If this is 0, then it was never loaded.
		if(music != 0)
		{
			Mix_FreeMusic(music);
			music = 0;
		}

		// Unload the file.
		file->unload();
	}
	
} // love_sdlmixer
