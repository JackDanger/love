#include <love/Core.h>

// STD
#include <iostream>

// LOVE
#include <love/Exception.h>

namespace love
{

	Core::Core()
		: argc(0), argv(0)
	{
	}

	Core::~Core()
	{
		dynamic_modules.clear();

		// Unload modules in reverse order.
		while(!modules.empty())
		{
			modules.back()->module_quit();
			modules.back()->unload();
			modules.pop_back();
		}
	}

	void Core::setArgs(int argc, char ** argv)
	{
		this->argc = argc;
		this->argv = argv;
	}

	bool Core::insmod(pModule m)
	{
		// Check args.
		if(argc == 0 || argv == 0)
		{
			std::cerr << "Error: arguments not set." << std::endl;
			return false;
		}

		// Load the module.
		if(!m->load())
			return false;

		// Add it to the list of modules.
		// Note that this must happen *BEFORE* module_init, 
		// otherwise love.system won't b included.
		modules.push_back(m);

		// Try to init the module.
		if(!m->module_init(argc, argv, this))
			return false;

		return true;
	}

	bool Core::insmod(fptr_init init, fptr_quit quit, fptr_open open)
	{
		// Create the static module.
		pModule m(new StaticModule(init, quit, open));
		return insmod(m);
	}

	bool Core::insmod(const std::string & name)
	{
		// Check args.
		if(argc == 0 || argv == 0)
		{
			std::cerr << "Error: arguments not set." << std::endl;
			return false;
		}
		
		// Create the dynamic module.
		pDynamicModule m(new DynamicModule(name));

		if(!insmod((pModule)m))
			return false;

		// Add to dynamic modules.
		dynamic_modules[name] = m;

		return true;
	}

	bool Core::open(void * vm)
	{
		for(int i = 0;i<(int)modules.size();i++)
		{
			if(!modules[i]->module_open(vm))
				return false;
		}
		return true;
	}

	bool Core::verify()
	{
		// Verify all standard modules
		if(!filesystem.verify()) return false;
		if(!graphics.verify()) return false;
		if(!timer.verify()) return false;
		if(!system.verify()) return false;
		if(!audio.verify()) return false;
		if(!mouse.verify()) return false;
		if(!keyboard.verify()) return false;
		return true;
	}

	void Core::error(const char * msg)
	{
		system.error(msg);
	}

	// Accessor functions.
	Filesystem * Core::getFilesystem() { return &filesystem; }
	Graphics * Core::getGraphics() { return &graphics; }
	Timer * Core::getTimer() { return &timer; }
	System * Core::getSystem() { return &system; }
	Audio * Core::getAudio() { return &audio; }
	Mouse * Core::getMouse() { return &mouse; }
	Keyboard * Core::getKeyboard() { return &keyboard; }

} // love
