/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-10-16
**/

#include "love_openal.h"

// STD
#include <list>
#include <iostream>
#include <cmath>

// LOVE
#include "../liblove/version.h"
#include "../liblove/constants.h"

// SDL
#include <SDL.h>

// OpenAL
#include <alut.h>

// Include the wrapper code.
#define LOVE_WRAP_NAMESPACE openal
#define LOVE_WRAP_BITS LOVE_OPENAL_BITS
#include "../liblove/audio/waudio.h"

#define MUTEX_ASSERT(fn, sval) \
	if(fn != sval) \
	{ \
		std::cout << "Mutex lock/unlock failure. " << SDL_GetError() << std::endl; \
		exit(-1); \
	} \

namespace love
{
namespace openal
{

	// List of playing channels.
	std::list<Channel *> playing_channels;

	// Set this to true when the channel updater 
	// should quit.
	bool quit_channel_updater = false;

	SDL_mutex * channels_mutex = 0;
	SDL_Thread * channel_update_thread = 0;

	// Prepares a channel for playing.
	void channel_insert(Channel * c)
	{
		c->retain();

		// Need mutex lock.
		MUTEX_ASSERT(SDL_mutexP(channels_mutex), 0);
		playing_channels.push_back(c);
		MUTEX_ASSERT(SDL_mutexV(channels_mutex), 0);

	}

	// This function updates all channel with a certain interval
	// (in a separate thread).
	int channel_updater(void * unused)
	{
		while(!quit_channel_updater)
		{
			MUTEX_ASSERT(SDL_mutexP(channels_mutex), 0);
			
			std::list<Channel *>::iterator p = playing_channels.begin();

			// Update channels and remove completed ones.
			while(p != playing_channels.end())
			{
				if((*p)->isDone())
				{
					(*p)->release();
					playing_channels.erase(p++);
				}
				else
				{
					(*p)->update();
					p++;
				}
			}
		

			MUTEX_ASSERT(SDL_mutexV(channels_mutex), 0);
			SDL_Delay(10);
		}

		return 0;
	}

	int luainfo(lua_State * L)
	{
		luax_register_info(L,
			"openal",
			"audio",
			"OpenAL Audio Module",
			"LOVE Development Team",
			luaopen);

		// Init OpenAL.
		alutInit(0, 0);

		// Create the mutex for the list of channels.
		channels_mutex = SDL_CreateMutex();

		// Init the sound control thread.
		channel_update_thread = SDL_CreateThread(channel_updater, 0);

		return 0;
	}

	int luaopen(lua_State * L)
	{
		luareg(L);
		luax_register_gc(L, "openal", luagc);
		return 0;
	}

	int luagc(lua_State * L)
	{
		if(channel_update_thread != 0)
		{
			quit_channel_updater = true;
			SDL_WaitThread(channel_update_thread, 0);
			channel_update_thread = 0;
			SDL_DestroyMutex(channels_mutex);
		}

		alutExit();
		return 0;
	}

	Sound * newSound(SoundData * data)
	{
		return new Sound(data);
	}

	Music * newMusic(SoundData * data)
	{
		return new Music(data);
	}

	void play(Audible * audible)
	{
		Music * m = (Music*)audible;
		Music * mc = m->clone();
		Channel * c = new Channel(mc);
		mc->release();
		c->play();
		channel_insert(c);
		c->release();
	}

} // openal
} // love
