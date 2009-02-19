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

#include "Music.h"

#include <iostream>

namespace love
{
namespace audio
{
namespace openal
{
	Music::Music(love::sound::SoundData * data)
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
		love::sound::SoundData * sd = data->clone();
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
} // audio
} // love