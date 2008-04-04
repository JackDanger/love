#include "Module.h"

// SDL
#include <SDL_loadso.h>

// LOVE
#include "Exception.h"

namespace love
{

	// Static members.
	std::map<std::string, void *> Module::attached_modules;

	Module::Module()
	{
	}

	Module::~Module()
	{
	}

	fptr_luaopen Module::getLuaOpen()
	{
		return luaopen;
	}

	bool Module::init(const std::string & so, love_mod::modconf * conf)
	{
		try
		{
			mod_init = getf<fptr_init>(so, "init");
			mod_quit = getf<fptr_quit>(so, "quit");
			luaopen = getf<fptr_luaopen>(so, "luaopen");

			// Init the module.
			if(!mod_init(conf)) 
				return false;
		}
		catch(Exception e)
		{
			std::cerr << e.msg() << std::endl;
			return false;
		}

		return extra(so);
	}

	bool Module::extra(const std::string & so)
	{
		// Subclasses may init extra stuff here.
		return true;
	}

	bool Module::quit()
	{
		return mod_quit();
	}

	bool Module::attach(const std::string & so)
	{

		if(attached_modules.find(so) != attached_modules.end())
		{
			std::cerr << "Error, could not attach module: already attached." << std::endl;
			return false;
		}

		void * handle = SDL_LoadObject(so.c_str());

#ifdef LOVE_MOD_PATH
		if(handle == 0)
		{
			std::string mod_path(LOVE_MOD_PATH);
			mod_path += so;
			handle = SDL_LoadObject(mod_path.c_str());	
		}
#endif

		if(handle == 0) 
		{
			std::cerr << "Loading of module failed." << SDL_GetError() << std::endl;
			return false;
		}

		attached_modules[so] = handle;

		return true;
	}

	bool Module::detach(const std::string & so)
	{
		if(attached_modules.find(so) != attached_modules.end())
		{
			std::cerr << "Error, could not detach module: not attaced." << std::endl;
			return false;
		}

		SDL_UnloadObject(attached_modules[so]);

		attached_modules.erase(so);

		return true;
	}

	bool Module::detach_all()
	{

		std::map<std::string, void *>::const_iterator i = attached_modules.begin();
		
		while(i != attached_modules.end())
		{
			SDL_UnloadObject(i->second);
			i++;
		}

		attached_modules.clear();

		return true;
	}

	void * Module::getfunc(const std::string & so, const std::string & name)
	{
		// Check that the module is attached.
		if(attached_modules.find(so) == attached_modules.end() && !attach(so))
			throw Exception("Could not load function " + so + ":" + name + ": Could not attach the module.");

		// Return the function. The caller must check that the pointer is valid.
		void *fptr = SDL_LoadFunction(attached_modules[so], name.c_str());
		if (fptr == 0)
			throw Exception("Could not load function " + so + ":" + name + ": Function does not exist.");

		return fptr;
	}

}
