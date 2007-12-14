#ifndef LOVE_SOUND_H
#define LOVE_SOUND_H

#include <SDL_mixer.h>
#include "Loadable.h"
#include "Updateable.h"
#include "Object.h"
#include "Resource.h"

namespace love
{
	
	class AbstractFile;

	/**
	* @class Sound
	* @version 1.0
	* @since 1.0
	* @author Michael Enger
	* @date 2007-08-1
	* @brief A class to contain all the information about a sound file, for playback later.
	**/
	class Sound : public Object, public Loadable, public Resource
	{
	private:

		Mix_Chunk * sound;
		std::string filename;
		int channel;
		int volume;

	public:
		/**
		 * @param filename Path to a sound file.
		 * @brief Initializes the variables.
		 **/
		Sound(AbstractFile * file);

		/**
		 * @brief Does nothing.
		 **/
		~Sound();

		/**
		 * @return The volume the sound will be played at (0-128)
		 * @brief Returns the volume.
		 **/
		int getVolume();

		/**
		 * @brief Plays the sound on any available channel and (if successful) sets the volume of that channel.
		 **/
		void play();

		/**
		 * @param volume A new volume value.
		 * @breif Sets the volume the sound file will be played at, cannot be lower than 0 or higher than 128.
		 **/
		void setVolume(int volume);

		/**
		 * @brief Loads the sound file from memory.
		 **/
		int load();

		/**
		 * @brief Does nothing.
		 **/
		void unload();

		// Static methods
		static void stopAll();
	};

	typedef boost::shared_ptr<Sound> pSound;
}

#endif
