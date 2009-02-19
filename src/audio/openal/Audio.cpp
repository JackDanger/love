/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
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
* 
* -- LOVE Development Team, http://love2d.org
**/

#include "Audio.h"

// LOVE
#include "wrap_Audio.h"

#define MUTEX_ASSERT(fn, sval) \
	if(fn != sval) \
	{ \
		std::cout << "Mutex lock/unlock failure. " << SDL_GetError() << std::endl; \
		exit(-1); \
	} \

namespace love
{
namespace audio
{
namespace openal
{
	Audio * Audio::_instance = 0;

	Audio::Audio()
		: quit_channel_updater(false), channels_mutex(0), channel_update_thread(0)
	{
	}

	Audio * Audio::__getinstance()
	{
		if(_instance == 0)
			_instance = new Audio();
		return _instance;
	}

	int Audio::__advertise(lua_State * L)
	{
		love::luax_register_info(L,
			"openal",
			"audio",
			"OpenAL Audio Module",
			"LOVE Development Team",
			&__open);
		return 0;
	}

	int Audio::__open(lua_State * L)
	{
		// Open stuff here.
		wrap_Audio_open(L);
		luax_register_gc(L, "openal", &__garbagecollect);
		return 0;
	}

	int Audio::__garbagecollect(lua_State * L)
	{
		Audio * m = Audio::__getinstance();
		if(m != 0)
			delete m;
		return 0;
	}

	bool Audio::channel_playing(Channel * c)
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

	void Audio::channel_insert(Channel * c)
	{
		c->retain();

		// Need mutex lock.
		MUTEX_ASSERT(SDL_mutexP(channels_mutex), 0);
		std::cout << " --> Channel inserted." << std::endl;
		playing_channels.push_back(c);
		MUTEX_ASSERT(SDL_mutexV(channels_mutex), 0);

	}

	int Audio::channel_updater(void * unused)
	{
		while(!Audio::__getinstance()->quit_channel_updater)
		{
			MUTEX_ASSERT(SDL_mutexP(Audio::__getinstance()->channels_mutex), 0);
			
			std::list<Channel *>::iterator p = Audio::__getinstance()->playing_channels.begin();

			// Update channels and remove completed ones.
			while(p != Audio::__getinstance()->playing_channels.end())
			{
				if((*p)->isDone())
				{
					(*p)->release();
					Audio::__getinstance()->playing_channels.erase(p++);
					std::cout << " <-- Channel removed." << std::endl;
				}
				else
				{
					(*p)->update();
					p++;
				}
			}
		

			MUTEX_ASSERT(SDL_mutexV(Audio::__getinstance()->channels_mutex), 0);
			SDL_Delay(10);
		}

		return 0;
	}

	int Audio::getNumChannels()
	{
		return playing_channels.size();
	}

	Sound * Audio::newSound(love::sound::SoundData * data)
	{
		return new Sound(data);
	}

	Music * Audio::newMusic(love::sound::SoundData * data)
	{
		return new Music(data);
	}

	Channel * Audio::newChannel()
	{
		return new Channel();
	}

	void Audio::play(Audible * audible, Channel * channel)
	{
		// Set the audible, overwrite if necessary.
		channel->setAudible(audible);
		
		// Play the channel.
		channel->play();

		// Insert only if not already playing.	
		if(!channel_playing(channel))
			channel_insert(channel);
	}

	void Audio::play(Audible * audible)
	{
		Channel * c = new Channel();
		play(audible, c);
		c->release();
	}

	void Audio::stop(Channel * channel)
	{
		channel->stop();
	}

	void Audio::pause(Channel * channel)
	{
		channel->pause();
	}

	void Audio::rewind(Channel * channel)
	{
		channel->rewind();
	}

	void Audio::setVolume(float volume)
	{
		alListenerf(AL_GAIN, volume);
	}

	float Audio::getVolume()
	{
		ALfloat volume;
		alGetListenerf(AL_GAIN, &volume);
		return volume;
	}

} // openal
} // audio
} // love
