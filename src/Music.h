#ifndef LOVE_MUSIC_H
#define LOVE_MUSIC_H


#define USE_RWOPS // Needs to be here for great Ubuntuness.
#include <SDL_mixer.h>

#include "Loadable.h"
#include "Updateable.h"
#include "Resource.h"

namespace love
{
	class Music : public Loadable, public Updateable, public Resource
	{
	private:

		Mix_Music *music;
		std::string filename;

		int volume;
		float pauseCount;
		float location;

		
	public:
		/**
		 * @param filename Path to the music file.
		 * @brief Initializes the variables.
		 **/
		Music(AbstractFile * file);

		/**
		 * @brief Does nothing.
		 **/
		~Music();

		/**
		 * return A pointer to a Mix_Music object.
		 * @brief Returns the current Mix_Music object.
		 **/
		Mix_Music* get();

		/**
		 * @return Whether the music is playing.
		 * @brief Returns whether the music is playing.
		 **/
		bool isPlaying();
		
		bool isPaused();

		/**
		 * @return The current volume level (0-128)
		 * @brief Returns the volume the music will be played at.
		 **/
		int getVolume();


		/**
		 * @return The location of the music (in seconds).
		 * @brief Returns the location of the music.
		 **/
		float getLocation();

		/**
		 * @param playing Whether the music is playing.
		 * @brief Sets whether the music is playing.
		 **/
		void play(int loop = -1);

		void pause();
		void resume();

		void stop();
		void rewind();
		void seek(float seconds);

		/**
		 * @param volume The new volume level (0-128)
		 * @brief Sets the volume the music will be played at.
		 **/
		void setVolume(int volume);

		/**
		 * @param location The new location for the music (in seconds).
		 * @brief Sets the location.
		 **/
		void setLocation(float location);

		/**
		 * @brief Loads the music file.
		 **/
		int load();

		/**
		 * @brief Frees the music object.
		 **/
		void unload();

		/**
		 * @brief Updates the location of the music. Should only be called if this music is playing.
		 **/
		void update(float dt);

		// Static methods
		static bool mixIsPlaying();
		static bool mixIsPaused();
		static void mixPause();
		static void mixResume();
		static void mixStop();
	};

	typedef boost::shared_ptr<Music> pMusic;
}

#endif
