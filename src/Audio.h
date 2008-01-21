/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_AUDIO_H 
#define LOVE_AUDIO_H 

// LOVE
#include "Device.h"
#include "Sound.h"
#include "Music.h"
#include "File.h"

// STL

namespace love
{

	/**
	* Abstract Audio device.
	*
	* @author Anders Ruud
	* @date 2007-08-19
	**/
	class Audio : public Device
	{
	private:
	public:
	
		virtual ~Audio();

		/**
		* Gets a sound that is compatible with the current sound device.
		**/
		virtual pSound getSound(pFile file) const = 0;
		
		/**
		* Gets music that is compatible with the current sound device.
		**/
		virtual pMusic getMusic(pFile file) const = 0;

		// Convenience functions. Base source is assumed.
		pSound getSound(const std::string & filename) const;
		pMusic getMusic(const std::string & filename) const;

		/**
		* Checks if audio is playing or not.
		**/
		virtual bool isPlaying() const = 0;

		/**
		* Checks if audio is paused or not.
		**/
		virtual bool isPaused() const = 0;

		/**
		* Pauses all audio. (Sound and Music).
		**/
		virtual void pause() const = 0;

		/**
		* Stops all audio. (Sound and Music).
		**/
		virtual void stop() const = 0;

		/**
		* Resumes all paused audio. (Sound and Music).
		**/
		virtual void resume() const = 0;

		/**
		* Sets global volume.
		* @param volume The volume from 0.0 - 1.0.
		**/
		virtual void setVolume(float volume) const = 0;

		/**
		* Plays a Sound file. 
		* @param loop The number of times to play. (0 = forever)
		* @param channel The channel to play the sound on.
		**/
		virtual void play(pSound sound, int loop = 1, int channel = -1) const = 0;

		/**
		* Plays a Music file. 
		* @param loop The number of times to play. (0 = forever)
		**/
		virtual void play(pMusic music, int loop = 1) const = 0;
		
	}; // Audio

} // love

#endif
