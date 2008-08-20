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

// Module
#include "Joint.h"

namespace love_box2d
{
	/**
	* The DistanceJoint keeps Bodies at a fixed distance 
	* from eachother.
	**/
	class DistanceJoint : public Joint
	{
	private:
		// The Box2D DistanceJoint object.
		b2DistanceJoint * joint;
	public:

		/**
		* Creates a DistanceJoint connecting body1 to body2. 
		**/
		DistanceJoint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2, b2DistanceJointDef * def);

		virtual ~DistanceJoint();

		/**
		* Sets the equilibrium distance between the two bodies.
		**/
		void setLength(float length);

		/**
		* Gets the equilibrium distance between the two bodies.
		**/
		float getLength() const;

		/**
		* Sets the response speed.
		**/
		void setFrequency(float hz);

		/**
		* Gets the response speed.
		**/
		float getFrequency() const;

		/**
		* Sets the damping ratio.
		* 0 = no damping, 1 = critical damping.
		**/
		void setDamping(float d);

		/**
		* Gets the damping ratio.
		* 0 = no damping, 1 = critical damping.
		**/
		float getDamping() const;

	};

	typedef boost::shared_ptr<DistanceJoint> pDistanceJoint;

} // love_box2d

#endif // LOVE_BOX2D_DISTANCE_JOINT_H
