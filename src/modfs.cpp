#include "modfs.h"

namespace love_mod
{
	// The currently active filesystem. This is used
	// by load/unload to manage files and MUST be set 
	// for those functions to do anything.
	Filesystem * filesystem = 0;
	
	void setFilesystem(Filesystem * f)
	{
		filesystem = f;
	}

	bool load(love::pFile & f)
	{
		if(filesystem == 0)
			return false;
		return filesystem->load(f);
	}

	bool unload(love::pFile & f)
	{
		if(filesystem == 0)
			return false;
		return filesystem->unload(f);
	}

	love::pFile newFile( const char * filename )
	{
		love::pFile f(new love::File(std::string(filename)));
		return f;
	}

} // love_mod

// That's right, we're including cpp-files here,
// to avoid oversaturation of make- and project files.
#include "mod.cpp"
#include "File.cpp"
#include "Resource.cpp"
#include "MemoryFile.cpp"
