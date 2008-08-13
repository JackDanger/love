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

namespace love_box2d
{
	pWorld newWorld(float lx, float ly, float ux, float uy, float gx, float gy, bool sleep);
	pBody newBody(pWorld world, float x, float y, float mass);
	pCircleShape newCircle(pBody body, float x, float y, float radius);
	pCircleShape newCircle(pBody body, float radius);
	pDistanceJoint newDistanceJoint(pBody body1, pBody body2, float x1, float y1, float x2, float y2);
	pMouseJoint newMouseJoint(pBody body, float x, float y);
}

%native(newPolygon) int love_box2d::newPolygon(lua_State * L);

%luacode {
love.physics = mod_box2d
}