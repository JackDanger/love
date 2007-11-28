#include "Resource.h"
#include "AbstractFile.h"

namespace love
{

	Resource::Resource()
	{
	}

	Resource::Resource(pAbstractFile file) : file(file)
	{
	}

}// love
