/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
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
#include "../../config.h"
#include "../../constants.h"
#include "../../luax.h"
#include "../../sound/SoundData.h"
#include "Channel.h"
#include "Sound.h"
#include "Music.h"

namespace love
{
namespace audio
{
namespace openal
{
	class Audio
	{
	private:
		static Audio * _instance;

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

	protected:
		Audio();
	public:

		static Audio * __getinstance();
		static int __advertise(lua_State * L);
		static int __open(lua_State * L);
		static int __garbagecollect(lua_State * L);

		int getNumChannels();

		Sound * newSound(love::sound::SoundData * data);
		Music * newMusic(love::sound::SoundData * data);
		Channel * newChannel();

		void play(Audible * audible, Channel * channel);
		void play(Audible * audible);

		void stop(Channel * channel);
		void pause(Channel * channel);
		void rewind(Channel * channel);

		void setVolume(float volume);
		float getVolume();

	}; // Audio

} // openal
} // audio
} // love

#endif // LOVE_AUDIO_OPENAL_AUDIO_H