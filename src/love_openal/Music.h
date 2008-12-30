/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-20
**/

#ifndef LOVE_OPENAL_MUSIC_H
#define LOVE_OPENAL_MUSIC_H

// LOVE
#include "../liblove/sound/SoundData.h"

// love_openal
#include "Audible.h"

namespace love
{
namespace openal
{
	class Music : public Audible
	{
	private:
		static const unsigned int NUM_BUFFERS = 4;
		ALuint buffers[NUM_BUFFERS];
		SoundData * data;
	public:
		Music(SoundData * data);
		virtual ~Music();
		Music * clone();
		void init(ALuint source);
		void update(ALuint source);
		void quit(ALuint source);
		void rewind(ALuint source);
	private:
		bool stream(ALuint buffer);
	}; // Sound

} // openal
} // love

#endif // LOVE_OPENAL_MUSIC_H