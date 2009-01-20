/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-17
**/

#ifndef LOVE_SDLSOUND_SOUND_DATA_H
#define LOVE_SDLSOUND_SOUND_DATA_H

// LOVE
#include "../liblove/filesystem/File.h"
#include "../liblove/sound/SoundData.h"

// SDL_sound
#include <SDL_sound.h>

namespace love
{	
namespace sdlsound
{
	class SoundData : public love::SoundData
	{
	private:

		// The sample structure from SDL_sound.
		Sound_Sample * sample;

		File * file;

		char * data;

	public:
		SoundData(File * file);
		virtual ~SoundData();

		// Implements Data.
		void * getData();
		int getSize();

		// Implements love::SoundData
		love::SoundData * clone();
		unsigned int decode();
		unsigned int decodeAll();
		void setBufferSize(int size);
		void rewind();
		void seek(int pos);
		bool canSeek();

	}; // SoundData

} // sdlsound
} // love

#endif // LOVE_SDLSOUND_SOUND_DATA_H
