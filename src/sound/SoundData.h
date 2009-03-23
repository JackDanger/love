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

#ifndef LOVE_SOUND_SOUND_DATA_H
#define LOVE_SOUND_SOUND_DATA_H

// LOVE
#include "../Data.h"

namespace love
{
namespace sound
{
	class SoundData : public Data
	{
	public:
		virtual ~SoundData();
		virtual SoundData * clone() = 0;
		virtual unsigned int decode() = 0;
		virtual unsigned int decodeAll() = 0;
		virtual void setBufferSize(int size) = 0;
		virtual void rewind() = 0;
		virtual void seek(int pos) = 0;
		virtual bool canSeek() = 0;
	}; // SoundData

} // sound
} // love

#endif // LOVE_SOUND_SOUND_DATA_H