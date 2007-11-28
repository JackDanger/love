/**
* @file SDLMixerSound.h
* @author Michael Enger
* @date 2007-08-19
* @brief Contains definition for class SDLMixerSound.
**/

#ifndef LOVE_SDLMIXERSOUND_H 
#define LOVE_SDLMIXERSOUND_H 

// LOVE
#include "AbstractSound.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

// SDL_mixer
#include <SDL_mixer.h>

namespace love
{

	/**
	* @class SDLMixerSound
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-08-19
	* @brief 
	**/
	class SDLMixerSound : public AbstractSound
	{
	private:
	
		// The chunk of data used by SDL_mixer.
		Mix_Chunk * sound;

	public:
	
		/**
		* @brief Constructs an empty SDLMixerSound.
		**/
		SDLMixerSound(pAbstractFile file);
		
		/**
		* @brief Destructor.
		**/
		virtual ~SDLMixerSound();

		/**
		* @brief Plays the sound.
		* @param loop The number of loops. Default is 0, -1 for forever.
		**/
		virtual void play(int loop = 0);

		/**
		* @brief Sets the volume for this sound.
		* @param volume The volume from 0.0 - 1.0.
		**/
		virtual void setVolume(float volume);

		/**
		 * @brief Loads the sound file.
		 **/
		int load();

		/**
		 * @brief Unloads the sound file.
		 **/
		void unload();
		
	}; // SDLMixerSound
	
	typedef boost::shared_ptr<SDLMixerSound> pSDLMixerSound;
	
} // love

#endif
