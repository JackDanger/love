#include "love_sdlmixer.h"

// LOVE
#include <love/Core.h>
#include <love/Exception.h>

// SDL and friends.
#include <SDL.h>
#include <SDL_mixer.h>

// From SWIG.
extern "C" {
	int luaopen_mod_sdlmixer(lua_State * L);
}

namespace love_sdlmixer
{

	// Required modules + Core.
	love::Core * core = 0;
	love::Filesystem * filesystem = 0;

	bool module_init(int argc, char ** argv, love::Core * core)
	{
		std::cout << "INIT love.audio [" << "SDL_mixer" << "]" << std::endl;

		// Get modules.
		filesystem = core->getFilesystem();

		// Verify all.
		if(!filesystem->verify())
		{
			std::cerr << "Required module filesystem not loaded." << std::endl;
			return false;
		}

		love_sdlmixer::core = core;

		int bits = 0;
		int audio_rate,audio_channels,audio_buffers=1024;
		Uint16 audio_format;

		// High: 44100
		// Medium: 22050
		// Low: 11025

		if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,audio_buffers)<0)
		{
			std::cout << "SDLMixerAudio: Unable to open audio!" << std::endl;
			return false;
		}

		// @todo All this must be configurable.

		Mix_AllocateChannels(8);
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		bits=audio_format&0xFF;
		Mix_Volume(-1,MIX_MAX_VOLUME);
		Mix_VolumeMusic(MIX_MAX_VOLUME);


		// Set function pointers and load module.
		{
			love::Audio * a = core->getAudio();
			a->loaded = true;
		}

		return true;
	}

	bool module_quit()
	{
		Mix_CloseAudio();
		std::cout << "QUIT love.audio [" << "SDL_mixer" << "]" << std::endl;
		return true;
	}

	bool module_open(void * vm)
	{
		lua_State * s = (lua_State *)vm;
		if(s == 0)
			return false;
		luaopen_mod_sdlmixer(s);
		return true;
	}

	pSound newSound(const char * filename)
	{
		love::pFile * file = filesystem->getFile(filename);
		pSound sound(new Sound(*file));
		if(!sound->load())
		{
			std::stringstream err;
			err << "Could not load sound \"" << filename << "\".";
			core->error(err.str().c_str());
		}
		delete file; // sound has copy of the file at this point.
		return sound;
	}
	
	pMusic newMusic(const char * filename)
	{
		love::pFile * file = filesystem->getFile( filename );
		pMusic music(new Music(*file));
		if(!music->load())
		{
			std::stringstream err;
			err << "Could not load music \"" << filename << "\".";
			core->error(err.str().c_str());
		}
		delete file; // music has copy of the file at this point.
		return music;
	}

	bool isPlaying()
	{
		// Is sound playing?
		int sound = Mix_Playing(-1);

		// Is music playing?
		int music = Mix_PlayingMusic();

		// If both are 0, none are playing
		return (sound + music != 0);
	}

	bool isPaused()
	{
		// Is sound paused?
		int sound = Mix_Paused(-1);

		// Is music paused?
		int music = Mix_PausedMusic();

		// If both are 0, none are playing
		return (sound + music != 0);
	}

	void pause()
	{
		// Pause all sound
		Mix_Pause(-1);

		// Pause music
		Mix_PauseMusic();
	}

	void stop()
	{
		// Stop all sounds
		Mix_HaltChannel(-1);

		// Stop music
		Mix_HaltMusic();
	}

	void resume()
	{
		// Resume sounds
		Mix_Resume(-1);

		// Resume music.
		Mix_ResumeMusic();
	}

	void setVolume(float volume)
	{
		// Set the volume for all channels
		Mix_Volume(-1,(int)(MIX_MAX_VOLUME * volume));

		// Set the volume for music
		Mix_VolumeMusic((int)(MIX_MAX_VOLUME * volume));
	}

	void play(const pSound & sound, int loop, int channel)
	{
		sound->play(loop);
	}

	void play(const pMusic & music, int loop)
	{
		music->play(loop);
	}

} // love_sdlmixer
