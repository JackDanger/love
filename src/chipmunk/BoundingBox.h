/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development
* 
* @author Anders Ruud
* @date 2008-07-05
*/

#ifndef LOVE_CHIPMUNK_BOUNDING_BOX_H
#define LOVE_CHIPMUNK_BOUNDING_BOX_H

// love_chipmunk
#include "Vector.h"

// Chipmunk
#include "chipmunk/chipmunk.h"

// boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{
	/**
	* Chipmunk vector wrapper.
	**/
	class BoundingBox
	{
	private:
		cpBB b;
	public:
		BoundingBox();
		BoundingBox(float l, float b, float r, float t);
		BoundingBox(cpBB b);
		bool intersects(const boost::shared_ptr<BoundingBox> & b) const;
		bool contains(const boost::shared_ptr<BoundingBox> & b) const;
		bool contains(const pVector & v) const;
		pVector clamp(const pVector & v) const;
		pVector wrap(const pVector & v) const;
	};

	typedef boost::shared_ptr<BoundingBox> pBoundingBox;

} //love_chipmunk

#endif// LOVE_CHIPMUNK_BOUNDING_BOX_H
