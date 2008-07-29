/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-07-14
*/

#ifndef LOVE_CHIPMUNK_SLIDE_JOINT_H
#define LOVE_CHIPMUNK_SLIDE_JOINT_H

// love_chipmunk
#include "Joint.h"

namespace love_chipmunk
{
	int _SlideJoint_getPoints(lua_State * L);
	int _SlideJoint_getLimits(lua_State * L);

	class SlideJoint : public Joint
	{
		friend int _SlideJoint_getPoints(lua_State * L);
		friend int _SlideJoint_getLimits(lua_State * L);
	protected:
		cpSlideJoint * slideJoint;
	public:

		SlideJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, 
			cpVect anchr1, cpVect anchr2, float min, float max);
		virtual ~SlideJoint();
	}; // SlideJoint

	typedef boost::shared_ptr<SlideJoint> pSlideJoint;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_SLIDE_JOINT_H
