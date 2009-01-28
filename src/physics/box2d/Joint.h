/*
* LOVE: Free 2D Game Engine.
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2009 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-12
*/
#ifndef LOVE_PHYSICS_BOX2D_JOINT_H
#define LOVE_PHYSICS_BOX2D_JOINT_H

// LOVE
#include "../../luax.h"
#include "../../Object.h"
#include "../../constants.h"

// Box2D
#include "Include/Box2D.h"

namespace love
{
namespace physics
{
namespace box2d
{
	// Forward declarations.
	class Body;
	class World;

	/**
	* A Joint acts as positioning constraints on Bodies. 
	* A Joint can be used to prevent Bodies from going to 
	* far apart, or coming too close together.
	**/
	class Joint : public Object
	{
	private:
		
		// A Joint must be destroyed *before* the bodies it acts upon, 
		// and the world they reside in. We therefore need shared_ptrs
		// parents and associations to prevent wrong destruction order.
		Body * body1, * body2;
		World * world;

		// The Box2D joint object.
		b2Joint * joint;

	public:

		/**
		* This constructor will connect one end of the joint to body1, 
		* and the other one to the default ground body.
		* 
		* This constructor is mainly used by MouseJoint.
		**/
		Joint(Body * body1);

		/**
		* Create a joint between body1 and body2.
		**/
		Joint(Body * body1, Body * body2);

		virtual ~Joint();

		/**
		* Gets the type of joint.
		**/
		int getType() const;

		/**
		* Gets the anchor positions of the Joint in world
		* coordinates. This is useful for debugdrawing the joint.
		**/
		int getAnchors(lua_State * L);

		/**
		* Gets the reaction force on body2 at the joint anchor.
		**/
		int getReactionForce(lua_State * L);

		/**
		* Gets the reaction torque on body2.
		**/
		float getReactionTorque();

		/**
		* Sets whether connected bodies should collide
		* or not. Default is false.
		**/
		void setCollideConnected(bool collide);

		/**
		* Gets whether connected bodies should collide
		* or not.
		**/
		bool getCollideConnected() const;

	protected:

		/**
		* Joints require pointers to a Box2D joint objects at
		* different polymorphic levels, which is why these function 
		* were created.
		**/

		/**
		* Creates a Joint, and ensures that the parent class
		* gets a copy of the pointer.
		**/
		b2Joint * createJoint(b2JointDef * def);

		/**
		* Destroys the joint. This function was created just to 
		* get some cinsistency.
		**/
		void destroyJoint(b2Joint * joint);
	};

} // box2d
} // physics
} // love

#endif // LOVE_PHYSICS_BOX2D_JOINT_H
