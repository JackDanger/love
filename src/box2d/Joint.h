/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-12
*/
#ifndef LOVE_BOX2D_JOINT_H
#define LOVE_BOX2D_JOINT_H

// LOVE
#include <love/mod.h>

// Boost
#include <boost/shared_ptr.hpp>

// Box2D
#include <Box2D.h>

namespace love_box2d
{

	// Forward declarations.
	class Body;
	class World;

	/**
	* A Joint acts as positioning constraints on Bodies. 
	* A Joint can be used to prevent Bodies from going to 
	* far apart, or coming too close together.
	**/
	class Joint
	{
	private:
		
		// A Joint must be destroyed *before* the bodies it acts upon, 
		// and the world they reside in. We therefore need shared_ptrs
		// parents and associations to prevent wrong destruction order.
		boost::shared_ptr<Body> body1, body2;
		boost::shared_ptr<World> world;

		// The Box2D joint object.
		b2Joint * joint;

	public:

		/**
		* This constructor will connect one end of the joint to body1, 
		* and the other one to the default ground body.
		* 
		* This constructor is mainly used by MouseJoint.
		**/
		Joint(boost::shared_ptr<Body> body1);

		/**
		* Create a joint between body1 and body2.
		**/
		Joint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2);

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

	typedef boost::shared_ptr<Joint> pJoint;

} // love_box2d

#endif // LOVE_BOX2D_JOINT_H
