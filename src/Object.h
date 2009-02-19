/**
* LOVE -- Free 2D Game Engine
* Version $(DOC_VERSION), $(DOC_DATE)
* 
* Copyright (c) 2006-$(DOC_YEAR) LOVE Development Team
* 
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software. If you use this software
*    in a product, an acknowledgment in the product documentation would be
*    appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 
* -- LOVE Development Team, http://love2d.org
**/

#ifndef LOVE_OBJECT_H
#define LOVE_OBJECT_H

namespace love
{
	/**
	* Superclass for all object that should be able to 
	* cross the Lua/C border (this pertains to most objects).
	*
	* This class is an alternative to using smart pointers;
	* it contains retain/release methods, and will delete
	* itself with the reference count hits zero.
	* 
	* The wrapper code assumes that all userdata inherits from
	* this class.
	**/
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
