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

#ifndef LOVE_SOUND_SDLSOUND_SOUND_DATA_H
#define LOVE_SOUND_SDLSOUND_SOUND_DATA_H

// LOVE
#include "../../filesystem/File.h"
#include "../SoundData.h"

// SDL_sound
#include <SDL_sound.h>

namespace love
{	
namespace sound
{
namespace sdlsound
{
	class SoundData : public love::sound::SoundData
	{
	private:

		// The sample structure from SDL_sound.
		Sound_Sample * sample;

		love::filesystem::File * file;

		char * data;

	public:
		SoundData(love::filesystem::File * file);
		virtual ~SoundData();

		// Implements Data.
		void * getData();
		int getSize();

		// Implements love::SoundData
		love::sound::SoundData * clone();
		unsigned int decode();
		unsigned int decodeAll();
		void setBufferSize(int size);
		void rewind();
		void seek(int pos);
		bool canSeek();

	}; // SoundData

} // sdlsound
} // sound
} // love

#endif // LOVE_SOUND_SDLSOUND_SOUND_DATA_H