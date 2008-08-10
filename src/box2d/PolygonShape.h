/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-09
*/
#ifndef LOVE_BOX2D_POLYGON_SHAPE_H
#define LOVE_BOX2D_POLYGON_SHAPE_H

// Module
#include "Shape.h"

namespace love_box2d
{
	class PolygonShape : public Shape
	{
	private:
	public:
		PolygonShape(boost::shared_ptr<Body> body, b2PolygonDef * def);
		virtual ~PolygonShape();
		int getPoints(lua_State * L);
	};

	typedef boost::shared_ptr<PolygonShape> pPolygonShape;

} // love_box2d

#endif // LOVE_BOX2D_POLYGON_SHAPE_H
