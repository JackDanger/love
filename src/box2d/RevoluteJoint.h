/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-12
*/
#ifndef LOVE_BOX2D_REVOLUTE_JOINT_H
#define LOVE_BOX2D_REVOLUTE_JOINT_H

// Module
#include "Joint.h"

namespace love_box2d
{
	/**
	* A RevoluteJoint allows two bodies relative rotation
	* around a single point.
	**/
	class RevoluteJoint : public Joint
	{
	private:

		// The Box2D revolute joint object.
		b2RevoluteJoint * joint;

	public:

		/**
		* Creates a new RevoluteJoint connecting body1 and body2.
		**/
		RevoluteJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, b2RevoluteJointDef * def);
		
		virtual ~RevoluteJoint();

		/**
		* Get the current joint angle in degrees.
		**/
		float getAngle() const;

		/**
		* Get the current joint angle speed in degrees per second.
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
		* Set the maximum motor torque, usually in N-m.
		**/
		void setMaxMotorTorque(float torque);

		/**
		* Gets the maximum motor torque, usually in N-m.
		**/
		float getMaxMotorTorque() const;

		/**
		* Sets the motor speed in degrees per second.
		**/
		void setMotorSpeed(float speed);

		/**
		* Gets the motor speed in degrees per second.
		**/
		float getMotorSpeed() const;

		/**
		* Get the current motor torque, usually in N-m.
		**/
		float getMotorTorque() const;

		/**
		* Enable/disable the joint limit.
		**/
		void setLimitsEnabled(bool limit);

		/**
		* Checks whether limits are enabled.
		**/
		bool isLimitsEnabled() const;

		/**
		* Sets the upper limit in degrees.
		**/
		void setUpperLimit(float limit);

		/**
		* Sets the lower limit in degrees.
		**/
		void setLowerLimit(float limit);

		/**
		* Sets the limits in degrees.
		**/
		void setLimits(float lower, float upper);

		/**
		* Gets the lower limit in degrees.
		**/
		float getLowerLimit() const;

		/**
		* Gets the upper limit in degrees.
		**/
		float getUpperLimit() const;
		
		/**
		* Gets the limits in degrees.
		* @returns The lower limit.
		* @returns The upper limit.
		**/
		int getLimits(lua_State * L);

	};

	typedef boost::shared_ptr<RevoluteJoint> pRevoluteJoint;

} // love_box2d

#endif // LOVE_BOX2D_REVOLUTE_JOINT_H
