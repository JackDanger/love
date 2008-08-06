/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development
*  
* @author Anders Ruud
* @date 2008-08-06
*/

#ifndef LOVE_REFERENCE_H
#define LOVE_REFERENCE_H

// boost
#include <boost/shared_ptr.hpp>

// LOVE
#include "luax.h"

namespace love
{
	class Reference
	{
	private:
		lua_State * L;
		int ref;
	public:
		static const char * TABLE;
		Reference(lua_State * L, int idx);
		~Reference();
		void push();
	};

	typedef boost::shared_ptr<Reference> pReference;

} // love

#endif // LOVE_REFERENCE_H
