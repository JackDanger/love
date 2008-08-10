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

namespace love_box2d
{
	pWorld newWorld(float lx, float ly, float ux, float uy, float gx, float gy, bool sleep);
	pBody newBody(pWorld world, float x, float y, float mass);
	pCircleShape newCircle(pBody body, float x, float y, float radius);
	pCircleShape newCircle(pBody body, float radius);
}

%native(newPolygon) int love_box2d::newPolygon(lua_State * L);

%luacode {
love.physics = mod_box2d
}