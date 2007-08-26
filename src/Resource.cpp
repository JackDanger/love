#include "Resource.h"
#include "AbstractFile.h"

namespace love
{

	Resource::Resource(AbstractFile * file) : file(file)
	{
	}

	Resource::~Resource()
	{
		if(file != 0)
			delete file;
	}


}// love
