%module love_openal

%{
#include <boost/shared_ptr.hpp>
#include "love_openal.h"
using namespace love_openal;
%}

// Wrap boost::shared_ptr.
namespace boost {
  template<class T> class shared_ptr
  {
    public:
      T * operator-> () const;
  };
}

namespace love_openal
{
}

%luacode{
love.audio = mod_openal
}
