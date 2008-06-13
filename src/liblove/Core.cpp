#include <love/Core.h>

// STD
#include <iostream>

// LOVE
#include <love/Exception.h>

namespace love
{

	Core::Core() : m_error(0)
	{
	}

	Core::~Core()
	{
		std::map<std::string, pModule>::const_iterator i = modules.begin();

		while(i != modules.end())
		{
			i->second->module_quit();
			i++;
		}
	}

	bool Core::insmod(int argc, char ** argv, const std::string & name, unsigned int provides)
	{
		// Create a new module.
		pModule m(new Module(name));

		// Load the shared library.
		if(!m->load())
			return false;

		// It's loaded, now add it to the map and the array 
		// (if applicable).
		if(provides < Module::COUNT)
			mptr[provides] = m;
		modules[name] = m;

		// Init the actual module.
		if(!m->module_init(argc, argv, this))
			return false;

		return true;
	}

	bool Core::insmod(int argc, char ** argv, const std::string & name)
	{
		return insmod(argc, argv, name, Module::CUSTOM);
	}

	void * Core::getf( const std::string & module, const std::string & name) const
	{
		// Check that module is loaded.
		std::map<std::string, pModule>::const_iterator i = modules.find(name);
		if( i == modules.end() )
			throw Exception("Could not load function " + name + ". Module isn't loaded.");

		return i->second->getf(name);
	}

	void * Core::getf( unsigned int module, const std::string & name) const
	{
		if( module >= Module::COUNT )
			throw Exception("Module does not exist.");

		// Check that module is loaded.
		if( mptr[module] == 0 )
			throw Exception("Could not load function " + name + ". Module isn't loaded.");

		return mptr[module]->getf(name);
	}

	bool Core::open(void * vm)
	{
		std::map<std::string, pModule>::const_iterator i = modules.begin();

		while(i != modules.end())
		{
			if(!i->second->module_open(vm))
				return false;
			i++;
		}
		return true;
	}

	void Core::error(const char * msg)
	{
		// Get the function pointer when called for
		// the first time.
		if(m_error == 0)
		{
			try
			{
				m_error = (void (*)(const char *))getf(Module::SYSTEM, "err");
			}
			catch(Exception e)
			{
				std::cerr << e.msg() << std::endl;	
				return;
			}
		}

		// Call the function.
		m_error(msg);

	}

} // love
