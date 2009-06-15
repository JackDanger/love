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

#include "Mpg123Decoder.h"

#include <set>
#include <common/Exception.h>

namespace love
{
namespace sound
{
namespace lullaby
{
	Mpg123Decoder::Mpg123Decoder(Data * data, const std::string & ext, int bufferSize, int sampleRate)
		: Decoder(data, ext, bufferSize, sampleRate), handle(0), data(data)
	{
		int ret = mpg123_init();
		if (ret != MPG123_OK)
			throw love::Exception("Could not initialize mpg123.");
		//Intialize the handle
		handle = mpg123_new(NULL, &ret);
		if (handle == NULL)
			throw love::Exception("Could not create handle.");
		ret = mpg123_open_feed(handle);
		if (ret != MPG123_OK)
			throw love::Exception("Could not open feed.");
	}

	Mpg123Decoder::~Mpg123Decoder()
	{
		mpg123_close(handle);
	}

	bool Mpg123Decoder::accepts(const std::string & ext)
	{
		static const std::string supported[] = {
			"mp3", ""
		};

		for(int i = 0; !(supported[i].empty()); i++)
		{
			if(supported[i].compare(ext) == 0)
				return true;
		}

		return false;
	}

	love::sound::Decoder * Mpg123Decoder::clone()
	{
		return new Mpg123Decoder(data, ext, bufferSize, sampleRate);
	}

	int Mpg123Decoder::decode()
	{
		size_t numbytes;
		int r =  mpg123_decode(handle, (unsigned char*) data->getData(), data->getSize(), (unsigned char*) buffer, bufferSize, &numbytes);

//		if (r != MPG123_DONE && r != MPG123_OK)
			//throw love::Exception("Could not decode data.");
		if (numbytes == 0)
			eof = true;

		return numbytes;
	}

	bool Mpg123Decoder::seek(int ms)
	{
		mpg123_seek(handle, SEEK_SET, ms);
		return true;
	}

	bool Mpg123Decoder::rewind()
	{
		mpg123_seek(handle, SEEK_SET, 0);
		return true;
	}

	bool Mpg123Decoder::isSeekable()
	{
		return true;
	}

	sound::Decoder::Format Mpg123Decoder::getFormat() const 
	{
		return STEREO16;
	}

} // lullaby
} // sound
} // love
