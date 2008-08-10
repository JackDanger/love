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

		void applyImpulse(float jx, float jy);
		void applyImpulse(float jx, float jy, float rx, float ry);
		void applyForce(float fx, float fy, float rx, float ry);
	
		void setX(float x);
		void setY(float y);
		void setPosition(float x, float y);
		void setMassFromShapes();
	};

	typedef boost::shared_ptr<Body> pBody;

} // love_box2d

#endif // LOVE_BOX2D_BODY_H
