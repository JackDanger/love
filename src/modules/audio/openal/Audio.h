/**
* Copyright (c) 2006-2009 LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
**/

#ifndef LOVE_AUDIO_OPENAL_AUDIO_H
#define LOVE_AUDIO_OPENAL_AUDIO_H

// STD
#include <list>
#include <iostream>
#include <cmath>

// SDL
#include <SDL.h>

// OpenAL
#include <alut.h>

// LOVE
#include "../../../common/Module.h"
#include "../../../common/config.h"
#include "../../../common/constants.h"
#include "../../sound/SoundData.h"
#include "Channel.h"
#include "Sound.h"
//#include "Music.h"

namespace love
{
namespace audio
{
namespace openal
{
	/**
	* @class Audio
	* OpenAL audio module. Note that audio modules in general
	* do not decode audio data, they just plays them back.
	**/
	class Audio : public Module
	{
	private:

		// List of playing channels.
		std::list<Channel *> playing_channels;

		// Set this to true when the channel updater 
		// should quit.
		bool quit_channel_updater;

		SDL_mutex * channels_mutex;
		SDL_Thread * channel_update_thread;

		bool channel_playing(Channel * c);
		void channel_insert(Channel * c);
		static int channel_updater(void * unused);

	public:

		Audio();
		~Audio();

		const char * getName() const;

		/**
		* Gets the number of currently playing channels.
		* @return The number of playing channels.
		**/
		int getNumChannels();

		/**
		* Creates a new Sound with the specified SoundData.
		* @param data The SoundData from which to create the sound.
		* @return A new Sound if successful, zero otherwise.
		**/
		Sound * newSound(love::sound::SoundData * data);

		/**
		* Creates a new Music (stream) using the specified SoundData.
		* @param data The SoundData from which to create the music stream.
		**/
		//Music * newMusic(love::sound::SoundData * data);

		/**
		* Creates a new Channel.
		* @returns A new Channel.
		**/
		Channel * newChannel();

		/**
		* Plays one Sound on the specified Channel.
		* @param sound The Sound to play.
		* @param channel The Channel on which to play the Audible.
		**/
		void play(Sound * sound, Channel * channel);

		/**
		* Plays the Sound on a on-the-fly-created Channel.
		* @param sound The Sound to play.
		**/
		void play(Sound * sound);

		/**
		* Stops playback on the specified channel.
		* @param channel The channel on which to stop the playback.
		**/
		void stop(Channel * channel);

		/**
		* Pauses playback on the specified channel.
		* @param channel The channel on which to pause the playback.
		**/
		void pause(Channel * channel);

		/**
		* Rewinds the specified channel. Whatever is playing on this
		* channel gets rewound to the start.
		* @param channel The channel to rewind.
		**/
		void rewind(Channel * channel);

		/**
		* Sets the master volume, where 0.0f is min (off) and 1.0f is max.
		* @param volume The new master volume.
		**/
		void setVolume(float volume);

		/**
		* Gets the master volume.
		* @return The current master volume.
		**/
		float getVolume();

	}; // Audio

} // openal
} // audio
} // love

#endif // LOVE_AUDIO_OPENAL_AUDIO_H