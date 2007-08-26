#include "Music.h"
#include "love.h"
#include "AbstractFile.h"

namespace love
{

	Music::Music(AbstractFile * file) : Resource(file)
	{
		this->filename = "";
		music = 0;
		pauseCount = 0;
		location = 0;
		volume = MIX_MAX_VOLUME;
	}

	Music::~Music()
	{}

	Mix_Music* Music::get()
	{
		return music;
	}

	bool Music::isPlaying()
	{
		return (Mix_PlayingMusic() != 0);
	}

	bool Music::isPaused()
	{
		return (Mix_PausedMusic() != 0);
	}

	int Music::getVolume()
	{
		return volume;
	}

	float Music::getLocation()
	{
		return location;
	}

	void Music::play(int loop)
	{
		Mix_PlayMusic(music, loop);
	}

	void Music::resume()
	{
		Mix_ResumeMusic();
	}


	void Music::pause()
	{
		Mix_PauseMusic();
	}

	void Music::stop()
	{
		Mix_HaltMusic();
	}

	void Music::rewind()
	{
		Mix_RewindMusic();
	}


	void Music::seek(float seconds)
	{
		if(Mix_SetMusicPosition(seconds) == -1)
			printf("Unable to set music position: %s\n", Mix_GetError());
	}
	
	void Music::setVolume(int volume)
	{
		this->volume = volume;
		if(this->volume > SDL_MIX_MAXVOLUME)
			this->volume = SDL_MIX_MAXVOLUME;
		else if(this->volume < 0)
			this->volume = 0;

		Mix_VolumeMusic(this->volume);
	}

	void Music::setLocation(float location)
	{
		this->location = location;
		if(this->location < 0)
			this->location = 0;
	}

	int Music::load()
	{


		file->load();

		// Create SDL_RWops
		SDL_RWops * rw = SDL_RWFromMem(file->getData(), file->getSize());

		if( !(music = Mix_LoadMUS_RW(rw) ))
			printf("Unable to open music file '%s': %s\n", file->getFilename().c_str(), Mix_GetError());
		

		Mix_VolumeMusic(SDL_MIX_MAXVOLUME);

		return LOVE_OK;
	}

	void Music::unload()
	{
		Mix_FreeMusic(music);

		file->unload();
	}

	void Music::update(float dt)
	{
		location += dt;
	}


	// Static methods
	bool Music::mixIsPlaying() 
	{
		return (Mix_PlayingMusic() != 0);
	}

	bool Music::mixIsPaused()
	{
		return (Mix_PausedMusic() != 0);
	}

	void Music::mixPause()
	{
	}

	void Music::mixResume()
	{
		Mix_ResumeMusic();
	}

	void Music::mixStop()
	{
		Mix_HaltMusic();
	}

}
