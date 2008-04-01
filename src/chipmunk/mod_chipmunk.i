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
%include Space.i
%include Body.i
%include Shape.i

namespace love_chipmunk
{
	pSpace newSpace();
	pBody newBody(pSpace space, float x, float y, float m, float i);
	pShape newCircle(pSpace space, pBody body, float radius);	
}

