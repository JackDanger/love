#include "SDLMixerSoundDevice.h"
#include "SDL_mixer.h"
#include "love.h"
#include "Core.h"

#include "SDLMixerSound.h"
#include "SDLMixerMusic.h"

namespace love
{
	
	SDLMixerSoundDevice::SDLMixerSoundDevice()
	{
	}
	
	SDLMixerSoundDevice::~SDLMixerSoundDevice()
	{
		// Close the audio device.
		Mix_CloseAudio();
	}

	int SDLMixerSoundDevice::init()
	{
		int bits=0;
		int audio_rate,audio_channels,
		// set this to any of 512,1024,2048,4096
		// the higher it is, the more FPS shown and CPU needed
		audio_buffers=1024;
		Uint16 audio_format;

		if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,audio_buffers)<0)
		{
			printf("Unable to open audio!\n");
			return LOVE_ERROR;
		}

		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
		bits=audio_format&0xFF;
		core->printf("Opened audio at %d Hz %d bit %s, %d bytes audio buffer\n", audio_rate,
				bits, audio_channels>1?"stereo":"mono", audio_buffers );

		return LOVE_OK;
	}

	AbstractSound * SDLMixerSoundDevice::getSound(AbstractFile * file) const
	{
		return new SDLMixerSound(file);
	}
	
	AbstractMusic * SDLMixerSoundDevice::getMusic(AbstractFile * file) const
	{
		return new SDLMixerMusic(file);
	}

	bool SDLMixerSoundDevice::isPlaying() const
	{
		// Is sound playing?
		int sound = Mix_Playing(-1);

		// Is music playing?
		int music = Mix_PlayingMusic();

		// If both are 0, none are playing
		return (sound + music != 0);
	}

	bool SDLMixerSoundDevice::isPaused() const
	{
		// Is sound paused?
		int sound = Mix_Paused(-1);

		// Is music paused?
		int music = Mix_PausedMusic();

		// If both are 0, none are playing
		return (sound + music != 0);
	}

	void SDLMixerSoundDevice::pause() const
	{
		// Pause all sound
		Mix_Pause(-1);

		// Pause music
		Mix_PauseMusic();

	}

	void SDLMixerSoundDevice::stop() const
	{
		// Stop all sounds
		Mix_HaltChannel(-1);

		// Stop music
		Mix_HaltMusic();

	}

	void SDLMixerSoundDevice::resume() const
	{
		// Resume sounds
		Mix_Resume(-1);

		// Resume music.
		Mix_ResumeMusic();
	}

	void SDLMixerSoundDevice::setVolume(float volume) const
	{
		// Set the volume for all channels
		Mix_Volume(1,(int)(MIX_MAX_VOLUME * volume));

		// Set the volume for music
		Mix_VolumeMusic((int)(MIX_MAX_VOLUME * volume));
	}
	
} // love
