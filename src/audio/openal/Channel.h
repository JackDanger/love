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
* 
* --> Visit http://love2d.org for more information! (^.^)/
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