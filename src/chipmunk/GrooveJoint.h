/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-07-14
*/

#ifndef LOVE_CHIPMUNK_GROOVE_JOINT_H
#define LOVE_CHIPMUNK_GROOVE_JOINT_H

// love_chipmunk
#include "Joint.h"

namespace love_chipmunk
{

	int _GrooveJoint_getPoints(lua_State * L);

	class GrooveJoint : public Joint
	{
		friend int _GrooveJoint_getPoints(lua_State * L);
	protected:
		cpGrooveJoint * grooveJoint;
	public:

		GrooveJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, 
			cpVect groove_a, cpVect groove_b, cpVect anchr);
		virtual ~GrooveJoint();
	}; // GrooveJoint

	typedef boost::shared_ptr<GrooveJoint> pGrooveJoint;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_GROOVE_JOINT_H
