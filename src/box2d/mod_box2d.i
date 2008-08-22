%module mod_box2d

%{
#include <boost/shared_ptr.hpp>
#include "love_box2d.h"
%}

// Wrap boost::shared_ptr.
namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}

%include World.i

%include Body.i

%include Shape.i
%include CircleShape.i
%include PolygonShape.i

%include Contact.i

%include Joint.i
%include DistanceJoint.i
%include MouseJoint.i
%include RevoluteJoint.i
%include PrismaticJoint.i

namespace love_box2d
{
	pWorld newWorld(float lx, float ly, float ux, float uy, float gx, float gy, bool sleep);
	pWorld newWorld(float w, float h);
	pBody newBody(pWorld world, float x, float y, float m);
	pBody newBody(pWorld world, float x, float y);
	pBody newBody(pWorld world);
	pCircleShape newCircleShape(pBody body, float radius);
	pCircleShape newCircleShape(pBody body, float x, float y, float radius);
	
	pPolygonShape newRectangleShape(pBody body, float w, float h);
	pPolygonShape newRectangleShape(pBody body, float x, float y, float w, float h);
	pPolygonShape newRectangleShape(pBody body, float x, float y, float w, float h, float angle);
	
	pDistanceJoint newDistanceJoint(pBody body1, pBody body2, float x1, float y1, float x2, float y2);
	pMouseJoint newMouseJoint(pBody body, float x, float y);
	pRevoluteJoint newRevoluteJoint(pBody body1, pBody body2, float x, float y);
	pPrismaticJoint newPrismaticJoint(pBody body1, pBody body2, float x, float y, float ax, float ay);
}

%native(newPolygonShape) int love_box2d::newPolygonShape(lua_State * L);

%luacode {
love.physics = mod_box2d
}