#include "Resource.h"

namespace love 
{

	Resource::Resource()
	{
	}

	Resource::~Resource()
	{
	}

	string Resource::getFilename()
	{
		return this->filename;
	}

}