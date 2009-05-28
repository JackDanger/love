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
namespace sdlsound
{
	SoundData::SoundData(filesystem::File * file)
		: data(0), size(0)
	{
		// Read the raw data from the file.
		Data * raw = file->read();

		SDL_RWops * rwops = SDL_RWFromConstMem((const void*)raw->getData(), raw->getSize());

		Sound_AudioInfo desired;
		desired.channels = 2;
		desired.format = AUDIO_S16SYS;
		desired.rate = 44100;

		// Get the extention of the file. Note: this is required for 
		// module-files such as XM!
		std::string ext = file->getExtention();

		// Create the SDL_sound sample.
		Sound_Sample * sample = Sound_NewSample(rwops, (ext.empty() ? 0 : ext.c_str()), &desired, 1024);

		if(sample == 0)
		{
			raw->release();
			std::cerr << Sound_GetError() << std::endl;
			return;
		}

		Sound_DecodeAll(sample);

		raw->release();

		// Copy memory.
		size = sample->buffer_size;
		data = new short[size];

		memcpy(data, sample->buffer, size);

		// Cleanup sample.
		Sound_FreeSample(sample);
		
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

	void SoundData::setSample(int i, float sample)
	{
		if(data != 0 && i >= 0 && i < size)
			data[i] = (short)(sample*(float)SHRT_MAX);
	}

	float SoundData::getSample(int i) const
	{
		if(data != 0 && i >= 0 && i < size)
			return ((float)data[i])/(float)SHRT_MAX;
		return 0;
	}


} // sdlsound
} // sound
} // love
