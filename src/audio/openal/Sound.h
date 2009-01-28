/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
**/

#ifndef LOVE_AUDIO_OPENAL_SOUND_H
#define LOVE_AUDIO_OPENAL_SOUND_H

// LOVE
#include "../../sound/SoundData.h"
#include "Audible.h"

// OpenAL
#include <alut.h>

namespace love
{
namespace audio
{
namespace openal
{
	class Sound : public Audible
	{
	private:

		// Sounds only need one buffer.
		ALuint buffer;

	public:
		Sound(love::sound::SoundData * data);
		virtual ~Sound();
		void init(ALuint source);
		void update(ALuint source);
		void quit(ALuint source);
		void rewind(ALuint source);
	}; // Sound

} // openal
} // audio
} // love

#endif // LOVE_AUDIO_OPENAL_SOUND_H