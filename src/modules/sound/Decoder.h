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

#ifndef LOVE_SOUND_DECODER_H
#define LOVE_SOUND_DECODER_H

// LOVE
#include <common/Object.h>

namespace love
{
namespace sound
{
	/**
	* Decoder objects are responsible for decoding audio files. They maintain 
	* an interal buffer into which they write raw decoded audio data. 
	**/
	class Decoder : public Object
	{
	public:

		/**
		* Supported formats are signed 8/16 bit samples, either mono
		* or stereo.
		**/
		enum Format
		{
			UNSUPPORTED,
			MONO8,
			MONO16,
			STEREO8,
			STEREO16,
		};

		/**
		* Indicates how many bytes of raw data should be generated at each
		* call to Decode.
		**/
		static const int DEFAULT_BUFFER_SIZE = 1024;

		/**
		* Indicates the quality of the sound. 
		**/
		static const int DEFAULT_SAMPLE_RATE = 44100;

		/**
		* Example of subclass constructor:
		* 
		* Creates a new Decoder, or throws a love::Exception if the file format
		* is unrecognized, or any other error occors.
		**/
		//Decoder(filesystem::File * file, int bufferSize, int sampleRate);

		/**
		* Destructor. Should free internal buffer. 
		**/
		virtual ~Decoder(){};

		/**
		* Decodes the next chunk of the music stream, this will usually be
		* bufferSize amount of bytes, unless EOF occurs. A negative value on 
		* errors.
		* @return The number of bytes actually decoded.
		**/
		virtual int decode() = 0;

		/**
		* Decodes all data in the file. This also changes the size of the
		* buffer as needed.
		* @return The number of bytes decoded.
		**/
		virtual int decodeAll() = 0;

		/**
		* Gets the size of the buffer (NOT the size of the entire stream).
		* @return The size of the buffer. May vary on EOF.
		**/
		virtual int getSize() const = 0;

		/**
		* Gets a pointer to the actual data. The contents of this buffer will 
		* change with each call to decode, so the client must copy the data.
		* @return A buffer to raw sound data.
		**/
		virtual void * getBuffer() const = 0;

		/**
		* Seeks to the specified position, if possible.
		* @param pos The position in the stream (millisecond precision).  
		* @return True if success, false on fail/unsupported.
		**/
		virtual bool seek(float pos) = 0;

		/**
		* Rewinds the stream to the start.
		**/
		virtual void rewind() = 0;

		/**
		* Checks whether a stream is seekable.
		* @return True if seekable, false otherwise.
		**/
		virtual bool isSeekable() = 0;

		/**
		* Checks whether a stream has more data to decode or not. Use
		* rewind to start the stream again.
		* @return True if there is more data, false on EOF.
		**/
		virtual bool isFinished() = 0;

		/**
		* Gets the format for the stream.
		* @return A format identifier, or UNSUPPORTED if conversion is impossible.
		**/
		virtual Format getFormat() = 0;

	}; // Decoder

} // sound
} // love

#endif // LOVE_SOUND_SOUND_STREAM_H