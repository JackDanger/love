/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
**/

#ifndef LOVE_GRAPHICS_VOLATILE_H
#define LOVE_GRAPHICS_VOLATILE_H

// STL
#include <list>

namespace love
{
namespace graphics
{
	class Volatile
	{
	private:

		// A list of all Volatile objcets currently alive.
		static std::list<Volatile *> all;

	public:
		Volatile();
		virtual ~Volatile();

		virtual bool loadVolatile() = 0;
		virtual void unloadVolatile() = 0;

		static bool loadAll();
		static void unloadAll();

	};

} // graphics
} // love

#endif // LOVE_GRAPHICS_VOLATILE_H
