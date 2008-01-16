#include "SDLMixerAudio.h"

// LOVE
#include "SDLMixerSound.h"
#include "SDLMixerMusic.h"

#include <SDL_mixer.h>

namespace love
{
	
	SDLMixerAudio::~SDLMixerAudio()
	{
		quit();
	}

	bool SDLMixerAudio::init(int argc, char* argv[])
	{
		int bits=0;
		int audio_rate,audio_channels,
		// set this to any of 512,1024,2048,4096
		// the higher it is, the more FPS shown and CPU needed
		audio_buffers=1024;
		Uint16 audio_format;

		// High: 44100
		// Medium: 22050
		// Low: 11025

		if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,audio_buffers)<0)
		{
			printf("SDLMixerAudio: Unable to open audio!");
			//printf("Unable to open audio!\n");
			return false;
		}

		Mix_AllocateChannels(32);

		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		bits=audio_format&0xFF;
		//printf("[INIT] Audio (SDL_mixer)\n - Opened audio at %d Hz %d bit %s\n - %d bytes audio buffer\n", audio_rate,
		//		bits, audio_channels>1?"stereo":"mono", audio_buffers );

		Mix_Volume(-1,MIX_MAX_VOLUME);
		Mix_VolumeMusic(MIX_MAX_VOLUME);

		return true;
	}

	void SDLMixerAudio::quit()
	{
		// Close the audio device.
		Mix_CloseAudio();

		//printf("[QUIT] Audio\n");
	}

	pSound SDLMixerAudio::getSound(pFile file) const
	{
		pSound tmp(new SDLMixerSound(file));
		return tmp;
	}
	
	pMusic SDLMixerAudio::getMusic(pFile file) const
	{
		pMusic tmp(new SDLMixerMusic(file));
		return tmp;
	}

	bool SDLMixerAudio::isPlaying() const
	{
		// Is sound playing?
		int sound = Mix_Playing(-1);

		// Is music playing?
		int music = Mix_PlayingMusic();

		// If both are 0, none are playing
		return (sound + music != 0);
	}

	bool SDLMixerAudio::isPaused() const
	{
		// Is sound paused?
		int sound = Mix_Paused(-1);

		// Is music paused?
		int music = Mix_PausedMusic();

		// If both are 0, none are playing
		return (sound + music != 0);
	}

	void SDLMixerAudio::pause() const
	{
		// Pause all sound
		Mix_Pause(-1);

		// Pause music
		Mix_PauseMusic();

	}

	void SDLMixerAudio::stop() const
	{
		// Stop all sounds
		Mix_HaltChannel(-1);

		// Stop music
		Mix_HaltMusic();

	}

	void SDLMixerAudio::resume() const
	{
		// Resume sounds
		Mix_Resume(-1);

		// Resume music.
		Mix_ResumeMusic();
	}

	void SDLMixerAudio::setVolume(float volume) const
	{
		// Set the volume for all channels
		Mix_Volume(1,(int)(MIX_MAX_VOLUME * volume));

		// Set the volume for music
		Mix_VolumeMusic((int)(MIX_MAX_VOLUME * volume));
	}

	void SDLMixerAudio::play(pSound sound, int loop, int channel) const
	{
		sound->play(loop);
	}

	void SDLMixerAudio::play(pMusic music, int loop) const
	{
		music->play(loop);
	}
	
} // love
