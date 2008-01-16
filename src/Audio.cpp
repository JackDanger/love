#include "Audio.h"

// LOVE
#include "using_filesystem.h"

using std::string;

namespace love
{
	
	Audio::~Audio()
	{
	}

	pSound Audio::getSound(const string & filename) const
	{
		pFile file = filesystem->getBaseFile(filename);
		return getSound(file);
	}

	pMusic Audio::getMusic(const string & filename) const
	{
		pFile file = filesystem->getBaseFile(filename);
		return getMusic(file);
	}

} // love
