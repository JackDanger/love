/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright © 2006-2008 LOVE Development Team
*/

#ifndef LOVE_SDL_MIXER_AUDIO_H 
#define LOVE_SDL_MIXER_AUDIO_H 

// LOVE
#include "Audio.h"

namespace love
{

	/**
	* Audio device implemented using SDL_mixer.
	* 
	* @author Anders Ruud
	* @date 2007-08-19
	**/
	class SDLMixerAudio : public Audio
	{
	private:
	
	public:
		
		/**
		* @brief Destructor.
		**/
		virtual ~SDLMixerAudio();

		// From Device
		bool init(int argc, char* argv[]);
		void quit();

		// From Audio
		pSound getSound(pFile file) const;
		pMusic getMusic(pFile file) const;
		bool isPlaying() const;
		bool isPaused() const;
		void pause() const;
		void stop() const;
		void resume() const;
		void setVolume(float volume) const;
		void play(pSound sound, int loop = 1, int channel = -1) const;
		void play(pMusic music, int loop = 1) const;
		
	}; // SDLMixerAudio
	
} // love

#endif // LOVE_SDL_MIXER_AUDIO_H
