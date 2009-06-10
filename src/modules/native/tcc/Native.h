/**
* Copyright (c) 2006-2009 LOVE Development Team
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
**/

#ifndef LOVE_NATIVE_TCC_NATIVE_H
#define LOVE_NATIVE_TCC_NATIVE_H

// C++
#include <vector>

// tcc
#include "libtcc/libtcc.h"

// LOVE
#include "../../../common/Module.h"

namespace love
{
namespace native
{
namespace tcc
{

	class Native : public Module
	{
	private:

		// The tcc state.
		TCCState * state;

		// Space for relocating. Using vector to support
		// multiple relocations.
		std::vector<void *> buffers;		

	public:

		/**
		* Constructor.
		**/
		Native();

		/**
		* Destructor.
		**/
		~Native();

		/**
		* Gets the name of the module.
		* @return Always returns "love.native.tcc".
		**/
		const char * getName() const;

		bool compile(const char * str);

		bool relocate();

		void * getSymbol(const char * sym);


	}; // Native

} // tcc
} // native
} // love

#endif // LOVE_NATIVE_TCC_NATIVE_H
