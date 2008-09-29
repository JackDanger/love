#include <love/Module.h>

namespace love
{
	Module::Module(fptr_core init, fptr_core quit, fptr_core open) 
		: init(init), quit(quit), open(open)
	{
	}

	Module::~Module()
	{
	}

} // love
