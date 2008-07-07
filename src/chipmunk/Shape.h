/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-03-21
*/

#ifndef LOVE_CHIPMUNK_SHAPE_H
#define LOVE_CHIPMUNK_SHAPE_H

// love_chipmunk
#include "chipmunk/chipmunk.h"

// love
#include <love/constants.h>

// Boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{

	class Body;

	class Shape 
	{
		friend class Body;
	protected:
		cpShape * shape;
		boost::shared_ptr<Body> body;
	public:

		Shape(boost::shared_ptr<Body> body);
		virtual ~Shape();
	
		void remove();

		void setType(unsigned long type);
		unsigned long getType() const;
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
