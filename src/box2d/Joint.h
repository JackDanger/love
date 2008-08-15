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

	class Body;
	class World;

	class Joint
	{
	private:
		boost::shared_ptr<Body> body1, body2;
		boost::shared_ptr<World> world;
		b2Joint * joint;
	public:
		Joint(boost::shared_ptr<Body> body1);
		Joint(boost::shared_ptr<Body> body1, boost::shared_ptr<Body> body2);
		virtual ~Joint();
		int getType() const;

		int getAnchors(lua_State * L);
		int getReactionForce(lua_State * L);

		float getReactionTorque();

		void setCollideConnected(bool collide);
		bool getCollideConnected() const;

	protected:
		b2Joint * createJoint(b2JointDef * def);
		void destroyJoint(b2Joint * joint);
	};

	typedef boost::shared_ptr<Joint> pJoint;

} // love_box2d

#endif // LOVE_BOX2D_JOINT_H
