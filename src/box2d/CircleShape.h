/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-08
*/
#ifndef LOVE_BOX2D_CIRCLE_SHAPE_H
#define LOVE_BOX2D_CIRCLE_SHAPE_H

// Module
#include "Shape.h"

namespace love_box2d
{
	class CircleShape : public Shape
	{
	private:
		float radius;
	public:
		CircleShape(boost::shared_ptr<Body> body, b2CircleDef * def);
		virtual ~CircleShape();
		float getRadius() const;
	};

	typedef boost::shared_ptr<CircleShape> pCircleShape;

} // love_box2d

#endif // LOVE_BOX2D_CIRCLE_SHAPE_H
