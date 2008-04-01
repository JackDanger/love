/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_CHIPMUNK_SHAPE_H
#define LOVE_CHIPMUNK_SHAPE_H

#include "Space.h"

// Boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{
	/**
	 * @author Anders Ruud
	 * @date 2008-03-21
	 **/
	class Shape
	{
		friend class Body;
	private:
		pSpace space;
		cpShape * shape;
	public:

		Shape(pSpace space, cpShape * shape);
		virtual ~Shape();

		void setCollisionType(unsigned long type);
		unsigned long getCollisionType() const;
		void setGroup(unsigned long group);
		unsigned long getGroup() const;
		void setLayers(unsigned long layers);
		unsigned long getLayers() const;

		void setElasticity(float e);
		float getElasticity() const;
		void setFriction(float u);
		float getFriction() const;
		void setSurfaceVelocity(float x, float y);

	}; // Shape

	typedef boost::shared_ptr<Shape> pShape;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_SHAPE_H
