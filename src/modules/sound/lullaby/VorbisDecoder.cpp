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

#include "VorbisDecoder.h"

#include <string.h>
#include <common/Exception.h>

namespace love
{
namespace sound
{
namespace lullaby
{
	/**
	* CALLBACK FUNCTIONS
	**/
	int vorbisClose(void * datasource	/* ptr to the data that the vorbis files need*/)
	{
		// Does nothing (handled elsewhere)
		return 1;
	}

	size_t vorbisRead(void * ptr		/* ptr to the data that the vorbis files need*/, 
					  size_t byteSize	/* how big a byte is*/, 
					  size_t sizeToRead	/* How much we can read*/, 
					  void * datasource	/* this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct*/)
	{
		size_t				spaceToEOF;			// How much more we can read till we hit the EOF marker
		size_t				actualSizeToRead;	// How much data we are actually going to read from memory
		SOggFile*			vorbisData;			// Our vorbis data, for the typecast

		// Get the data in the right format
		vorbisData = (SOggFile*)datasource;

		// Calculate how much we need to read.  This can be sizeToRead*byteSize or less depending on how near the EOF marker we are
		spaceToEOF = vorbisData->dataSize - vorbisData->dataRead;
		if ((sizeToRead*byteSize) < spaceToEOF)
			actualSizeToRead = (sizeToRead*byteSize);
		else
			actualSizeToRead = spaceToEOF;	
		
		// A simple copy of the data from memory to the datastruct that the vorbis libs will use
		if (actualSizeToRead)
		{
			// Copy the data from the start of the file PLUS how much we have already read in
			memcpy(ptr, (char*)vorbisData->dataPtr + vorbisData->dataRead, actualSizeToRead);
			// Increase by how much we have read by
			vorbisData->dataRead += (actualSizeToRead);
		}

		// Return how much we read (in the same way fread would)
		return actualSizeToRead;
	}

	int vorbisSeek(void * datasource	/* ptr to the data that the vorbis files need*/,
				   ogg_int64_t offset	/*offset from the point we wish to seek to*/,
				   int whence			/*where we want to seek to*/)
	{
		size_t				spaceToEOF;		// How much more we can read till we hit the EOF marker
		ogg_int64_t			actualOffset;	// How much we can actually offset it by
		SOggFile*			vorbisData;		// The data we passed in (for the typecast)

		// Get the data in the right format
		vorbisData = (SOggFile*) datasource;

		// Goto where we wish to seek to
		switch (whence)
		{
		case SEEK_SET: // Seek to the start of the data file
			// Make sure we are not going to the end of the file
			if (vorbisData->dataSize >= offset)
				actualOffset = offset;
			else
				actualOffset = vorbisData->dataSize;
			// Set where we now are
			vorbisData->dataRead = (int)actualOffset;
			break;
		case SEEK_CUR: // Seek from where we are
			// Make sure we dont go past the end
			spaceToEOF = vorbisData->dataSize - vorbisData->dataRead;
			if (offset < spaceToEOF)
				actualOffset = (offset);
			else
				actualOffset = spaceToEOF;	
			// Seek from our currrent location
			vorbisData->dataRead += (int)actualOffset;
			break;
		case SEEK_END: // Seek from the end of the file
			vorbisData->dataRead = vorbisData->dataSize+1;
			break;
		default:
			throw love::Exception("Unknown seek command in vorbisSeek\n");
			break;
		};

		return 0;
	}

	long vorbisTell(void * datasource	/* ptr to the data that the vorbis files need*/)
	{
		SOggFile * vorbisData;
		vorbisData = (SOggFile*) datasource;
		return vorbisData->dataRead;
	}
	/**
	* END CALLBACK FUNCTIONS
	**/

