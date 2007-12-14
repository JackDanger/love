#include "AbstractAudio.h"

#include "Core.h"
#include "love.h"
#include "AbstractFileSystem.h"

using std::string;

namespace love
{
	
	AbstractAudio::AbstractAudio()
	{
	}
	
	AbstractAudio::~AbstractAudio()
	{
	}

	pAbstractSound AbstractAudio::getSound(const string & filename) const
	{
		pAbstractFile file = core->filesystem->getBaseFile(filename);
		return getSound(file);
	}

	pAbstractMusic AbstractAudio::getMusic(const string & filename) const
	{
		pAbstractFile file = core->filesystem->getBaseFile(filename);
		return getMusic(file);
	}
	
} // love
