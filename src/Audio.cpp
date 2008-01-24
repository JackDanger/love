#include "Audio.h"

// LOVE
#include "using_filesystem.h"

using std::string;

namespace love
{
	
	Audio::~Audio()
	{
	}

	pSound Audio::newSound(const string & filename) const
	{
		pFile file = filesystem->newBaseFile(filename);
		return newSound(file);
	}

	pMusic Audio::newMusic(const string & filename) const
	{
		pFile file = filesystem->newBaseFile(filename);
		return newMusic(file);
	}

} // love
