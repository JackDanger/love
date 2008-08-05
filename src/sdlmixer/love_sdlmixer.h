/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* An interface for loading and playback of music
* and sound files by means of SDL_mixer. Very 
* limited at the moment.
* 
* @author Michael Enger
* @author Anders Ruud
* @date 2008-03-16
*/
#ifndef LOVE_MOD_SDLMIXER_H
#define LOVE_MOD_SDLMIXER_H

// LOVE
#include <love/mod.h>
#include <love/File.h>

// Module files.
#include "Sound.h"
#include "Music.h"

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_sdlmixer
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

	/**
	* Gets a Sound object.
	**/
	pSound newSound(const char * filename);

	/**
	* Gets a Music object.
	**/
	pMusic newMusic(const char * filename);

	/**
	* Checks if audio is playing or not.
	**/
	bool isPlaying();

	/**
	* Checks if audio is paused or not.
	**/
	bool isPaused();

	/**
	* Pauses all audio. (Sound and Music).
	**/
	void pause();

	/**
	* Stops all audio. (Sound and Music).
	**/
	void stop();

	/**
	* Resumes all paused audio. (Sound and Music).
	**/
	void resume();

	/**
	* Sets the number of channels for sound effect mixing.
	* @param channels The amount of channels.
	**/
	void setChannels(int channels);

	/**
	* Sets the audio mode.
	* @param frequency The frequency (in Hz, could be AUDIO_QUALITY_LOW, AUDIO_QUALITY_MEDIUM, AUDIO_QUALITY_HIGH or custom value).
	* @param mode The audio mode (AUDIO_MODE_MONO, AUDIO_MODE_STEREO).
	* @param buffersize The size of the buffer (bytes per output per sample).
	**/
	void setMode(int frequency, int mode, int buffersize);

	/**
	* Sets global volume.
	* @param volume The volume from 0.0 - 1.0.
	**/
	void setVolume(float volume);

	/**
	* Plays a Sound file. 
	* @param loop The number of times to play. (0 = forever)
	* @param channel The channel to play the sound on.
	**/
	void play(const pSound & sound, int loop = 1, int channel = -1);

	/**
	* Plays a Music file. 
	* @param loop The number of times to play. (0 = forever)
	**/
	void play(const pMusic & music, int loop = 1);

} // love_sdlmixer

#endif // LOVE_MOD_SDLMIXER_H
