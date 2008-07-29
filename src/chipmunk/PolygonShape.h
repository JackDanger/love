/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-07-06
*/


#ifndef LOVE_CHIPMUNK_POLYGON_SHAPE_H
#define LOVE_CHIPMUNK_POLYGON_SHAPE_H

// love_chipmunk
#include "Shape.h"

#include <love/mod.h>
#include "chipmunk/chipmunk.h"

// Boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{
	// Special native methods.
	int _PolygonShape_getTransformedPoints(lua_State * L);
	int _PolygonShape_setData(lua_State * L);
	int _PolygonShape_getData(lua_State * L);


	// Forward declarations.
	class Body;

	class PolygonShape : public Shape
	{
		friend int _PolygonShape_getTransformedPoints(lua_State * L);
		friend int _PolygonShape_setData(lua_State * L);
		friend int _PolygonShape_getData(lua_State * L);
	private:
		cpVect * verts;
		cpPolyShape * polygonShape;
	public:

		PolygonShape(boost::shared_ptr<Body> body, cpVect * verts, int num);
		virtual ~PolygonShape();

	}; // PolygonShape

	typedef boost::shared_ptr<PolygonShape> pPolygonShape;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_POLYGON_SHAPE_H
