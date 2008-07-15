/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-07-14
*/

#ifndef LOVE_CHIPMUNK_PIVOT_JOINT_H
#define LOVE_CHIPMUNK_PIVOT_JOINT_H

// love_chipmunk
#include "Joint.h"

namespace love_chipmunk
{
	int _PivotJoint_getPoint(lua_State * L);

	class PivotJoint : public Joint
	{
		friend int _PivotJoint_getPoint(lua_State * L);
	protected:
		cpPivotJoint * pivotJoint;
	public:

		PivotJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, 
			cpVect pivot);
		virtual ~PivotJoint();
	}; // PivotJoint

	typedef boost::shared_ptr<PivotJoint> pPivotJoint;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_PIVOT_JOINT_H
