/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-08
*/
#ifndef LOVE_BOX2D_BODY_H
#define LOVE_BOX2D_BODY_H

// LOVE
#include <love/mod.h>

// Boost
#include <boost/shared_ptr.hpp>

// Box2D
#include <Box2D.h>

namespace love_box2d
{
	class World;

	class Body
	{
		friend class Joint;
		friend class DistanceJoint;
		friend class MouseJoint;
		friend class CircleShape;
		friend class PolygonShape;
	private:
		boost::shared_ptr<World> world;
		
	public:
		b2Body * body;
		Body(boost::shared_ptr<World> world, b2Vec2 p, float m);
		~Body();

		float getX();
		float getY();
		float getAngle();

		int getPosition(lua_State * L);
		int getWorldCenter(lua_State * L);
		int getLocalCenter(lua_State * L);

		float getSpin() const;
		float getMass() const;
		float getInertia() const;
		float getAngularDamping() const;
		float getDamping() const;

		void applyImpulse(float jx, float jy);
		void applyImpulse(float jx, float jy, float rx, float ry);
		void applyTorque(float t);
		void applyForce(float fx, float fy, float rx, float ry);
	
		void setX(float x);
		void setY(float y);
		void setVelocity(float x, float y);
		void setAngle(float d);
		void setSpin(float r);
		void setPosition(float x, float y);
		void setMassFromShapes();
		void setMass(float x, float y, float m, float i);
		void setAngularDamping(float d);
		void setDamping(float d);

		int getWorldPoint(lua_State * L);
		int getWorldVector(lua_State * L);
		int getLocalPoint(lua_State * L);
		int getLocalVector(lua_State * L);
		int getVelocityWorldPoint(lua_State * L);
		int getVelocityLocalPoint(lua_State * L);

		bool isBullet() const;
		void setBullet(bool bullet);
		bool isStatic() const;
		bool isDynamic() const;
		bool isFrozen() const;
		bool isSleeping() const;

		void setAllowSleep(bool allow);
		void setSleep(bool sleep);
	private:
		b2Vec2 getVector(lua_State * L);
		int pushVector(lua_State * L, const b2Vec2 & v);
	};

	typedef boost::shared_ptr<Body> pBody;

} // love_box2d

#endif // LOVE_BOX2D_BODY_H
