/**
* @file SDLMixerAudio.h
* @author Anders Ruud
* @date 2007-08-19
* @brief Contains definition for class SDLMixerAudio.
**/

#ifndef LOVE_SDLMixerAudio_H 
#define LOVE_SDLMixerAudio_H 

// LOVE
#include "AbstractAudio.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class SDLMixerAudio
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-19
	* @brief 
	**/
	class SDLMixerAudio : public AbstractAudio
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty SDLMixerAudio.
		**/
		SDLMixerAudio();
		
		/**
		* @brief Destructor.
		**/
		virtual ~SDLMixerAudio();

		/**
		* @brief Inits the sound device.
		* @return LOVE_OK if no errors.
		**/
		int init();

		/**
		* @brief Gets a sound that is compatible with the current sound device.
		* @param file The file to get the sound from.
		* @return A pointer to a new sound.
		**/
		pAbstractSound getSound(pAbstractFile file) const;
		
		/**
		* @brief Gets music that is compatible with the current sound device.
		* @param file The file to get the music from.
		* @return A pointer to the new music.
		**/
		pAbstractMusic getMusic(pAbstractFile file) const;

		/**
		* @brief Checks if audio is playing or not.
		* @return True if audio is playing, false otherwise.
		**/
		bool isPlaying() const;

		/**
		* @brief Checks if audio is paused or not.
		* @resume True if audio is paused, false otherwise.
		**/
		bool isPaused() const;

		/**
		* @brief Pauses all audio. (Sound and Music).
		**/
		void pause() const;

		/**
		* @brief Stops all audio. (Sound and Music).
		**/
		void stop() const;

		/**
		* @brief Resumes all paused audio. (Sound and Music).
		**/
		void resume() const;

		/**
		* @brief Sets global volume.
		* @param volume The volume from 0.0 - 1.0.
		**/
		void setVolume(float volume) const;

		void play(pAbstractSound sound, int loop = 0, int channel = -1) const;
		void play(pAbstractMusic music, int loop = 0) const;
		
	}; // SDLMixerAudio
	
	typedef boost::shared_ptr<SDLMixerAudio> pSDLMixerAudio;
	
} // love

#endif
