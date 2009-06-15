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

#include "ModPlugDecoder.h"

#include <common/Exception.h>

namespace love
{
namespace sound
{
namespace lullaby
{
	ModPlugDecoder::ModPlugDecoder(filesystem::File * file, int bufferSize, int sampleRate)
		: plug(0), data(0), bufferSize(bufferSize), actualSize(bufferSize), eof(false), buffer(0)
	{
		init(file->read(), bufferSize, sampleRate, file->getExtention());
	}

	ModPlugDecoder::ModPlugDecoder(Data * data, int bufferSize, int sampleRate, const std::string & ext)
		: plug(0), data(0), bufferSize(bufferSize), actualSize(bufferSize), eof(false), buffer(0)
	{
		init(data, bufferSize, sampleRate, ext);
	}

	ModPlugDecoder::~ModPlugDecoder()
	{
		if(plug != 0)
			ModPlug_Unload(plug);
		if(data != 0)
			data->release();
		if(buffer != 0)
			delete [] buffer;
	}

	Decoder * ModPlugDecoder::clone()
	{
		return new ModPlugDecoder(data, bufferSize, settings.mFrequency, ext);
	}

	int ModPlugDecoder::decode()
	{
		int r =  ModPlug_Read(plug, buffer, bufferSize);

		if(r == 0)
			eof = true;

		return r;
	}

	int ModPlugDecoder::decodeAll()
	{
		return 0;
	}

	int ModPlugDecoder::getSize() const
	{
		return actualSize;
	}

	void * ModPlugDecoder::getBuffer() const
	{
		return buffer;
	}

	bool ModPlugDecoder::seek(int ms)
	{
		ModPlug_Seek(plug, ms);
		return true;
	}

	bool ModPlugDecoder::rewind()
	{
		ModPlug_Seek(plug, 0);
		return true;
	}

	bool ModPlugDecoder::isSeekable()
	{
		return true;
	}

	bool ModPlugDecoder::isFinished()
	{
		return eof;
	}

	sound::Decoder::Format ModPlugDecoder::getFormat()  const 
	{
		return STEREO16;
	}

	int ModPlugDecoder::getSampleRate() const
	{
		return settings.mFrequency;
	}

	void ModPlugDecoder::init(Data * data, int bufferSize, int sampleRate, const std::string & ext)
	{
		this->ext = ext;
		this->data = data;
		data->retain();

		buffer = (void*)(new char[bufferSize]);

		settings.mFlags = MODPLUG_ENABLE_OVERSAMPLING | MODPLUG_ENABLE_NOISE_REDUCTION;
		settings.mChannels = 2;
		settings.mBits = 16;
		settings.mFrequency = sampleRate;
		settings.mResamplingMode = MODPLUG_RESAMPLE_LINEAR;
		settings.mLoopCount = 0;

		ModPlug_SetSettings(&settings);

		plug = ModPlug_Load(data->getData(), data->getSize());

		if(plug == 0)
			throw love::Exception("Could not load file with ModPlug.");
	}

} // lullaby
} // sound
} // love
