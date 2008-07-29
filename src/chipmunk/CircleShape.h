/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-07-06
*/

#ifndef LOVE_CHIPMUNK_CIRCLE_SHAPE_H
#define LOVE_CHIPMUNK_CIRCLE_SHAPE_H

// love_chpimunk
#include "Space.h"
#include "Shape.h"

// Boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{
	// Forward declarations.
	class Body;

	int _CircleShape_setData(lua_State * L);
	int _CircleShape_getData(lua_State * L);
	int _CircleShape_getPoint(lua_State * L);

	class CircleShape : public Shape
	{
		friend int _CircleShape_setData(lua_State * L);
		friend int _CircleShape_getData(lua_State * L);
		friend int _CircleShape_getPoint(lua_State * L);
	protected:
		cpCircleShape * circleShape;
	public:
		CircleShape(boost::shared_ptr<Body> body, float r, float x, float y);
		virtual ~CircleShape();
	}; // CircleShape

	typedef boost::shared_ptr<CircleShape> pCircleShape;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_CIRCLE_SHAPE_H
