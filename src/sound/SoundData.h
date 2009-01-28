/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-12-16
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