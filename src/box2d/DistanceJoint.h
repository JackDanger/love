/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-12
*/
#ifndef LOVE_BOX2D_DISTANCE_JOINT_H
#define LOVE_BOX2D_DISTANCE_JOINT_H

#include "Joint.h"

namespace love_box2d
{
	class DistanceJoint : public Joint
	{
	private:
		b2DistanceJoint * joint;
	public:
		DistanceJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, b2DistanceJointDef * def);
		virtual ~DistanceJoint();
		void setLength(float length);
		float getLength() const;
	};

	typedef boost::shared_ptr<DistanceJoint> pDistanceJoint;

} // love_box2d

#endif // LOVE_BOX2D_DISTANCE_JOINT_H
