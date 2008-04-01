#include "love_sdlmixer.h"

// SDL and friends.
#include <SDL.h>
#include <SDL_mixer.h>

// From SWIG.
extern "C" {
	int luaopen_mod_sdlmixer(lua_State * L);
}

namespace love_sdlmixer
{
	bool init(love_mod::modconf * conf)
	{
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

		Mix_AllocateChannels(8);
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		bits=audio_format&0xFF;
		Mix_Volume(-1,MIX_MAX_VOLUME);
		Mix_VolumeMusic(MIX_MAX_VOLUME);

		// Standard mod setup.
		love_mod::setConf(conf);
		love_mod::setFilesystem(conf->filesystem);
		love_mod::report_init("love.audio", "SDL_mixer");
		return true;
	}

	bool quit()
	{
		Mix_CloseAudio();

		love_mod::report_init("love.audio", "Shutdown");
		return true;
	}

	bool luaopen(lua_State * s)
	{
		love_mod::setL(s);
		luaopen_mod_sdlmixer(s);
		love_mod::do_string("love.audio = mod_sdlmixer");
		return true;
	}

	pSound newSound(const char * filename)
	{
		love::pFile file = love_mod::newFile( filename );
		pSound sound(new Sound(file));
		sound->load();
		return sound;
	}
	
	pMusic newMusic(const char * filename)
	{
		love::pFile file = love_mod::newFile( filename );
		pMusic music(new Music(file));
		music->load();
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
