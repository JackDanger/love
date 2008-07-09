/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-03-21
*/

#ifndef LOVE_CHIPMUNK_SPACE_H
#define LOVE_CHIPMUNK_SPACE_H

// Boost
#include <boost/shared_ptr.hpp>

// Chipmunk
#include "chipmunk/chipmunk.h"

namespace love_chipmunk
{
	class Space
	{
		friend class Body;
		friend class Shape;
		friend class SegmentShape;
		friend class PolygonShape;
		friend class CircleShape;
		friend class SegmentShape;

	private:
		cpSpace * space;
	public:

		Space();
		~Space();

		void update(float dt);

		void setGravity(float x, float y);
		void setGravity(float y);
		void setDamping(float d);

		void resizeStaticHash(float dim, int count);
		void resizeActiveHash(float dim, int count);


	}; // Space

	typedef boost::shared_ptr<Space> pSpace;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_SPACE_H
