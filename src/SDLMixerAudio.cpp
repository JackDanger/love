#include "SDLMixerAudio.h"
#include "SDL_mixer.h"
#include "love.h"
#include "Core.h"

#include "SDLMixerSound.h"
#include "SDLMixerMusic.h"

namespace love
{
	
	SDLMixerAudio::SDLMixerAudio()
	{
	}
	
	SDLMixerAudio::~SDLMixerAudio()
	{
		// Close the audio device.
		Mix_CloseAudio();
	}

	int SDLMixerAudio::init()
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
			core->error("SDLMixerAudio: Unable to open audio!");
			//printf("Unable to open audio!\n");
			return LOVE_ERROR;
		}

		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		bits=audio_format&0xFF;
		core->printf("Opened audio at %d Hz %d bit %s, %d bytes audio buffer\n", audio_rate,
				bits, audio_channels>1?"stereo":"mono", audio_buffers );

		return LOVE_OK;
	}

	pAbstractSound SDLMixerAudio::getSound(pAbstractFile file) const
	{
		pAbstractSound tmp(new SDLMixerSound(file));
		return tmp;
	}
	
	pAbstractMusic SDLMixerAudio::getMusic(pAbstractFile file) const
	{
		pAbstractMusic tmp(new SDLMixerMusic(file));
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

	void SDLMixerAudio::play(pAbstractSound sound, int loop, int channel) const
	{
		sound->play(loop);
	}

	void SDLMixerAudio::play(pAbstractMusic music, int loop) const
	{
		music->play(loop);
	}
	
} // love
