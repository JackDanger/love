/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-07-14
*/

#ifndef LOVE_CHIPMUNK_PIN_JOINT_H
#define LOVE_CHIPMUNK_PIN_JOINT_H

// love_chipmunk
#include "Joint.h"

namespace love_chipmunk
{

	int _PinJoint_getPoints(lua_State * L);

	class PinJoint : public Joint
	{
		friend int _PinJoint_getPoints(lua_State * L);
	protected:
		cpPinJoint * pinJoint;
	public:

		PinJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, 
			cpVect anchr1, cpVect anchr2);
		virtual ~PinJoint();
	}; // PinJoint

	typedef boost::shared_ptr<PinJoint> pPinJoint;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_PIN_JOINT_H
