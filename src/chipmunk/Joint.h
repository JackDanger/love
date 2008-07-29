/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-07-14
*/

#ifndef LOVE_CHIPMUNK_JOINT_H
#define LOVE_CHIPMUNK_JOINT_H

// love_chipmunk
#include "chipmunk/chipmunk.h"

// love
#include <love/mod.h>
#include <love/constants.h>

// Boost
#include <boost/shared_ptr.hpp>

namespace love_chipmunk
{

	class Body;

	class Joint 
	{
		friend class Body;
	protected:
		cpJoint * joint;
		boost::shared_ptr<Body> body1, body2;
		int jointType;
	public:

		Joint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, int jointType);
		virtual ~Joint();
		virtual int getJointType() const;
	}; // Joint

	typedef boost::shared_ptr<Joint> pJoint;

} // love_chipmunk

#endif // LOVE_CHIPMUNK_JOINT_H
