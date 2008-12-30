/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-20
**/

#ifndef LOVE_OPENAL_CHANNEL_H
#define LOVE_OPENAL_CHANNEL_H

// LOVE
#include "../liblove/Object.h"

// love_openal
#include "Audible.h"

// OpenAL
#include <alut.h>

namespace love
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
		bool isDone();
		void update();
		void setPitch(float pitch);
		float getPitch();
	}; // Channel

} // openal
} // love

#endif // LOVE_OPENAL_CHANNEL_H