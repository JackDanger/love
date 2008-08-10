/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-08
*/
#ifndef LOVE_MOD_BOX2D_H
#define LOVE_MOD_BOX2D_H

// LOVE
#include <love/mod.h>

// Box2D
#include <Box2D.h>

// Module.
#include "World.h"
#include "Body.h"
#include "CircleShape.h"
#include "PolygonShape.h"

// Creating a separate namespace to avoid conflicts
// with standard library functions.
namespace love_box2d
{
	// Standard module functions.
	bool module_init(int argc, char ** argv, love::Core * core);
	bool module_quit();
	bool module_open(void * vm);

	pWorld newWorld(float lx, float ly, float ux, float uy, float gx, float gy, bool sleep);
	pBody newBody(pWorld world, float x, float y, float mass);
	pCircleShape newCircle(pBody body, float radius);
	pCircleShape newCircle(pBody body, float x, float y, float radius);
	int newPolygon(lua_State * L);

} // love_box2d

#endif // LOVE_MOD_BOX2D_H
