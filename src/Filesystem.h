/*
* LOVE: Totally Awesome 2D Gaming.
* Website: http://love.sourceforge.net
* Licence: ZLIB/libpng
* Copyright (c) 2006-2008 LOVE Development Team
*/

#ifndef LOVE_FILESYSTEM_H
#define LOVE_FILESYSTEM_H

// LOVE
#include "Module.h"
#include "File.h"

namespace love
{

	// Function pointer typedefs.
	typedef bool (*fptr_load)(pFile &);
	typedef bool (*fptr_unload)(pFile &);
	typedef void (*fptr_setLoad)(fptr_load);
	typedef bool (*fptr_addDir)(const std::string &);
	typedef bool (*fptr_exists)(const std::string &);
	typedef void (*fptr_getLeaf)(const std::string &, std::string &);
	typedef bool (*fptr_setSaveDirectory)(const std::string &);
	
	/**
	* Filesystem module interface.
	* @author Anders Ruud
	* @date 2008-03-15
	**/
	class Filesystem : public Module
	{
	public:

		// Member function pointers.
		fptr_load load;
		fptr_unload unload;
		fptr_bool push;
		fptr_bool pop;
		fptr_addDir addDir;
		fptr_bool addBase;
		fptr_exists exists;
		fptr_str getBaseDir;
		fptr_str getUserDir;
		fptr_getLeaf getLeaf;
		fptr_setSaveDirectory setSaveDirectory;

		// From Module
		bool extra(const std::string & so);

	}; 

} // love

#endif // LOVE_FILESYSTEM_H
