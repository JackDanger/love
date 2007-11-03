#include "Sound.h"
#include "love.h"
#include "AbstractFile.h"

namespace love
{

	Sound::Sound(AbstractFile * file) : Resource(file), sound(0), filename(""), channel(-1), volume(MIX_MAX_VOLUME)
	{

	}

	Sound::~Sound()
	{
	}

	int Sound::getVolume()
	{
		return this->volume;
	}

	void Sound::play()
	{
		channel = Mix_PlayChannel(-1, sound, 0);
		if(channel == -1)
			printf("Error playing sound: %s\n", Mix_GetError());
		else
			Mix_Volume(channel, volume);
	}

	void Sound::setVolume(int volume)
	{
		this->volume = volume;
		if(this->volume < 0)
			this->volume = 0;
		else if(this->volume > MIX_MAX_VOLUME)
			this->volume = MIX_MAX_VOLUME;
	}

	int Sound::load()
	{

		file->load();

		// Create SDL_RWops
		SDL_RWops * rw = SDL_RWFromMem(file->getData(), file->getSize());

		if( !(sound = Mix_LoadWAV_RW(rw, 1)) )
			printf("Unable to create sound: %s\n", Mix_GetError());

		return LOVE_OK;
	}

	void Sound::unload()
	{
		file->unload();
	}

	void Sound::stopAll()
	{
		
	}
}
