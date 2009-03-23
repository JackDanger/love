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
* 
* --> Visit http://love2d.org for more information! (^.^)/
**/

#include "Channel.h"

#include <iostream>

namespace love
{
namespace audio
{
namespace openal
{
	Channel::Channel()
		: source(0), audible(0)
	{
		alGenSources(1, &source);
		std::cout << "+Channel created." << std::endl;
	}

	Channel::~Channel()
	{
		if(audible != 0)
		{
			this->audible->quit(source);
			audible->release();
		}

		alDeleteSources(1, &source);
		std::cout << "-Channel destroyed." << std::endl;
	}

	void Channel::setAudible(Audible * audible)
	{
		if(this->audible != 0)
		{
			this->audible->quit(source);
			this->audible->release();
		}

		this->audible = audible;
		audible->retain();
	}

	void Channel::play()
	{
		if(audible != 0)
			audible->init(source);
		alSourcePlay(source);
	}

	void Channel::stop()
	{
		alSourceStop(source);

		if(this->audible != 0)
		{
			this->audible->quit(source);
			this->audible->release();
			this->audible = 0;
		}
	}

	void Channel::pause()
	{
		alSourcePause(source);
	}

	void Channel::rewind()
	{
		audible->rewind(source);
	}

	bool Channel::isDone()
	{
		ALenum state;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		return (state == AL_STOPPED);
	}

	void Channel::update()
	{
		if(audible != 0)
			audible->update(source);
	}
	
	void Channel::setPitch(float pitch)
	{
		alSourcef(source, AL_PITCH, pitch);
	}

	float Channel::getPitch()
	{
		ALfloat pitch;
		alGetSourcef(source, AL_PITCH, &pitch);
		return pitch;
	}

	void Channel::setVolume(float volume)
	{
		alSourcef(source, AL_GAIN, volume);
	}

	float Channel::getVolume()
	{
		ALfloat volume;
		alGetSourcef(source, AL_GAIN, &volume);
		return volume;
	}

} // openal
} // audio
} // love
