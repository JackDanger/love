/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-03-21
*/

#ifndef LOVE_CHIPMUNK_BODY_H
#define LOVE_CHIPMUNK_BODY_H

// STD
#include <list>

// love_chipmunk
#include "Vector.h"
#include "Space.h"
#include "Shape.h"
#include "Joint.h"

// Boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{
	class Body
	{
		friend class Shape;
		friend class CircleShape;
		friend class SegmentShape;
		friend class PolygonShape;
		friend class Joint;
		friend class PinJoint;
		friend class SlideJoint;
		friend class PivotJoint;
		friend class GrooveJoint;
	protected:
		// The space this body is added to.
		pSpace space;

		// The chipmunk body.
		cpBody * body;		

		// The list of joints and shapes associated 
		// with this body.
		std::list<pShape> shapes;
		std::list<pJoint> joints;

		bool dynamic;
	public:

		Body(pSpace space, float x, float y, float m, float i, bool dynamic = true);
		virtual ~Body();

		cpBody * get();

		void addShape(pShape s);
		void removeShape(pShape s);
		void addJoint(pJoint j);
		void removeJoint(pJoint j);

		bool isDynamic() const;

		float getX();
		float getY();
		float getAngle();

		void setMass(float m);
		void setMoment(float m);
		void setAngle(float a);
		void applyImpulse(float jx, float jy, float rx, float ry);
		void applyForce(float fx, float fy, float rx, float ry);
		void resetForces();

		void dampedSpring(boost::shared_ptr<Body> & b, const pVector & anchr1, 
			const pVector & anchr2, float rlen, float k, float dmp, float dt);

	}; // Body

	typedef boost::shared_ptr<Body> pBody;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_BODY_H
