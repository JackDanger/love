/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-07-06
*/


#ifndef LOVE_CHIPMUNK_SEGMENT_SHAPE_H
#define LOVE_CHIPMUNK_SEGMENT_SHAPE_H

// love_chipmunk
#include "Shape.h"
#include "Vector.h"

// Boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{
	// Forward declarations.
	class Body;

	class SegmentShape : public Shape
	{
	protected:
		cpSegmentShape * segmentShape;
	public:

		SegmentShape(boost::shared_ptr<Body> body, cpVect v1, cpVect v2);
		virtual ~SegmentShape();
		int getPoints(lua_State * L);

	}; // SegmentShape

	typedef boost::shared_ptr<SegmentShape> pSegmentShape;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_SEGMENT_SHAPE_H
