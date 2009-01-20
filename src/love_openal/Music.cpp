/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-20
**/

#include "Music.h"

#include <iostream>

namespace love
{
namespace openal
{
	Music::Music(SoundData * data)
		: data(data)
	{
		data->retain();
		alGenBuffers(NUM_BUFFERS, buffers);
	}

	Music::~Music()
	{
		data->release();
		alDeleteBuffers(NUM_BUFFERS, buffers);
	}

	Music * Music::clone()
	{
		SoundData * sd = data->clone();
		Music * m = new Music(sd);
		sd->release();
		return m;
	}

	void Music::init(ALuint source)
	{
		for(int i = 0; i < NUM_BUFFERS; i++)
		{
			if(!stream(buffers[i]))
			{
				std::cout << "Could not stream music." << std::endl;
				return;
			}
		}

		alSourceQueueBuffers(source, NUM_BUFFERS, buffers);
	}

	void Music::update(ALuint source)
	{
		// Number of processed buffers.
		ALint processed;

		alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

		while(processed--)
		{
			ALuint buffer;

			// Get a free buffer.
			alSourceUnqueueBuffers(source, 1, &buffer);

			if(stream(buffer))
				alSourceQueueBuffers(source, 1, &buffer);
		}
	}

	void Music::quit(ALuint source)
	{
		ALuint bufs[NUM_BUFFERS];
		alSourceStop(source);
		alSourceUnqueueBuffers(source, NUM_BUFFERS, bufs);
	}

	void Music::rewind(ALuint source)
	{
		// Stop source, unqueue buffers.
		quit(source);

		// Rewind data pointer.
		data->rewind();

		// Requeue buffers.
		init(source);
	}

	bool Music::stream(ALuint buffer)
	{
		// Get more sound data.
		unsigned int decoded = data->decode();

		if(decoded > 0)
		{
			alBufferData(buffer, AL_FORMAT_STEREO16, 
				data->getData(), data->getSize(), 44100);
			return true;

		}
		return false;
	}

} // openal
} // love