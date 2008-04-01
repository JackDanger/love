#include "version.h"
#include "string.h"

namespace love
{
	bool is_compatible(const char * version_str)
	{
		if((strcmp(version_str, LOVE_VERSION_STR) == 0) ||
			(strcmp(version_str, "any") == 0))
		return true;

		return false;
	}

} // love