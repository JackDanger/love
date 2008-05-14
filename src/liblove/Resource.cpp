#include <love/Resource.h>

namespace love
{

	Resource::Resource(pFile file) : file(file)
	{
	}

	Resource::~Resource()
	{
	}

	bool Resource::reload()
	{
		unload();
		return load();
	}

}// love