	VorbisDecoder::VorbisDecoder(Data * data, const std::string & ext, int bufferSize, int sampleRate)
		: Decoder(data, ext, bufferSize, sampleRate)
	{
		// Initialize callbacks
		vorbisCallbacks.close_func = vorbisClose;
		vorbisCallbacks.seek_func  = vorbisSeek;
		vorbisCallbacks.read_func  = vorbisRead;
		vorbisCallbacks.tell_func  = vorbisTell;

		// Initialize OGG file
		oggFile.dataPtr = (char *) data->getData();
		oggFile.dataSize = data->getSize();
		oggFile.dataRead = 0;

		// Open Vorbis handle
		if(ov_open_callbacks(&oggFile, &handle, NULL, 0, vorbisCallbacks) < 0)
			throw love::Exception("Could not read Ogg bitstream");
		
		// Get info and comments
		vorbisInfo = ov_info(&handle, -1);
		vorbisComment = ov_comment(&handle, -1);
	}

	VorbisDecoder::~VorbisDecoder()
	{
		ov_clear(&handle);
	}

	bool VorbisDecoder::accepts(const std::string & ext)
	{
		static const std::string supported[] = {
			"ogg", "oga", ""
		};

		for(int i = 0; !(supported[i].empty()); i++)
		{
			if(supported[i].compare(ext) == 0)
				return true;
		}

		return false;
	}

	love::sound::Decoder * VorbisDecoder::clone()
	{
		return new VorbisDecoder(data, ext, bufferSize, sampleRate);
	}

	int VorbisDecoder::decode()
	{
		int bits = this->getBits();
		int size = 0;
		int section;
		int result;

		if(bits == 16)
			bits = 2;
		else
			bits = 1;

		while(size < bufferSize)
		{
			result = ov_read(&handle, (char*) buffer + size, bufferSize - size, 0, bits, 1, &section);

			if(result > 0)
				size += result;
			else if(result < 0)
			{
				switch(result)
				{
				case OV_EREAD:
					throw love::Exception("Vorbis read: Read from media");
				case OV_ENOTVORBIS:
					throw love::Exception("Vorbis read: Not Vorbis data");
				case OV_EVERSION:
					throw love::Exception("Vorbis read: Vorbis version mismatch");
				case OV_EBADHEADER:
					throw love::Exception("Vorbis read: Invalid Vorbis header");
				case OV_EFAULT:
					throw love::Exception("Vorbis read: Internal logic fault (bug or heap/stack corruption)");
				default:
					throw love::Exception("Vorbis read: Unknown error");
				}
			}
			else
				break;
		}

		if(oggFile.dataSize - oggFile.dataRead == 0)
			eof = true;

		return size;
	}

	bool VorbisDecoder::seek(int ms)
	{
		eof = false;
		int result = ov_time_seek(&handle, ms / 100);

		if(result == 0)
			return true;
		
		switch(result)
		{
		case OV_ENOSEEK:
			throw love::Exception("Vorbis seek: Bitstream is unseekable");
		case OV_EINVAL:
			throw love::Exception("Vorbis seek: Invalid argument value");
		case OV_EREAD:
			throw love::Exception("Vorbis seek: Read from media");
		case OV_EFAULT:
			throw love::Exception("Vorbis seek: Internal logic fault (bug or heap/stack corruption)");
		case OV_EBADLINK:
			throw love::Exception("Vorbis seek: Invalid stream section supplied or link is corrupt");
		default:
			throw love::Exception("Vorbis seek: Unknown error");
		}

		return false;
	}

	bool VorbisDecoder::rewind()
	{
		eof = false;
		return this->seek(0);
	}

	bool VorbisDecoder::isSeekable()
	{
		long result = ov_seekable(&handle);
		return (result != 0);
	}

	int VorbisDecoder::getChannels() const
	{
		return vorbisInfo->channels;
	}

	int VorbisDecoder::getBits() const
	{
		//return vorbisInfo->bitrate_nominal / 10000;
		return 16;
	}

	int VorbisDecoder::getSampleRate() const
	{
		return vorbisInfo->rate;
	}

} // lullaby
} // sound
} // love
