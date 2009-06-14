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

#include "Audio.h"

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
	Audio::Audio()
		: quit_channel_updater(false)
	{
		alutInit(0, 0);
		channels_mutex = SDL_CreateMutex();
		channel_update_thread = SDL_CreateThread(Audio::channel_updater, (void*)this);
	}

	Audio::~Audio()
	{
		SDL_KillThread(channel_update_thread);
		SDL_DestroyMutex(channels_mutex);
		
		std::list<Channel *>::iterator p = playing_channels.begin();

		while(p != playing_channels.end())
		{
			(*p)->stop();
			(*p)->release();
			p++;
		}

		alutExit();
	}

	const char * Audio::getName() const
	{
		return "love.audio.openal";
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

	int Audio::channel_updater(void * audio)
	{
		Audio * instance = (Audio*)audio;

		while(!instance->quit_channel_updater)
		{
			MUTEX_ASSERT(SDL_mutexP(instance->channels_mutex), 0);
			
			std::list<Channel *>::iterator p = instance->playing_channels.begin();

			// Update channels and remove completed ones.
			while(p != instance->playing_channels.end())
			{
				if((*p)->isDone())
				{
					(*p)->release();
					instance->playing_channels.erase(p++);
					std::cout << " <-- Channel removed." << std::endl;
				}
				else
				{
					(*p)->update();
					p++;
				}
			}
		

			MUTEX_ASSERT(SDL_mutexV(instance->channels_mutex), 0);
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


	Music * Audio::newMusic(love::sound::Decoder * decoder)
	{
		return new Music(decoder);
	}

	Channel * Audio::newChannel()
	{
		return new Channel();
	}
	
	void Audio::play(Audible * audible, Channel * channel)
	{
		Channel * c = channel;

		if(channel == 0)
			c = new Channel();

		// Set the audible, overwrite if necessary.
		c->setAudible(audible);
		
		// Play the channel.
		c->play();

		// Insert only if not already playing.	
		if(!channel_playing(c))
			channel_insert(c);

		if(channel == 0)
			c->release();
	}

	void Audio::play(Sound * sound, Channel * channel)
	{
		play((Audible*)sound, channel);
	}

	void Audio::play(Music * music, Channel * channel)
	{
		Music * m = music->clone();
		play((Audible*)m, channel);
		m->release();
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
