#include <love/version.h>

// STD
#include <cstring>

namespace love
{

	bool is_compatible(const char * version_str)
	{
		// Return true if it's made for any version.
		if((strcmp(version_str, "any") == 0))
			return true;
		
		char compat [] = LOVE_VERSION_COMPATIBILITY;

		// Get first token.
		char * tok = strtok(compat, " ");

		// Check first token.
		if(strcmp(tok, version_str) == 0) 
			return true;
		while (tok != 0)
		{
			if(strcmp(tok, version_str) == 0) 
				return true;
			tok = strtok (0, " ");
		}

		return false;
	}

} // love
