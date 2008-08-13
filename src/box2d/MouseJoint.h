/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-12
*/
#ifndef LOVE_BOX2D_MOUSE_JOINT_H
#define LOVE_BOX2D_MOUSE_JOINT_H

#include "Joint.h"

namespace love_box2d
{
	class MouseJoint : public Joint
	{
	private:
		b2MouseJoint * joint;
	public:
		MouseJoint(boost::shared_ptr<Body> body1, b2MouseJointDef * def);
		virtual ~MouseJoint();
		void setTarget(float x, float y);
	};

	typedef boost::shared_ptr<MouseJoint> pMouseJoint;

} // love_box2d

#endif // LOVE_BOX2D_MOUSE_JOINT_H
