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
	/**
	* A CircleShape represent a Circle which can 
	* be used for collision detection and physics.
	* 
	* The CircleShape is much faster than the PolygonShape, 
	* and should generally be used where possible.
	**/
	class CircleShape : public Shape
	{
	private:
		// The radius of the circle. We need to store this because
		// Box2D has no built-in method for getting the radius.
		float radius;
	public:
		
		/**
		* Create a new CircleShape from the parent body and a 
		* Box2D CircleShape definition.
		* @param body The parent body.
		* @param def The CircleShape definition.
		**/
		CircleShape(boost::shared_ptr<Body> body, b2CircleDef * def);

		virtual ~CircleShape();

		/**
		* Gets the radius for the circle.
		**/
		float getRadius() const;

		// There is no support for setting the radius.
	};

	typedef boost::shared_ptr<CircleShape> pCircleShape;

} // love_box2d

#endif // LOVE_BOX2D_CIRCLE_SHAPE_H
