/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-20
**/

#ifndef LOVE_AUDIO_OPENAL_MUSIC_H
#define LOVE_AUDIO_OPENAL_MUSIC_H

// LOVE
#include "../../sound/SoundData.h"
#include "Audible.h"

namespace love
{
namespace audio
{
namespace openal
{
	class Music : public Audible
	{
	private:
		static const unsigned int NUM_BUFFERS = 4;
		ALuint buffers[NUM_BUFFERS];
		love::sound::SoundData * data;
	public:
		Music(love::sound::SoundData * data);
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
} // audio
} // love

#endif // LOVE_AUDIO_OPENAL_MUSIC_H