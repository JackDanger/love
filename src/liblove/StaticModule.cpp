#include <love/StaticModule.h>

// STD
#include <iostream>

namespace love
{
	StaticModule::StaticModule(fptr_init init, fptr_quit quit, fptr_open open)
	{
		module_init = init;
		module_quit = quit;
		module_open = open;
	}

	StaticModule::~StaticModule()
	{
		unload();
	}

	bool StaticModule::load()
	{
		if(module_init == 0 || module_quit == 0 || module_open == 0)
		{
			std::cerr << "Standard module functions not set." << std::endl;
			return false;
		}
		return true;
	}

	void StaticModule::unload()
	{
	}

} // love
