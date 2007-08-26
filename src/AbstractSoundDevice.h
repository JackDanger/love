/**
* @file AbstractSoundDevice.h
* @author Anders Ruud
* @date 2007-08-19
* @brief Contains definition for class AbstractSoundDevice.
**/

#ifndef LOVE_ABSTRACTSOUNDDEVICE_H 
#define LOVE_ABSTRACTSOUNDDEVICE_H 

// LOVE
#include "AbstractDevice.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

namespace love
{

	class AbstractSound;
	class AbstractMusic;
	class AbstractFile;

	/**
	* @class AbstractSoundDevice
	* @version 1.0
	* @since 1.0
	* @author Anders Ruud
	* @date 2007-08-19
	* @brief
	**/
	class AbstractSoundDevice : public AbstractDevice
	{
	private:
	
	public:
	
		/**
		* @brief Constructs an empty AbstractSoundDevice.
		**/
		AbstractSoundDevice();
		
		/**
		* @brief Destructor.
		**/
		virtual ~AbstractSoundDevice();

		/**
		* @brief Gets a sound that is compatible with the current sound device.
		* @param file The file to get the sound from.
		* @return A pointer to a new sound.
		**/
		virtual AbstractSound * getSound(AbstractFile * file) const = 0;
		
		/**
		* @brief Gets music that is compatible with the current sound device.
		* @param file The file to get the music from.
		* @return A pointer to the new music.
		**/
		virtual AbstractMusic * getMusic(AbstractFile * file) const = 0;

		/**
		* @brief Checks if audio is playing or not.
		* @return True if audio is playing, false otherwise.
		**/
		virtual bool isPlaying() const = 0;

		/**
		* @brief Checks if audio is paused or not.
		* @resume True if audio is paused, false otherwise.
		**/
		virtual bool isPaused() const = 0;

		/**
		* @brief Pauses all audio. (Sound and Music).
		**/
		virtual void pause() const = 0;

		/**
		* @brief Stops all audio. (Sound and Music).
		**/
		virtual void stop() const = 0;

		/**
		* @brief Resumes all paused audio. (Sound and Music).
		**/
		virtual void resume() const = 0;

		/**
		* @brief Sets global volume.
		* @param volume The volume from 0.0 - 1.0.
		**/
		virtual void setVolume(float volume) const = 0;

		
	}; // AbstractSoundDevice
	
	typedef boost::shared_ptr<AbstractSoundDevice> pAbstractSoundDevice;
	
} // love

#endif
