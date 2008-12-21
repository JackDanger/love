/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-17
**/

#include "SoundData.h"

// STD
#include <iostream>

namespace love
{
namespace sdlsound
{
	SoundData::SoundData(File * file)
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

		sample = Sound_NewSample(rwops, ext_c, &desired, 1024*4);

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

	love::SoundData * SoundData::clone()
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
} // love
