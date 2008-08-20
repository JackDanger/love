/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-12
*/
#ifndef LOVE_BOX2D_PRISMATIC_JOINT_H
#define LOVE_BOX2D_PRISMATIC_JOINT_H

#include "Joint.h"

namespace love_box2d
{
	/**
	* PrismaticJoints allow shapes to move in relation to eachother
	* along a any axis.
	**/
	class PrismaticJoint : public Joint
	{
	private:
		b2PrismaticJoint * joint;
	public:
		PrismaticJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, b2PrismaticJointDef * def);
		virtual ~PrismaticJoint();

		float getTranslation() const;
		float getSpeed() const;

		void setMotorEnabled(bool motor);
		bool isMotorEnabled() const;
		void setMaxMotorForce(float force);
		float getMaxMotorForce() const;
		void setMotorSpeed(float speed);
		float getMotorSpeed() const;
		float getMotorForce() const;

		void setLimitsEnabled(bool limit);
		bool isLimitsEnabled() const;
		void setUpperLimit(float limit);
		void setLowerLimit(float limit);
		void setLimits(float lower, float upper);
		float getLowerLimit() const;
		float getUpperLimit() const;
		int getLimits(lua_State * L);
		
	};

	typedef boost::shared_ptr<PrismaticJoint> pPrismaticJoint;

} // love_box2d

#endif // LOVE_BOX2D_PRISMATIC_JOINT_H
