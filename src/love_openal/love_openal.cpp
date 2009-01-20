/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
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

	// Checks whether a channel is already present.
	bool channel_playing(Channel * c)
	{
		std::list<Channel *>::iterator p = playing_channels.begin();

		while(p != playing_channels.end())
		{
			if(*p == c)
				return true;
			p++;
		}
		return false;
	}

	// Prepares a channel for playing.
	void channel_insert(Channel * c)
	{
		c->retain();

		// Need mutex lock.
		MUTEX_ASSERT(SDL_mutexP(channels_mutex), 0);
		std::cout << " --> Channel inserted." << std::endl;
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
					std::cout << " <-- Channel removed." << std::endl;
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

	int getNumChannels()
	{
		return playing_channels.size();
	}

	Sound * newSound(SoundData * data)
	{
		return new Sound(data);
	}

	Music * newMusic(SoundData * data)
	{
		return new Music(data);
	}

	Channel * newChannel()
	{
		return new Channel();
	}

	void play(Audible * audible, Channel * channel)
	{
		// Set the audible, overwrite if necessary.
		channel->setAudible(audible);
		
		// Play the channel.
		channel->play();

		// Insert only if not already playing.	
		if(!channel_playing(channel))
			channel_insert(channel);
	}

	void play(Audible * audible)
	{
		Channel * c = new Channel();
		play(audible, c);
		c->release();
	}

	void stop(Channel * channel)
	{
		channel->stop();
	}

	void pause(Channel * channel)
	{
		channel->pause();
	}

	void rewind(Channel * channel)
	{
		channel->rewind();
	}

	void setVolume(float volume)
	{
		alListenerf(AL_GAIN, volume);
	}

	float getVolume()
	{
		ALfloat volume;
		alGetListenerf(AL_GAIN, &volume);
		return volume;
	}

} // openal
} // love
