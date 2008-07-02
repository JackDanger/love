#include <love/Module.h>

namespace love
{
	Module::Module() 
		: module_init(0), module_quit(0), module_open(0)
	{
	}

	Module::~Module()
	{
	}

} // love
