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

#include "FLACDecoder.h"

#include <set>
#include <common/Exception.h>

namespace love
{
namespace sound
{
namespace lullaby
{
	FLACDecoder::FLACDecoder(Data * data, const std::string & ext, int bufferSize, int sampleRate)
		: Decoder(data, ext, bufferSize, sampleRate), pos(0)
	{
		init_ogg();
	}
	
	FLACDecoder::~FLACDecoder()
	{
		finish();
	}
	
	bool FLACDecoder::accepts(const std::string & ext)
	{
		static const std::string supported[] = {
			"flac", ""
		};

		for(int i = 0; !(supported[i].empty()); i++)
		{
			if(supported[i].compare(ext) == 0)
				return true;
		}

		return false;
	}

	love::sound::Decoder *FLACDecoder::clone()
	{
		return new FLACDecoder(data, ext, bufferSize, sampleRate);
	}

	int FLACDecoder::decode()
	{
		//process_single();
		process_until_end_of_stream();
		return 16;
	}

	bool FLACDecoder::seek(int ms)
	{
		seek_absolute(ms);
	}

	bool FLACDecoder::rewind()
	{
		seek_absolute(0);
	}

	bool FLACDecoder::isSeekable()
	{
		return true;
	}

	int FLACDecoder::getChannels() const
	{
		return 2;
	}

	int FLACDecoder::getBits() const
	{
		return 16;
	}
	
	FLAC__StreamDecoderReadStatus FLACDecoder::read_callback(FLAC__byte buffer[], size_t *bytes)
	{
		int size = data->getSize();
		char *d = (char *) data->getData() + pos;
		if (pos >= size)
			return FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM;
		if (pos+*bytes <= size)
		{
			memcpy(buffer, d, *bytes);
			pos = pos+*bytes;
		}
		else
		{
			memcpy(buffer, d, size-pos);
			*bytes = size-pos;
			pos = size;
		}
		return FLAC__STREAM_DECODER_READ_STATUS_CONTINUE;
	}
	
	FLAC__StreamDecoderSeekStatus FLACDecoder::seek_callback(FLAC__uint64 offset)
	{
		pos = offset;
		return FLAC__STREAM_DECODER_SEEK_STATUS_OK;
	}
	
	FLAC__StreamDecoderTellStatus FLACDecoder::tell_callback(FLAC__uint64 *offset)
	{
		*offset = pos;
		return FLAC__STREAM_DECODER_TELL_STATUS_OK;
	}
	
	FLAC__StreamDecoderLengthStatus FLACDecoder::length_callback(FLAC__uint64 *length)
	{
		*length = data->getSize();
		return FLAC__STREAM_DECODER_LENGTH_STATUS_OK;
	}
	
	bool FLACDecoder::eof_callback()
	{
		return (pos >= data->getSize());
	}
	
	FLAC__StreamDecoderWriteStatus FLACDecoder::write_callback(const FLAC__Frame *frame, const FLAC__int32 *const fbuffer[])
	{
		printf("FLAC: %d\n", frame->header.blocksize);
		memcpy(buffer, fbuffer, frame->header.blocksize);
		return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
	}
	
	void FLACDecoder::metadata_callback(const FLAC__StreamMetadata *metadata)
	{
		printf("Metadata\n");
		//we do nothing with metadata...
		return;
	}
	
	void FLACDecoder::error_callback(FLAC__StreamDecoderErrorStatus status)
	{
		//wow.. error, let's throw one (please clean this part up sometime)
		throw love::Exception("FLAC error: %s!", FLAC__StreamDecoderErrorStatusString[status]);
	}
} // lullaby
} // sound
} // love
