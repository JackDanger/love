#include "love_version.h"

// STD
#include <sstream>

namespace love
{
	std::string version_string()
	{
		std::stringstream ss;
		ss << LOVE_MAJOR_VERSION;
		ss << ".";
		ss << LOVE_MINOR_VERSION;
		ss << ".";
		ss << LOVE_REVISION;
		return ss.str();
	}
}

