#include "Filesystem.h"

using std::string;

namespace love
{

	Filesystem::Filesystem()
	{
	}

	Filesystem::~Filesystem()
	{
	}

	const string & Filesystem::getBase() const
	{
		return base;
	}

	const string & Filesystem::getUser() const
	{
		return user;
	}



}// love
