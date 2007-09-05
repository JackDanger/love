/**
* @file SDLMixerMusic.h
* @author Michael Enger
* @date 2007-08-19
* @brief Contains definition for class SDLMixerMusic.
**/

#ifndef LOVE_SDLMIXERMUSIC_H 
#define LOVE_SDLMIXERMUSIC_H 

// LOVE
#include "AbstractMusic.h"

// STL

// Boost
#include <boost/shared_ptr.hpp>

// SDL_mixer
#define USE_RWOPS
#include "SDL_mixer.h"

namespace love
{

	class AbstractFile;

	/**
	* @class SDLMixerMusic
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-08-19
	* @brief 
	**/
	class SDLMixerMusic : public AbstractMusic
	{
	private:
	
		// The music data used by SDL_mixer
		Mix_Music * music;

	public:
	
		/**
		* @brief Constructs an empty SDLMixerMusic.
		**/
		SDLMixerMusic(AbstractFile * file);
		
		/**
		* @brief Destructor.
		**/
		virtual ~SDLMixerMusic();

		/**
		* @brief Plays the music.
		* @param loop Amount of loops. Default is forever.
		**/
		void play(int loop = -1);

		/**
		* @brief Pauses music playback.
		**/
		void pause();

		/**
		* @brief Resumes music playback.
		**/
		void resume();

		/**
		* @brief Stops music playback.
		**/
		void stop();

		/**
		* @brief Rewinds the music.
		**/
		void rewind();

		/**
		* @brief Loads the music.
		* @return LOVE_OK if no errors.
		**/
		int load();

		/**
		* @brief Unloads the music.
		**/
		void unload();

		
	}; // SDLMixerMusic
	
	typedef boost::shared_ptr<SDLMixerMusic> pSDLMixerMusic;
	
} // love

#endif
