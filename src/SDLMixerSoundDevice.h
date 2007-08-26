/**
* @file SDLMixerSoundDevice.h
* @author Anders Ruud
* @date 2007-08-19
* @brief Contains definition for class SDLMixerSoundDevice.
**/

#ifndef LOVE_SDLMIXERSOUNDDEVICE_H 
#define LOVE_SDLMIXERSOUNDDEVICE_H 

// LOVE
#include "AbstractSoundDevice.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	/**
	* @class SDLMixerSoundDevice
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-19
	* @brief 
	**/
	class SDLMixerSoundDevice : public AbstractSoundDevice
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty SDLMixerSoundDevice.
		**/
		SDLMixerSoundDevice();
		
		/**
		* @brief Destructor.
		**/
		virtual ~SDLMixerSoundDevice();

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
		AbstractSound * getSound(AbstractFile * file) const;
		
		/**
		* @brief Gets music that is compatible with the current sound device.
		* @param file The file to get the music from.
		* @return A pointer to the new music.
		**/
		AbstractMusic * getMusic(AbstractFile * file) const;

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
		
	}; // SDLMixerSoundDevice
	
	typedef boost::shared_ptr<SDLMixerSoundDevice> pSDLMixerSoundDevice;
	
} // love

#endif
