/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love2d.org
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
	/**
	* You should know what a Polygon is. :)
	* 
	* This class is needed so that we can easily get
	* the transformed points in Lua. By calling shape:getPoints(), 
	* the result can be passed directly to love.graphics.polygon().
	**/
	class PolygonShape : public Shape
	{
	public:

		/**
		* Create a new PolygonShape from the parent Body and
		* a Box2D polygon definition.
		* @param body The parent Body. 
		* @param def The polygon definition.
		**/
		PolygonShape(boost::shared_ptr<Body> body, b2PolygonDef * def);

		virtual ~PolygonShape();

		/**
		* Returns the transformed points of the polygon.
		* This function is useful for debug drawing and such.
		*
		* The result can be directly passed into love.graphics.polygon().
		**/
		int getPoints(lua_State * L);
	};

	typedef boost::shared_ptr<PolygonShape> pPolygonShape;

} // love_box2d

#endif // LOVE_BOX2D_POLYGON_SHAPE_H
