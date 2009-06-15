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

#include "Decoder.h"

#include <common/Exception.h>

namespace love
{
namespace sound
{
namespace sdlsound
{
	Decoder::Decoder(filesystem::File * file, int bufferSize, int sampleRate)
		: sample(0), data(0)
	{
		init(file->read(), bufferSize, sampleRate, file->getExtention());
	}

	Decoder::Decoder(Data * data, int bufferSize, int sampleRate, const std::string & ext)
		: data(0)
	{
		init(data, bufferSize, sampleRate, ext);
	}

	Decoder::~Decoder()
	{
		if(sample != 0)
			Sound_FreeSample(sample);
		if(data != 0)
			data->release();
	}

	Decoder * Decoder::clone()
	{
		return new Decoder(data, sample->buffer_size, sample->desired.rate, ext);
	}

	int Decoder::decode()
	{
		return Sound_Decode(sample);
	}

	int Decoder::getSize() const
	{
		return sample->buffer_size;
	}

	void * Decoder::getBuffer() const
	{
		return (void*)(sample->buffer);
	}

	bool Decoder::seek(int ms)
	{
		return (Sound_Seek(sample, ms) != 0);
	}

	bool Decoder::rewind()
	{
		return (Sound_Rewind(sample) != 0);
	}

	bool Decoder::isSeekable()
	{
		return (sample->flags & SOUND_SAMPLEFLAG_CANSEEK) != 0;
	}

	bool Decoder::isFinished()
	{
		return (sample->flags & SOUND_SAMPLEFLAG_EOF) != 0;
	}

	sound::Decoder::Format Decoder::getFormat()  const 
	{

		// Channels.
		int c = sample->desired.channels;

		if(c < 1 && c > 2)
			return UNSUPPORTED;

		switch(sample->desired.format)
		{
		case AUDIO_S16SYS:
			return (c == 2) ? STEREO16 : MONO16;
		case AUDIO_S8:
			return (c == 2) ? STEREO8 : MONO8;
		default:
			return UNSUPPORTED;
		}
	}

	int Decoder::getSampleRate() const
	{
		return sample->desired.rate;
	}

	void Decoder::init(Data * data, int bufferSize, int sampleRate, const std::string & ext)
	{
		this->ext = ext;
		this->data = data;

		data->retain();

		SDL_RWops * rwops = SDL_RWFromConstMem((const void*)data->getData(), data->getSize());

		Sound_AudioInfo desired;
		desired.channels = 2; // Stereo please.
		desired.format = AUDIO_S16SYS; // We want signed 16 bit.
		desired.rate = sampleRate;

		// Create the SDL_sound sample.
		sample = Sound_NewSample(rwops, (ext.empty() ? 0 : ext.c_str()), &desired, bufferSize);

		if(sample == 0)
			throw love::Exception(Sound_GetError());
	}

} // sdlsound
} // sound
} // love
