#include "AbstractFileSystem.h"
#include "AbstractFile.h"

namespace love
{

	AbstractFileSystem::AbstractFileSystem()
	{
	}

	AbstractFileSystem::~AbstractFileSystem()
	{
	}

	const string & AbstractFileSystem::getBase() const
	{
		return base;
	}

	const string & AbstractFileSystem::getUser() const
	{
		return user;
	}



}// love
