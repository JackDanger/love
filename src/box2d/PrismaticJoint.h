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

// Module
#include "Joint.h"

namespace love_box2d
{
	/**
	* PrismaticJoints allow shapes to move in relation to eachother
	* along a defined axis.
	**/
	class PrismaticJoint : public Joint
	{
	private:

		// The Box2D prismatic joint object.
		b2PrismaticJoint * joint;

	public:

		/**
		* Creates a new PrismaticJoint connecting body1 and body2.
		**/
		PrismaticJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, b2PrismaticJointDef * def);

		virtual ~PrismaticJoint();

		/**
		* Get the current joint translation, usually in meters.
		**/
		float getTranslation() const;

		/**
		* Get the current joint translation speed, usually in meters per second.
		**/
		float getSpeed() const;

		/**
		* Enable/disable the joint motor.
		**/
		void setMotorEnabled(bool motor);

		/**
		* Checks whether the motor is enabled.
		**/
		bool isMotorEnabled() const;

		/**
		* Set the maximum motor force, usually in N.
		**/
		void setMaxMotorForce(float force);

		/**
		* Get the current motor force, usually in N.
		**/
		float getMaxMotorForce() const;

		/**
		* Set the motor speed, usually in meters per second.
		**/
		void setMotorSpeed(float speed);

		/**
		* Get the motor speed, usually in meters per second.
		**/
		float getMotorSpeed() const;

		/**
		* Get the current motor force, usually in N.
		**/
		float getMotorForce() const;

		/**
		* Enable/disable the joint limit.
		**/
		void setLimitsEnabled(bool limit);

		/**
		* Checks whether limits are enabled.
		**/
		bool isLimitsEnabled() const;

		/**
		* Sets the upper limit, usually in meters.
		**/
		void setUpperLimit(float limit);

		/**
		* Sets the lower limit, usually in meters.
		**/
		void setLowerLimit(float limit);

		/**
		* Sets the limits, usually in meters.
		**/
		void setLimits(float lower, float upper);

		/**
		* Gets the lower limit, usually in meters.
		**/
		float getLowerLimit() const;

		/**
		* Gets the upper limit, usually in meters.
		**/
		float getUpperLimit() const;
		
		/**
		* Gets the limits, usually in meters.
		* @returns The upper limit.
		* @returns The lower limit.
		**/
		int getLimits(lua_State * L);
		
	};

	typedef boost::shared_ptr<PrismaticJoint> pPrismaticJoint;

} // love_box2d

#endif // LOVE_BOX2D_PRISMATIC_JOINT_H
