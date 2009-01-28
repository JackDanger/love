/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-17
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
