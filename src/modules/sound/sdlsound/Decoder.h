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

#ifndef LOVE_SOUND_SDLSOUND_DECODER_H
#define LOVE_SOUND_SDLSOUND_DECODER_H

// LOVE
#include <sound/Decoder.h>
#include <filesystem/File.h>

// SDL_sound
#include <SDL_sound.h>

namespace love
{
namespace sound
{
namespace sdlsound
{
	class Decoder : public love::sound::Decoder
	{
	private:

		Sound_Sample * sample;
		Data * data;
		std::string ext;

	public:

		Decoder(filesystem::File * file, int bufferSize, int sampleRate);
		Decoder(Data * data, int bufferSize, int sampleRate, const std::string & ext);
		~Decoder();
		Decoder * clone();
		int decode();
		int decodeAll();
		int getSize() const;
		void * getBuffer() const;
		bool seek(int ms);
		bool rewind();
		bool isSeekable();
		bool isFinished();
		Format getFormat() const;
		int getSampleRate() const;

	private:
		void init(Data * data, int bufferSize, int sampleRate, const std::string & ext);

	}; // Decoder

} // sdlsound
} // sound
} // love

#endif // LOVE_SOUND_SDLSOUND_DECODER_H
