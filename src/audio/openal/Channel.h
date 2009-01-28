/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-20
**/

#ifndef LOVE_AUDIO_OPENAL_CHANNEL_H
#define LOVE_AUDIO_OPENAL_CHANNEL_H

// LOVE
#include "../../Object.h"

// love_openal
#include "Audible.h"

// OpenAL
#include <alut.h>

namespace love
{
namespace audio
{
namespace openal
{
	class Channel : public Object
	{
	private:
		ALuint source;
		Audible * audible;
	public:
		Channel();
		virtual ~Channel();
		void setAudible(Audible * audible);
		void play();
		void stop();
		void pause();
		void rewind();
		bool isDone();
		void update();

		void setPitch(float pitch);
		float getPitch();

		void setVolume(float volume);
		float getVolume();

	}; // Channel

} // openal
} // audio
} // love

#endif // LOVE_AUDIO_OPENAL_CHANNEL_H