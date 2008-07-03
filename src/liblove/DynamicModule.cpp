#include <love/DynamicModule.h>

// STD
#include <iostream>

// SDL
#include <SDL_loadso.h>

// LOVE
#include <love/platform.h>
#include <love/Exception.h>

#if defined(LOVE_LINUX)
#define LOVE_MOD_PATH "/usr/lib/love"
#endif

namespace love
{
	DynamicModule::DynamicModule(std::string name)
		: name(name), handle(0)
	{
	}

	DynamicModule::~DynamicModule()
	{
		unload();
	}

	bool DynamicModule::load()
	{
		// Get the module from SDL.
		handle = SDL_LoadObject(name.c_str());

#ifdef LOVE_MOD_PATH
		// This code means that /usr/lib/love/<module> will be tried
		// first on Linux. If that fails, it will try the relative filename.
		if(handle == 0)
		{
			std::string mod_path(LOVE_MOD_PATH);
			mod_path += name;
			handle = SDL_LoadObject(mod_path.c_str());	
		}
#endif

		if(handle == 0) 
		{
			std::cerr << "Loading of module failed. " << SDL_GetError() << std::endl;
			return false;
		}

		try
		{
			// Try to load the standard set of functions. If one
			// of these fail, the whole module fail.
			module_init = (fptr_init)getf("module_init");
			module_quit = (fptr_quit)getf("module_quit");
			module_open = (fptr_open)getf("module_open");
		}
		catch(Exception e)
		{
			std::cerr << e.msg() << std::endl;
			return false;
		}

		return true;
	}

	void DynamicModule::unload()
	{
		// Unload it with SDL.
		if(handle != 0)
			SDL_UnloadObject(handle);

		handle = 0;
	}

	void * DynamicModule::getf(const std::string & name)
	{
		// Check that the module is attached.
		if( handle == 0)
			throw Exception("Could not load function " + this->name + ":" + name + ". DynamicModule is not loaded.");

		// We might have this function already.
		std::map<std::string, void *>::const_iterator i = functions.find(name);
		if( i != functions.end() )
			return i->second;

		// Return the function. The caller must check that the pointer is valid.
		void * fptr = SDL_LoadFunction(handle, name.c_str());

		if (fptr == 0)
			throw Exception("Could not load function " + this->name + ":" + name + ": Function does not exist.");
		else
			functions[name] = fptr; // Add to function map.

		return fptr;
	}
}
