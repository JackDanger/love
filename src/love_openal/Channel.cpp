/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-20
**/

#include "Channel.h"

#include <iostream>

namespace love
{
namespace openal
{
	Channel::Channel()
		: source(0), audible(0)
	{
		alGenSources(1, &source);
		std::cout << "Channel created." << std::endl;
	}

	Channel::~Channel()
	{
		if(audible != 0)
			audible->release();
		std::cout << "Channel destroyed." << std::endl;
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

} // openal
} // love