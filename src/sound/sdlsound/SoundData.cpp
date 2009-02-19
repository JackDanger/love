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

#include "SoundData.h"

// STD
#include <iostream>

namespace love
{
namespace sound
{
namespace sdlsound
{
	SoundData::SoundData(love::filesystem::File * file)
		: file(file)
	{
		file->retain();

		if(!file->load())
		{
			std::cerr << "Could not load file" << std::endl;
			return;
		}

		SDL_RWops * rwops = SDL_RWFromConstMem((const void*)file->getData(), file->getSize());

		Sound_AudioInfo desired;
		desired.channels = 2;
		desired.format = AUDIO_S16SYS;
		desired.rate = 44100;

		// Get the extention of the file. Note: this is required for 
		// module-files such as XM!
		std::string ext = file->getExtention();
		const char * ext_c = ext.empty() ? 0 : ext.c_str();

		sample = Sound_NewSample(rwops, ext_c, &desired, 1024);

		if(sample == 0)
		{
			std::cerr << Sound_GetError() << std::endl;
			return;
		}
	}

	SoundData::~SoundData()
	{
		file->release();
		Sound_FreeSample(sample);
	}

	void * SoundData::getData()
	{
		return sample->buffer;
	}

	int SoundData::getSize()
	{
		return (int)sample->buffer_size;
	}

	love::sound::SoundData * SoundData::clone()
	{
		return new SoundData(file);
	}

	unsigned int SoundData::decode()
	{
		return (unsigned int)Sound_Decode(sample);
	}

	unsigned int SoundData::decodeAll()
	{
		return (unsigned int)Sound_DecodeAll(sample);
	}

	void SoundData::setBufferSize(int size)
	{
		Sound_SetBufferSize(sample, size);
	}

	void SoundData::rewind()
	{
		Sound_Rewind(sample);
	}

	void SoundData::seek(int pos)
	{
		pos = pos < 0 ? 0 : pos;
		Sound_Seek(sample, pos);
	}

	bool SoundData::canSeek()
	{
		return ((sample->flags | SOUND_SAMPLEFLAG_CANSEEK) != 0);
	}

} // sdlsound
} // sound
} // love
