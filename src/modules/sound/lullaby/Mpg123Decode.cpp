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
		: Decoder(data, ext, bufferSize, sampleRate), plug(0)
	{
		
		//Intialize the handle
		int ret = mpg123_open_feed(handle);
		if (ret != MPG123_DONE )
			throw love::Exception("Could not open a mpg123 file handle.");
		
		int ret = mpg123_feed(handle, data->getData(), data->getSize());
		if (ret != MPG123_DONE )
			throw love::Exception("Could not feed data into mpg123.");
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
		int numbytes;
		int r =  mpg123_read(handle, buffer, bufferSize, &numbytes);

		if (r != MPG123_DONE)
			throw love::Exception("Could not decode file.");
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
