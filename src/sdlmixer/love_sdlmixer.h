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
	// Functions that should be availble to the love executable
	// must be declared C-style.
	extern "C"
	{
		// Standard module functions.
		bool DECLSPEC module_init(int argc, char ** argv, love::Core * core);
		bool DECLSPEC module_quit();
		bool DECLSPEC module_open(void * vm);
	}

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
