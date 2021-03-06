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

#include "Music.h"

namespace love
{
namespace audio
{
namespace null
{
	Music::Music(love::sound::Decoder * decoder)
		: decoder(decoder)
	{
		decoder->retain();
	}

	Music::~Music()
	{
		decoder->release();
	}

	love::audio::Music * Music::clone()
	{
		return new Music(decoder->clone());
	}

	void Music::play(love::audio::Source * s)
	{
	}

	void Music::update(love::audio::Source * s)
	{
	}

	void Music::stop(love::audio::Source * s)
	{
	}

	void Music::rewind(love::audio::Source * s)
	{
	}

} // null
} // audio
} // love