/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*
* A Chipmunk 2D wrapper. Provides 2D physics and
* fun for everyone in the family.
* 
* @author Anders Ruud
* @date 2008-03-21
*/
#ifndef LOVE_MOD_CHIPMUNK_H
#define LOVE_MOD_CHIPMUNK_H

// LOVE
#include "../mod.h"

// Module.
#include "Space.h"
#include "Body.h"
#include "Shape.h"

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_chipmunk
{
	// Functions that should be availble to the love executable
	// must be declared C-style.
	extern "C"
	{
		// Standard module functions.
		bool DECLSPEC init(love_mod::modconf * conf);
		bool DECLSPEC quit();
		bool DECLSPEC luaopen(lua_State * s);
	}

	pSpace newSpace();
	pBody newBody(pSpace space, float x, float y, float m, float i);
	pShape newCircle(pSpace space, pBody body, float radius);

} // love_chipmunk

#endif // LOVE_MOD_CHIPMUNK_H
