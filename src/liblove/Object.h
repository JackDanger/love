/**
* LOVE: Free 2D Game Engine
* Website: http://love2d.org
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
* 
* Superclass for all object that should be able to 
* cross the Lua/C border (this pertains to most objects).
*
* This class is an alternative to using smart pointers;
* it contains retain/release methods, and will delete
* itself with the reference count hits zero.
* 
* The wrapper code assumes that all userdata inherits from
* this class.
* 
* @author Anders Ruud
* @date 2008-10-30
**/

#ifndef LOVE_OBJECT_H
#define LOVE_OBJECT_H

namespace love
{
	class Object
	{
	private:
		int count;
	public:
		Object();
		virtual ~Object();
		int refcount() const;
		void retain();
		void release();
	};

} // love

#endif // LOVE_OBJECT_H
