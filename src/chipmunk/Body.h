/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_CHIPMUNK_BODY_H
#define LOVE_CHIPMUNK_BODY_H

#include "Space.h"
#include "Shape.h"

#include <list>

// Boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{
	/**
	 * @author Anders Ruud
	 * @date 2008-03-21
	 **/
	class Body
	{
		friend class Shape;
	private:
		pSpace space;
		cpBody * body;
		std::list<pShape> shapes;
	public:

		Body(pSpace space, float x, float y, float m, float i);
		~Body();

		cpBody * get();
		void add(pShape shape);
		void remove(const pShape & shape);

		float getX();
		float getY();
		float getAngle();

		void setMass(float m);
		void setMoment(float m);
		void setAngle(float a);
		void applyImpulse(float jx, float jy, float rx, float ry);
		void applyForce(float fx, float fy, float rx, float ry);
		void resetForces();

	}; // Body

	typedef boost::shared_ptr<Body> pBody;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_BODY_H
