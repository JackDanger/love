%module mod_chipmunk

%{
#include <boost/shared_ptr.hpp>
#include "love_chipmunk.h"
%}

// Wrap boost::shared_ptr.
namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}

// Order is important. No touching.
%include Vector.i
%include Space.i
%include Body.i
%include Shape.i

%include SegmentShape.i
%include PolygonShape.i

namespace love_chipmunk
{
	pSpace newSpace();
	pBody newBody(pSpace space, float x, float y, float m, float i);
	pBody newStaticBody(pSpace space, float x, float y, float m, float i);
	pShape newCircle(pBody body, float radius);
	pSegmentShape newSegment(pBody body, float x1, float y1, float x2, float y2);
}

//%native(newPolygon) int love_chipmunk::newPolygon(lua_State * L);

%luacode {
love.physics = mod_chipmunk
}