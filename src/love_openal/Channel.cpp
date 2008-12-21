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
	Channel::Channel(Audible * audible)
		: source(0), audible(audible)
	{
		audible->retain();
		alGenSources(1, &source);
		std::cout << "Channel created." << std::endl;
	}

	Channel::~Channel()
	{
		audible->release();
		std::cout << "Channel destroyed." << std::endl;
	}

	void Channel::play()
	{
		audible->init(source);
		alSourcePlay(source);
	}

	bool Channel::isDone()
	{
		ALenum state;
		alGetSourcei(source, AL_SOURCE_STATE, &state);
		return (state == AL_STOPPED);
	}

	void Channel::update()
	{
		audible->update(source);
	}
	
	void Channel::setPitch(float pitch)
	{
		alSourcef(source, AL_PITCH, pitch);
	}

} // openal
} // love