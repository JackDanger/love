/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_VOLATILE_H
#define LOVE_VOLATILE_H

// STL
#include <list>

namespace love_opengl
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
}

#endif
