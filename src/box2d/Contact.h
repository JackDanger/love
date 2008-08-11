/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* @author Anders Ruud
* @date 2008-08-10
*/
#ifndef LOVE_BOX2D_CONTACT_H
#define LOVE_BOX2D_CONTACT_H

// LOVE
#include <love/mod.h>

// Boost
#include <boost/shared_ptr.hpp>

// Box2D
#include <Box2D.h>

namespace love_box2d
{
	class Contact
	{
		friend class World;
	private:
		b2ContactPoint point;
	public:
		Contact(const b2ContactPoint * point);
		~Contact();
		int getPosition(lua_State * L);
		int getVelocity(lua_State * L);
		int getNormal(lua_State * L);
		float getSeparation() const;
		float getFriction() const;
		float getRestitution() const;
	};

	typedef boost::shared_ptr<Contact> pContact;

} // love_box2d

#endif // LOVE_BOX2D_CONTACT_H
