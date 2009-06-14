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

#include "SoundData.h"

// STD
#include <iostream>
#include <climits>

namespace love
{
namespace sound
{
	SoundData::SoundData(Decoder * decoder)
		: data(0), size(0), format(Decoder::UNSUPPORTED), sampleRate(Decoder::DEFAULT_SAMPLE_RATE)
	{

		decoder->decodeAll();

		format = decoder->getFormat();
		sampleRate = decoder->getSampleRate();

		// Copy memory.
		size = decoder->getSize();
		data = new char[size];

		memcpy(data, decoder->getBuffer(), size);		
	}

	SoundData::~SoundData()
	{
		if(data != 0)
			delete [] data;
	}

	void * SoundData::getData() const
	{
		return (void*)data;
	}

	int SoundData::getSize() const
	{
		return (int)size;
	}

	Decoder::Format SoundData::getFormat() const
	{
		return format;
	}

	int SoundData::getSampleRate() const
	{
		return sampleRate;
	}

	void SoundData::setSample(int i, float sample)
	{
	}

	float SoundData::getSample(int i) const
	{
		return 0;
	}

} // sound
} // love
