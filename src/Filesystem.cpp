#include "Filesystem.h"
#include "Exception.h"

namespace love
{
	bool Filesystem::extra(const std::string & so)
	{
		try
		{
			load = getf<fptr_load>(so, "load");
			unload = getf<fptr_unload>(so, "unload");
			push = getf<fptr_bool>(so, "push");
			pop = getf<fptr_bool>(so, "pop");
			addDir = getf<fptr_addDir>(so, "addDir");
			addBase = getf<fptr_bool>(so, "addBase");
			exists = getf<fptr_exists>(so, "exists");
			getBaseDir = getf<fptr_str>(so, "getBaseDir");
			getLeaf = getf<fptr_getLeaf>(so, "getLeaf");
			setSaveDirectory = getf<fptr_setSaveDirectory>(so, "setSaveDirectory");

		}
		catch(Exception e)
		{
			std::cerr << e.msg() << std::endl;
			return false;
		}

		return true;
	}
}
